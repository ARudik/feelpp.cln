// rationalize().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_real.h"


// Implementation.

#include "cl_R.h"
#include "cl_float.h"
#include "cl_rational.h"
#include "cl_integer.h"
#include "cl_RA.h"
#include "cl_I.h"

// Methode (rekursiv dargestellt):
// Falls x rational ist: x.
// Falls x=0.0: 0.
// Falls x<0.0: (- (rationalize (- x)))
// Falls x>0.0:
//   (Integer-Decode-Float x) liefert m,e,s=1.
//   Falls e>=0 : Liefere x=m*2^e als Ergebnis.
//   Suche rationale Zahl zwischen a=(m-1/2)*2^e und b=(m+1/2)*2^e mit
//   m�glichst kleinem Z�hler und Nenner. (a,b einschlie�lich, aber da a,b
//   den Nenner 2^(|e|+1) haben, w�hrend x selbst den Nenner <=2^|e| hat,
//   k�nnen weder a noch b als Ergebnis herauskommen.)
//   Suche also bei gegebenem a,b (0<a<b) Bruch y mit a <= y <= b.
//   Rekursiv:
//     c:=(ceiling a)
//     if c<b then return c      ; weil a<=c<b, c ganz
//            else ; a nicht ganz (sonst c=a<b)
//              k:=c-1 ; k=floor(a), k < a < b <= k+1
//              return y = k + 1/(Bruch zwischen 1/(b-k) und 1/(a-k))
//                                ; wobei 1 <= 1/(b-k) < 1/(a-k)
// Man sieht, da� hierbei eine Kettenbruchentwicklung auftritt.
// Methode (iterativ):
// Falls x rational: x.
// (Integer-Decode-Float x) liefert m,e,s.
// e>=0 -> m*2^e*s als Ergebnis (darin ist x=0.0 inbegriffen).
// Bilde a:=(2*m-1)*2^(e-1) und b:=(2*m+1)*2^(e-1), rationale Zahlen >0,
//   (unk�rzbar, da Nenner Zweierpotenz und Z�hler ungerade).
// Starte Kettenbruchentwicklung (d.h. p[-1]:=0, p[0]:=1, q[-1]:=1, q[0]:=0, i:=0.)
// Schleife:
//   c:=(ceiling a)
//   if c>=b then k:=c-1, "Ziffer k", (a,b) := (1/(b-k),1/(a-k)), goto Schleife
// "Ziffer c".
// (Dabei bedeutet "Ziffer a" die Iteration
//   i:=i+1, p[i]:=a*p[i-1]+p[i-2], q[i]:=a*q[i-1]+q[i-2].)
// Ende, liefere s * (p[i]/q[i]), das ist wegen der Invarianten
//   p[i]*q[i-1]-p[i-1]*q[i]=(-1)^i  ein bereits gek�rzter Bruch.

inline const cl_RA rationalize (const cl_RA& x)
{
	// x rational -> x als Ergebnis.
	return x;
}

inline const cl_RA rationalize (const cl_F& x)
{
	var cl_idecoded_float x_decoded = integer_decode_float(x);
	var cl_I& m = x_decoded.mantissa;
	var cl_I& e = x_decoded.exponent;
	var cl_I& s = x_decoded.sign;
	if (!minusp(e)) {
		// e>=0.
		var cl_I y = ash(m,e);
		if (minusp(s)) { y = -y; }
		return y;
	}
	// e<0.
	var cl_I m2 = ash(m,1); // 2*m
	var cl_I num1 = minus1(m2); // 2*m-1
	var cl_I num2 = plus1(m2); // 2*m+1
	var cl_I den = ash(1,plus1(-e)); // 2^(1-e)
	var cl_RA a = I_I_to_RT(num1,den); // a := (2*m-1)/(2^(1-e))
	var cl_RA b = I_I_to_RT(num2,den); // b := (2*m+1)/(2^(1-e))
	var cl_I p_iminus1 = 0;		// p[i-1]
	var cl_I p_i       = 1;		// p[i]
	var cl_I q_iminus1 = 1;		// q[i-1]
	var cl_I q_i       = 0;		// q[i]
	var cl_I c;
	for (;;) {
		c = ceiling1(a);
		if (c < b)
			break;
		var cl_I k = minus1(c); // k = c-1
		{
			var cl_I p_iplus1 = k * p_i + p_iminus1;
			p_iminus1 = p_i; p_i = p_iplus1;
		}
		{
			var cl_I q_iplus1 = k * q_i + q_iminus1;
			q_iminus1 = q_i; q_i = q_iplus1;
		}
		{
			var cl_RA new_b = recip(a-k); // 1/(a-k)
			var cl_RA new_a = recip(b-k); // 1/(b-k)
			a = new_a; b = new_b;
		}
	}
	// letzte "Ziffer" k=c :
	var cl_I p_last = c * p_i + p_iminus1;
	var cl_I q_last = c * q_i + q_iminus1;
	if (minusp(s))
		p_last = - p_last;
	return I_I_to_RA(p_last,q_last); // +-p[i] / q[i] bilden
}

const cl_RA rationalize (const cl_R& x)
GEN_R_OP1_2(x, rationalize, return)
