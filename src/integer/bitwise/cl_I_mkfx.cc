// mkf_extract().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_byte.h"


// Implementation.

#include "cln/integer.h"
#include "cl_I.h"
#include "cl_DS.h"

namespace cln {

const cl_I mkf_extract (const cl_I& x, uintC p, uintC q)
{
      CL_ALLOCA_STACK;
      var const uintD* MSDptr;
      var uintC len;
      var const uintD* LSDptr;
      I_to_NDS_nocopy(x, MSDptr=,len=,LSDptr=,cl_true, { return 0; } ); // NDS zu x bilden
      // MSDptr erh�hen und len erniedrigen, so da� len = ceiling(q/intDsize) wird:
      { var uintC qD = ceiling(q,intDsize); // ceiling(q/intDsize)
        // wegen q<=l ist qD = ceiling(q/intDsize) <= ceiling((l+1)/intDsize) = len, also
        // pa�t qD ebenso wie len in ein uintC.
        MSDptr = MSDptr mspop (len - qD); // MSDptr um len-qD Digits erh�hen
        len = qD; // len um len-qD erniedrigen
      }
      // Platz (len Digits) f�r die neue UDS bereitstellen:
      var uintD* newMSDptr;
      num_stack_alloc_1(len, newMSDptr = ,); // Platz belegen
      {var uintC pD = p/intDsize; // floor(p/intDsize), pa�t in ein uintC
       // Kopiere len-pD Digits aus der DS zu x heraus:
       var uintD* midptr = copy_loop_msp(MSDptr,newMSDptr,len-pD);
       // L�sche p-intDsize*floor(p/intDsize) Bits im Digit unterhalb von midptr:
       {var uintC p_D = p%intDsize;
        if (!(p_D==0)) { lspref(midptr,0) &= minus_bit(p_D); }
       }
       // L�sche pD Digits dar�ber:
       clear_loop_msp(midptr,pD);
      }
      // L�sche intDsize*ceiling(q/intDsize)-q Bits im ersten Digit:
      {var uintL q_D = q%intDsize;
#ifdef HAVE_FAST_LONGLONG
       if (!(q_D==0))
         mspref(newMSDptr,0) &= (uintD)((1LL<<q_D)-1); // erase intDsize-q_D bits
#else
       if (!(q_D==0))
         mspref(newMSDptr,0) &= (uintD)((1L<<q_D)-1); // erase intDsize-q_D bits
#endif
      }
      // Jetzt enth�lt die UDS newMSDptr/len/.. die extrahierten Bits.
      return UDS_to_I(newMSDptr,len);
}

}  // namespace cln
