// expt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/rational.h"


// Implementation.

namespace cln {

const cl_RA expt (const cl_RA& x, sintL y)
{
// Methode:
// F�r y>0: klar.
// F�r y=0: Ergebnis 1.
// F�r y<0: (/ (expt x (- y))).
	if (y > 0)
		return expt_pos(x,(uintL)y);
	elif (y == 0)
		return 1;
	else // y < 0
		return recip(expt_pos(x,(uintL)(-y)));
}

}  // namespace cln
