// sqrtp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_RA.h"
#include "cl_integer.h"

cl_boolean sqrtp (const cl_RA& x, cl_RA* w)
{
// Methode:
// Bei Integers: klar.
// Bei Br�chen a/b : mu� a=c^2 und b=d^2 sein. Dann ist die Wurzel = c/d
// (mit ggT(c,d)=1 und d>1).
	if (integerp(x)) {
		DeclareType(cl_I,x);
		return sqrtp(x,(cl_I*)w);
	} else {
	// x ist Ratio
	DeclareType(cl_RT,x);
	var const cl_I& b = denominator(x);
	var cl_I d;
	if (!sqrtp(b,&d)) // Nenner auf Quadratzahl testen
		return cl_false;
	var const cl_I& a = numerator(x);
	var cl_I c;
	if (!sqrtp(a,&c)) // Z�hler auf Quadratzahl testen
		return cl_false;
	// beides Quadratzahlen -> Quotient der Wurzeln bilden
	*w = I_I_to_RT(c,d); return cl_true;
}}
