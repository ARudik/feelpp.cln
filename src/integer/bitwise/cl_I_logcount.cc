// logcount().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_D.h"
#include "cl_low.h"

namespace cln {

uintL logcount (const cl_I& x)
{
	if (fixnump(x))
	  { var uint32 x32 = FN_to_L(x); // x als 32-Bit-Zahl
	    if (FN_L_minusp(x,(sint32)x32)) { x32 = ~ x32; } // falls <0, komplementieren
	    logcount_32(); // Bits von x32 z�hlen
	    return x32;
	  }
          else
          { var const uintD* MSDptr;
            var uintC len;
            BN_to_NDS_nocopy(x, MSDptr=,len=,); // DS zu x bilden, len>0.
            var uintL bitcount = 0; // Bitz�hler
            var const uintD* ptr = MSDptr; // l�uft durch die Digits durch
            var uintD sign = sign_of_sintD(mspref(ptr,0)); // Vorzeichen
            dotimespC(len,len,
              { bitcount += (uintL)logcountD(msprefnext(ptr) ^ sign); });
            // 0 <= bitcount < intDsize*2^intCsize.
            return bitcount;
          }
}

}  // namespace cln
