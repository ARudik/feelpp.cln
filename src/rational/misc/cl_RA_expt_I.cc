// expt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational.h"


// Implementation.

#include "cl_integer.h"
#include "cl_I.h"

const cl_RA expt (const cl_RA& x, const cl_I& y)
{
// Methode:
// F�r y>0: klar.
// F�r y=0: Ergebnis 1.
// F�r y<0: (/ (expt x (- y))).
	if (minusp(y))
		return recip(expt_pos(x,-y));
	elif (zerop(y))
		return 1;
	else // y > 0
		return expt_pos(x,y);
}
