// expt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_complex.h"


// Implementation.

#include "cl_C.h"
#include "cl_real.h"
#include "cl_I.h"

// Methode:
// F�r y>0:
//   a:=x, b:=y.
//   Solange b gerade, setze a:=a*a, b:=b/2. [a^b bleibt invariant, = x^y.]
//   c:=a.
//   Solange b:=floor(b/2) >0 ist,
//     setze a:=a*a, und falls b ungerade, setze c:=a*c.
//   Ergebnis c.
// F�r y=0: Ergebnis 1.
// F�r y<0: (/ (expt x (- y))).

// Assume y>0.
inline const cl_N expt_pos (const cl_N& x, const cl_I& y)
{
	var cl_N a = x;
	var cl_I b = y;
	while (!oddp(b)) { a = square(a); b = b >> 1; }
	var cl_N c = a;
	until (eq(b,1))
	  { b = b >> 1;
	    a = square(a);
	    if (oddp(b)) { c = a * c; }
	  }
	return c;
}

const cl_N expt (const cl_N& x, const cl_I& y)
{
	if (realp(x)) {
		DeclareType(cl_R,x);
		// x reell -> schnellere Routine
		return expt(x,y);
	}
	if (eq(y,0)) { return 1; } // y=0 -> Ergebnis 1
	var cl_boolean y_negative = minusp(y);
	var cl_I abs_y = (y_negative ? -y : y); // Betrag von y nehmen
	var cl_N z = expt_pos(x,abs_y); // (expt x (abs y))
	return (y_negative ? recip(z) : z); // evtl. noch Kehrwert nehmen
}
