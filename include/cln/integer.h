// Public integer operations.

#ifndef _CL_INTEGER_H
#define _CL_INTEGER_H

#include "cln/number.h"
#include "cln/integer_class.h"
#include "cln/random.h"

namespace cln {

CL_DEFINE_AS_CONVERSION(cl_I)


// Konversion Integer >=0, <2^32 nach uintL.
// Wandelt Integer >=0 in Unsigned Longword um.
// cl_I_to_UL(obj)
// > obj: Integer, sollte >=0, <2^32 sein
// < ergebnis: der Wert des Integer als 32-Bit-Zahl.
  extern uint32 cl_I_to_UL (const cl_I& obj);

// Konversion Integer >=-2^31, <2^31 nach sintL.
// Wandelt Integer in Signed Longword um.
// cl_I_to_L(obj)
// > obj: Integer, sollte >=-2^31, <2^31 sein
// < ergebnis: der Wert des Integer als 32-Bit-Zahl.
  extern sint32 cl_I_to_L (const cl_I& obj);

// Convert an integer to a C `int' or `unsigned int'.
#if (int_bitsize==32)
  inline int          cl_I_to_int  (const cl_I& x) { return cl_I_to_L(x);  }
  inline unsigned int cl_I_to_uint (const cl_I& x) { return cl_I_to_UL(x); }
#endif

// Convert an integer to a C `long' or `unsigned long'.
#if (long_bitsize==32)
  inline long          cl_I_to_long  (const cl_I& x) { return cl_I_to_L(x);  }
  inline unsigned long cl_I_to_ulong (const cl_I& x) { return cl_I_to_UL(x); }
#elif (long_bitsize==64)
  extern uint64 cl_I_to_UQ (const cl_I& obj);
  extern sint64 cl_I_to_Q (const cl_I& obj);
  inline long          cl_I_to_long  (const cl_I& x) { return cl_I_to_Q(x);  }
  inline unsigned long cl_I_to_ulong (const cl_I& x) { return cl_I_to_UQ(x); }
#endif


// Logische Operationen auf Integers:

// (LOGIOR x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I logior (const cl_I& x, const cl_I& y);

// (LOGXOR x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I logxor (const cl_I& x, const cl_I& y);

// (LOGAND x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I logand (const cl_I& x, const cl_I& y);

// (LOGEQV x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I logeqv (const cl_I& x, const cl_I& y);

// (LOGNAND x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I lognand (const cl_I& x, const cl_I& y);

// (LOGNOR x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I lognor (const cl_I& x, const cl_I& y);

// (LOGANDC2 x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I logandc2 (const cl_I& x, const cl_I& y);

// (LOGANDC1 x y), wenn x, y Integers sind.
// Ergebnis Integer.
inline const cl_I logandc1 (const cl_I& x, const cl_I& y)
{
	return logandc2(y,x);
}

// (LOGORC2 x y), wenn x, y Integers sind.
// Ergebnis Integer.
extern const cl_I logorc2 (const cl_I& x, const cl_I& y);

// (LOGORC1 x y), wenn x, y Integers sind.
// Ergebnis Integer.
inline const cl_I logorc1 (const cl_I& x, const cl_I& y)
{
	return logorc2(y,x);
}

// (LOGNOT x), wenn x ein Integer sind.
// Ergebnis Integer.
extern const cl_I lognot (const cl_I& x);

// Konstanten f�r BOOLE:
typedef enum {
	boole_clr,
	boole_set,
	boole_1,
	boole_2,
	boole_c1,
	boole_c2,
	boole_and,
	boole_ior,
	boole_xor,
	boole_eqv,
	boole_nand,
	boole_nor,
	boole_andc1,
	boole_andc2,
	boole_orc1,
	boole_orc2
} cl_boole;

// (BOOLE op x y), wenn x und y Integers und op ein Objekt sind.
// Ergebnis Integer.
extern const cl_I boole (cl_boole op, const cl_I& x, const cl_I& y);

// Pr�ft, ob (LOGTEST x y), wo x und y Integers sind.
// (LOGTEST x y) = (NOT (ZEROP (LOGAND x y))).
// < ergebnis: /=0, falls ja; =0, falls nein.
extern cl_boolean logtest (const cl_I& x, const cl_I& y);

// Pr�ft, ob (LOGBITP x y), wo x und y Integers sind.
// Ergebnis: /=0, wenn ja; =0, wenn nein.
extern cl_boolean logbitp (uintL x, const cl_I& y);
extern cl_boolean logbitp (const cl_I& x, const cl_I& y);

// Pr�ft, ob (ODDP x), wo x ein Integer ist.
// Ergebnis: /=0, falls ja; =0, falls nein.
extern cl_boolean oddp (const cl_I& x);

// Pr�ft, ob (EVENP x), wo x ein Integer ist.
// Ergebnis: /=0, falls ja; =0, falls nein.
inline cl_boolean evenp (const cl_I& x)
	{ return (cl_boolean) (!oddp(x)); }

// (ASH x y), wo x und y Integers sind. Ergebnis Integer.
extern const cl_I ash (const cl_I& x, sintL y);
extern const cl_I ash (const cl_I& x, const cl_I& y);

// (LOGCOUNT x), wo x ein Integer ist. Ergebnis uintL.
extern uintL logcount (const cl_I& x);

// (INTEGER-LENGTH x), wo x ein Integer ist. Ergebnis uintL.
extern uintL integer_length (const cl_I& x);

// (ORD2 x) = max{n>=0: 2^n | x }, wo x ein Integer /=0 ist. Ergebnis uintL.
extern uintL ord2 (const cl_I& x);

// power2p(x) stellt fest, ob ein Integer x>0 eine Zweierpotenz ist.
// Ergebnis: n>0, wenn x=2^(n-1), 0 sonst.
extern uintL power2p (const cl_I& x);

inline const cl_I operator| (const cl_I& x, const cl_I& y)
	{ return logior(x,y); }
inline const cl_I operator^ (const cl_I& x, const cl_I& y)
	{ return logxor(x,y); }
inline const cl_I operator& (const cl_I& x, const cl_I& y)
	{ return logand(x,y); }
inline const cl_I operator~ (const cl_I& x)
	{ return lognot(x); }
#ifdef WANT_OBFUSCATING_OPERATORS
// This could be optimized to use in-place operations.
inline cl_I& operator|= (cl_I& x, const cl_I& y) { return x = x | y; }
inline cl_I& operator^= (cl_I& x, const cl_I& y) { return x = x ^ y; }
inline cl_I& operator&= (cl_I& x, const cl_I& y) { return x = x & y; }
#endif


// Addition/Subtraktion von Integers

// (1+ x), wo x ein Integer ist. Ergebnis Integer.
extern const cl_I plus1 (const cl_I& x);

// (1- x), wo x ein Integer ist. Ergebnis Integer.
extern const cl_I minus1 (const cl_I& x);

// (+ x y), wo x und y Integers sind. Ergebnis Integer.
extern const cl_I operator+ (const cl_I& x, const cl_I& y);
// Dem C++-Compiler mu� man auch das Folgende sagen:
inline const cl_I operator+ (const int x, const cl_I& y)
	{ return cl_I(x) + y; }
inline const cl_I operator+ (const unsigned int x, const cl_I& y)
	{ return cl_I(x) + y; }
inline const cl_I operator+ (const long x, const cl_I& y)
	{ return cl_I(x) + y; }
inline const cl_I operator+ (const unsigned long x, const cl_I& y)
	{ return cl_I(x) + y; }
inline const cl_I operator+ (const cl_I& x, const int y)
	{ return x + cl_I(y); }
inline const cl_I operator+ (const cl_I& x, const unsigned int y)
	{ return x + cl_I(y); }
inline const cl_I operator+ (const cl_I& x, const long y)
	{ return x + cl_I(y); }
inline const cl_I operator+ (const cl_I& x, const unsigned long y)
	{ return x + cl_I(y); }

// (- x), wenn x ein Integer ist. Ergebnis Integer.
extern const cl_I operator- (const cl_I& x);

// (- x y), wo x und y Integers sind. Ergebnis Integer.
extern const cl_I operator- (const cl_I& x, const cl_I& y);
// Dem C++-Compiler mu� man auch das Folgende sagen:
inline const cl_I operator- (const int x, const cl_I& y)
	{ return cl_I(x) - y; }
inline const cl_I operator- (const unsigned int x, const cl_I& y)
	{ return cl_I(x) - y; }
inline const cl_I operator- (const long x, const cl_I& y)
	{ return cl_I(x) - y; }
inline const cl_I operator- (const unsigned long x, const cl_I& y)
	{ return cl_I(x) - y; }
inline const cl_I operator- (const cl_I& x, const int y)
	{ return x - cl_I(y); }
inline const cl_I operator- (const cl_I& x, const unsigned int y)
	{ return x - cl_I(y); }
inline const cl_I operator- (const cl_I& x, const long y)
	{ return x - cl_I(y); }
inline const cl_I operator- (const cl_I& x, const unsigned long y)
	{ return x - cl_I(y); }

// (abs x), wenn x ein Integer ist. Ergebnis Integer.
extern const cl_I abs (const cl_I& x);

// Shifts.
inline const cl_I operator<< (const cl_I& x, sintL y) // assume 0 <= y < 2^31
	{ return ash(x,y); }
inline const cl_I operator<< (const cl_I& x, const cl_I& y) // assume y >= 0
	{ return ash(x,y); }
inline const cl_I operator>> (const cl_I& x, sintL y) // assume 0 <= y < 2^31
	{ return ash(x,-y); }
inline const cl_I operator>> (const cl_I& x, const cl_I& y) // assume y >= 0
	{ return ash(x,-y); }


// Vergleich von Integers

// equal(x,y) vergleicht zwei Integers x und y auf Gleichheit.
extern cl_boolean equal (const cl_I& x, const cl_I& y);
// equal_hashcode(x) liefert einen equal-invarianten Hashcode f�r x.
extern uint32 equal_hashcode (const cl_I& x);

// compare(x,y) vergleicht zwei Integers x und y.
// Ergebnis: 0 falls x=y, +1 falls x>y, -1 falls x<y.
extern cl_signean compare (const cl_I& x, const cl_I& y);

inline bool operator== (const cl_I& x, const cl_I& y)
	{ return equal(x,y); }
inline bool operator!= (const cl_I& x, const cl_I& y)
	{ return !equal(x,y); }
inline bool operator<= (const cl_I& x, const cl_I& y)
	{ return compare(x,y)<=0; }
inline bool operator< (const cl_I& x, const cl_I& y)
	{ return compare(x,y)<0; }
inline bool operator>= (const cl_I& x, const cl_I& y)
	{ return compare(x,y)>=0; }
inline bool operator> (const cl_I& x, const cl_I& y)
	{ return compare(x,y)>0; }

// minusp(x) == (< x 0)
extern cl_boolean minusp (const cl_I& x);

// plusp(x) == (> x 0)
extern cl_boolean plusp (const cl_I& x);

// zerop(x) stellt fest, ob ein Integer = 0 ist.
extern cl_boolean zerop (const cl_I& x);


// BYTE-Operationen auf Integers

struct cl_byte {
	uintL size;
	uintL position;
// Konstruktor:
	cl_byte (unsigned int s, unsigned int p) : size (s), position (p) {}
};

// (LDB byte n), wo n ein Integer ist.
extern const cl_I ldb (const cl_I& n, const cl_byte& b);

// ldb_test(n,byte) f�hrt (LDB-TEST byte n) aus, wobei n ein Integer ist.
// Ergebnis: cl_false wenn nein (also alle fraglichen Bits =0), cl_true wenn ja.
extern cl_boolean ldb_test (const cl_I& n, const cl_byte& b);

// (MASK-FIELD byte n), wo n ein Integer ist.
extern const cl_I mask_field (const cl_I& n, const cl_byte& b);

// (DEPOSIT-FIELD newbyte byte n), wo n und newbyte Integers sind.
extern const cl_I deposit_field (const cl_I& newbyte, const cl_I& n, const cl_byte& b);

// (DPB newbyte byte n), wo n und newbyte Integers sind.
extern const cl_I dpb (const cl_I& newbyte, const cl_I& n, const cl_byte& b);


// Multiplikation ganzer Zahlen

// (* x y), wo x und y Integers sind. Ergebnis Integer.
extern const cl_I operator* (const cl_I& x, const cl_I& y);
// Dem C++-Compiler mu� man auch das Folgende sagen:
inline const cl_I operator* (const int x, const cl_I& y)
	{ return cl_I(x) * y; }
inline const cl_I operator* (const unsigned int x, const cl_I& y)
	{ return cl_I(x) * y; }
inline const cl_I operator* (const long x, const cl_I& y)
	{ return cl_I(x) * y; }
inline const cl_I operator* (const unsigned long x, const cl_I& y)
	{ return cl_I(x) * y; }
inline const cl_I operator* (const cl_I& x, const int y)
	{ return x * cl_I(y); }
inline const cl_I operator* (const cl_I& x, const unsigned int y)
	{ return x * cl_I(y); }
inline const cl_I operator* (const cl_I& x, const long y)
	{ return x * cl_I(y); }
inline const cl_I operator* (const cl_I& x, const unsigned long y)
	{ return x * cl_I(y); }

// (EXPT x 2), wo x Integer ist.
extern const cl_I square (const cl_I& x);

// (EXPT x y), wo x Integer, y Integer >0 ist.
extern const cl_I expt_pos (const cl_I& x, uintL y);
extern const cl_I expt_pos (const cl_I& x, const cl_I& y);

// Fakult�t (! n), wo n Fixnum >=0 ist. Ergebnis Integer.
extern const cl_I factorial (uintL n);
//CL_REQUIRE(cl_I_factorial)

// Double factorial (!! n), with n Fixnum >=0.  Returns integer.
extern const cl_I doublefactorial (uintL n);

// Binomialkoeffizient (n \choose k) = n! / k! (n-k)!, wo n,k >= 0 sind.
extern const cl_I binomial (uintL n, uintL k);


// Division ganzer Zahlen

// Return type for division operators.
// x / y  --> (q,r) with x = y*q+r.
struct cl_I_div_t {
	cl_I quotient;
	cl_I remainder;
// Constructor.
	cl_I_div_t () {}
	cl_I_div_t (const cl_I& q, const cl_I& r) : quotient(q), remainder(r) {}
};

// Dividiert zwei Integers x,y >=0 und liefert den Quotienten x/y >=0.
// Bei y=0 Error. Die Division mu� aufgehen, sonst Error.
// exquopos(x,y)
// > x,y: Integers >=0
// < ergebnis: Quotient x/y, ein Integer >=0
  extern const cl_I exquopos (const cl_I& x, const cl_I& y);

// Dividiert zwei Integers x,y und liefert den Quotienten x/y.
// Bei y=0 Error. Die Division mu� aufgehen, sonst Error.
// exquo(x,y)
// > x,y: Integers
// < ergebnis: Quotient x/y, ein Integer
  extern const cl_I exquo (const cl_I& x, const cl_I& y);

// mod(x,y) = (mod x y), wo x,y Integers sind.
  extern const cl_I mod (const cl_I& x, const cl_I& y);

// rem(x,y) = (rem x y), wo x,y Integers sind.
  extern const cl_I rem (const cl_I& x, const cl_I& y);

// Dividiert zwei Integers x,y und liefert Quotient und Rest
// (q,r) := (floor x y)
// floor2(x,y)
// > x,y: Integers
// < q,r: Quotient q, Rest r
  extern const cl_I_div_t floor2 (const cl_I& x, const cl_I& y);
  extern const cl_I floor1 (const cl_I& x, const cl_I& y);

// Dividiert zwei Integers x,y und liefert Quotient und Rest
// (q,r) := (ceiling x y)
// ceiling2(x,y)
// > x,y: Integers
// < q,r: Quotient q, Rest r
  extern const cl_I_div_t ceiling2 (const cl_I& x, const cl_I& y);
  extern const cl_I ceiling1 (const cl_I& x, const cl_I& y);

// Dividiert zwei Integers x,y und liefert Quotient und Rest
// (q,r) := (truncate x y)
// truncate2(x,y)
// > x,y: Integers
// < q,r: Quotient q, Rest r
  extern const cl_I_div_t truncate2 (const cl_I& x, const cl_I& y);
  extern const cl_I truncate1 (const cl_I& x, const cl_I& y);

// Dividiert zwei Integers x,y und liefert Quotient und Rest
// (q,r) := (round x y)
// round2(x,y)
// > x,y: Integers
// < q,r: Quotient q, Rest r
  extern const cl_I_div_t round2 (const cl_I& x, const cl_I& y);
  extern const cl_I round1 (const cl_I& x, const cl_I& y);


// ggT und kgV von Integers

// Liefert den ggT zweier Integers.
// gcd(a,b)
// > a,b: zwei Integers
// < ergebnis: (gcd a b), ein Integer >=0
  extern const cl_I gcd (const cl_I& a, const cl_I& b);
  extern uintV gcd (uintV a, uintV b);

// Liefert den ggT zweier Integers samt Beifaktoren.
// g = xgcd(a,b,&u,&v)
// > a,b: zwei Integers
// < u, v, g: Integers mit u*a+v*b = g >= 0
  extern const cl_I xgcd (const cl_I& a, const cl_I& b, cl_I* u, cl_I* v);
// Im Fall A/=0, B/=0 gen�gt das Ergebnis (g,u,v) den Ungleichungen:
//   Falls |A| = |B| : g = |A|, u = (signum A), v = 0.
//   Falls |B| | |A|, |B| < |A| : g = |B|, u = 0, v = (signum B).
//   Falls |A| | |B|, |A| < |B| : g = |A|, u = (signum A), v = 0.
//   Sonst: |u| <= |B| / (2*g), |v| <= |A| / (2*g).
//   In jedem Fall |u| <= |B|/g, |v| < |A|/g.
// (Beweis: Im Prinzip macht man ja mehrere Euklid-Schritte auf einmal. Im
// letzten Fall - oBdA |A| > |B| - braucht man mindestens zwei Euklid-Schritte,
// also gilt im Euklid-Tableau
//                 i         |A|            |B|         Erg.
//                --------------------------------------------
//                 0          1              0          |A|
//                 1          0              1          |B|
//                ...        ...            ...         ...
//                n-1  -(-1)^n*x[n-1]  (-1)^n*y[n-1]   z[n-1]
//                 n    (-1)^n*x[n]    -(-1)^n*y[n]     z[n]
//                n+1  -(-1)^n*x[n+1]  (-1)^n*y[n+1]   z[n+1] = 0
//                --------------------------------------------
//                       g = z[n], |u|=x[n], |v|=y[n]
// n>=2, z[0] > ... > z[n-1] > z[n] = g, g | z[n-1], also z[n-1] >= 2*g.
// Da aber mit  (-1)^i*x[i]*|A| - (-1)^i*y[i]*|B| = z[i]  f�r i=0..n+1
// und            x[i]*y[i+1] - x[i+1]*y[i] = (-1)^i  f�r i=0..n,
//                x[i]*z[i+1] - x[i+1]*z[i] = (-1)^i*|B|  f�r i=0..n,
//                y[i]*z[i+1] - y[i+1]*z[i] = -(-1)^i*|A|  f�r i=0..n
// auch |A| = y[i+1]*z[i] + y[i]*z[i+1], |B| = x[i+1]*z[i] + x[i]*z[i+1]
// f�r i=0..n (Cramersche Regel), folgt
// |A| = y[n]*z[n-1] + y[n-1]*z[n] >= y[n]*2*g + 0 = |v|*2*g,
// |B| = x[n]*z[n-1] + x[n-1]*z[n] >= x[n]*2*g + 0 = |u|*2*g.)

// Liefert den kgV zweier Integers.
// lcm(a,b)
// > a,b: zwei Integers
// < ergebnis: (lcm a b), ein Integer >=0
  extern const cl_I lcm (const cl_I& a, const cl_I& b);


// Wurzel aus ganzen Zahlen

// Zieht die Wurzel (ISQRT x) aus einem Integer.
// isqrt(x,&w)
// > x: Integer (sollte >=0 sein)
// < w: (isqrt x)
// < ergebnis: cl_true falls x Quadratzahl, cl_false sonst
  extern cl_boolean isqrt (const cl_I& x, cl_I* w);
// Wenn das boolesche Ergebnis uninteressant ist:
  inline const cl_I isqrt (const cl_I& x) { cl_I w; isqrt(x,&w); return w; }

// Stellt fest, ob ein Integer >=0 eine Quadratzahl ist.
// sqrtp(x,&w)
// > x: ein Integer >=0
// < w: Integer (sqrt x) falls x Quadratzahl
// < ergebnis: cl_true   ..................., cl_false sonst
  extern cl_boolean sqrtp (const cl_I& x, cl_I* w);

// Stellt fest, ob ein Integer >=0 eine n-te Potenz ist.
// rootp(x,n,&w)
// > x: ein Integer >=0
// > n: ein Integer >0
// < w: Integer (expt x (/ n)) falls x eine n-te Potenz
// < ergebnis: cl_true         ........................, cl_false sonst
  extern cl_boolean rootp (const cl_I& x, uintL n, cl_I* w);
  extern cl_boolean rootp (const cl_I& x, const cl_I& n, cl_I* w);


// max(x,y) liefert (max x y), wo x und y ganze Zahlen sind.
extern const cl_I max (const cl_I& x, const cl_I& y);

// min(x,y) liefert (min x y), wo x und y ganze Zahlen sind.
extern const cl_I min (const cl_I& x, const cl_I& y);

// signum(x) liefert (signum x), wo x eine ganze Zahl ist.
extern const cl_I signum (const cl_I& x);


// Multipliziert ein Integer mit 10 und addiert eine weitere Ziffer.
// mul_10_plus_x(y,x)
// > y: Integer Y (>=0)
// > x: Ziffernwert X (>=0,<10)
// < ergebnis: Integer Y*10+X (>=0)
extern const cl_I mul_10_plus_x (const cl_I& y, unsigned char x);


// 2-adische Inverse.
// cl_recip2adic(n,x)
// > n: >0
// > x: Integer, ungerade
// < ergebnis: n-Bit-Zahl y == (x mod 2^n)^-1, d.h. y*x == 1 mod 2^n
extern const cl_I cl_recip2adic (uintL n, const cl_I& x);

// 2-adische Division.
// cl_div2adic(n,x,y)
// > n: >0
// > x: Integer
// > y: Integer, ungerade
// < ergebnis: n-Bit-Zahl z == (x mod 2^n)/(y mod 2^n), d.h. z*y == x mod 2^n
extern const cl_I cl_div2adic (uintL n, const cl_I& x, const cl_I& y);


// numerator(r) liefert den Z�hler des Integer r.
inline const cl_I numerator (const cl_I& r)
	{ return r; }
// denominator(r) liefert den Nenner (> 0) des Integer r.
inline const cl_I denominator (const cl_I& r)
	{ (void)r; return 1; }


// Konversion zu einem C "float".
extern float float_approx (const cl_I& x);

// Konversion zu einem C "double".
extern double double_approx (const cl_I& x);


// random_I(randomstate,n) liefert zu einem Integer n>0 ein zuf�lliges
// Integer x mit 0 <= x < n.
// > randomstate: ein Random-State, wird ver�ndert
extern const cl_I random_I (random_state& randomstate, const cl_I& n);

inline const cl_I random_I (const cl_I& n)
	{ return random_I(default_random_state,n); }

// testrandom_I(randomstate) liefert ein zuf�lliges Integer zum Testen.
// > randomstate: ein Random-State, wird ver�ndert
extern const cl_I testrandom_I (random_state& randomstate);

inline const cl_I testrandom_I ()
	{ return testrandom_I(default_random_state); }


#ifdef WANT_OBFUSCATING_OPERATORS
// This could be optimized to use in-place operations.
inline cl_I& operator+= (cl_I& x, const cl_I& y) { return x = x + y; }
inline cl_I& operator+= (cl_I& x, const int y) { return x = x + y; }
inline cl_I& operator+= (cl_I& x, const unsigned int y) { return x = x + y; }
inline cl_I& operator+= (cl_I& x, const long y) { return x = x + y; }
inline cl_I& operator+= (cl_I& x, const unsigned long y) { return x = x + y; }
inline cl_I& operator++ /* prefix */ (cl_I& x) { return x = plus1(x); }
inline void operator++ /* postfix */ (cl_I& x, int dummy) { (void)dummy; x = plus1(x); }
inline cl_I& operator-= (cl_I& x, const cl_I& y) { return x = x - y; }
inline cl_I& operator-= (cl_I& x, const int y) { return x = x - y; }
inline cl_I& operator-= (cl_I& x, const unsigned int y) { return x = x - y; }
inline cl_I& operator-= (cl_I& x, const long y) { return x = x - y; }
inline cl_I& operator-= (cl_I& x, const unsigned long y) { return x = x - y; }
inline cl_I& operator-- /* prefix */ (cl_I& x) { return x = minus1(x); }
inline void operator-- /* postfix */ (cl_I& x, int dummy) { (void)dummy; x = minus1(x); }
inline cl_I& operator*= (cl_I& x, const cl_I& y) { return x = x * y; }
inline cl_I& operator<<= (cl_I& x, sintL y) // assume 0 <= y < 2^31
	{ return x = x << y; }
inline cl_I& operator<<= (cl_I& x, const cl_I& y) // assume y >= 0
	{ return x = x << y; }
inline cl_I& operator>>= (cl_I& x, sintL y) // assume 0 <= y < 2^31
	{ return x = x >> y; }
inline cl_I& operator>>= (cl_I& x, const cl_I& y) // assume y >= 0
	{ return x = x >> y; }
#if 0 // Defining operator/ collides with the operator/ (cl_RA, cl_RA).
// operator/ should perform exquo(x,y), but people believe in the C semantics.
// And it would be wiser to use floor1 and mod instead of truncate1 and rem,
// but again, many C compilers implement / and % like this and people believe
// in it.
inline const cl_I operator/ (const cl_I& x, const cl_I& y) { return truncate1(x,y); }
inline const cl_I operator% (const cl_I& x, const cl_I& y) { return rem(x,y); }
inline cl_I& operator/= (cl_I& x, const cl_I& y) { return x = x / y; }
inline cl_I& operator%= (cl_I& x, const cl_I& y) { return x = x % y; }
#endif
#endif


// Runtime typing support.
extern cl_class cl_class_fixnum;
extern cl_class cl_class_bignum;
CL_FORCE_LINK(cl_I_classes_dummy, cl_class_fixnum)


// Debugging support.
#ifdef CL_DEBUG
extern int cl_I_debug_module;
CL_FORCE_LINK(cl_I_debug_dummy, cl_I_debug_module)
#endif

}  // namespace cln

#endif /* _CL_INTEGER_H */
