// random_R().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/real.h"


// Implementation.

#include "cl_R.h"
#include "cl_RA.h"
#include "cln/io.h"
#include "cln/real_io.h"
#include "cln/abort.h"

namespace cln {

const cl_R random_R (random_state& r, const cl_R& n)
{
	// n mu� eine reelle Zahl sein, >0 und Float oder Integer
	if (plusp(n)) {
		if (floatp(n)) {
			DeclareType(cl_F,n);
			return random_F(r,n);
		} else {
			DeclareType(cl_RA,n);
			if (integerp(n)) {
				DeclareType(cl_I,n);
				return random_I(r,n);
			}
		}
	}
	fprint(std::cerr, "random: argument should be positive and an integer or float: ");
	fprint(std::cerr, n);
	fprint(std::cerr, "\n");
	cl_abort();
}

}  // namespace cln
