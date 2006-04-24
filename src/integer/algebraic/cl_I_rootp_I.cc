// rootp().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"

namespace cln {

// Methode:
// Falls x=0 oder x=1: x = x^n -> JA, x als Ergebnis.
// Hier also x>1. Suche ein Integer y > 1 mit x=y^n.
// Falls n >= integer_length(x): NEIN. (Da y>=2, m��te x>=2^n gelten.)
// Hier also n>0 klein...

cl_boolean rootp (const cl_I& x, const cl_I& n, cl_I* w)
{
	if (eq(x,0) || eq(x,1)) // x=0 oder x=1 ?
	  { *w = x; return cl_true; } // ja -> x als Ergebnis
	if (n >= (cl_I)(unsigned long)integer_length(x))
	  { return cl_false; }
	// Nun ist n < (integer-length x). Also pa�t n in ein uintC.
	return cl_rootp_aux(x,cl_I_to_ulong(n),w);
}

}  // namespace cln
