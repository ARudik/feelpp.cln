// ldb_extract().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_I_byte.h"


// Implementation.

#include "cln/integer.h"
#include "cl_I.h"
#include "cl_DS.h"

namespace cln {

const cl_I ldb_extract (const cl_I& x, uintC p, uintC q)
    { CL_ALLOCA_STACK;
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
      // LSDptr und len um floor(p/intDsize) erniedrigen:
      { var uintC pD = floor(p,intDsize); // floor(p/intDsize)
        LSDptr = LSDptr lspop pD;
        len -= pD;
      }
      // Jetzt enth�lt MSDptr/len/LSDptr genau die ma�geblichen Digits.
      var uintD* newMSDptr;
      { var uintL i = p%intDsize; // p mod intDsize
        // Kopiere sie und schiebe sie dabei um i Bits nach rechts:
        num_stack_alloc_1(len, newMSDptr=,); // neue UDS newMSDptr/len/..
        if (i==0)
          { copy_loop_msp(MSDptr,newMSDptr,len); }
          else
          { shiftrightcopy_loop_msp(MSDptr,newMSDptr,len,i,0); }
      }
      // newMSDptr/len/.. = geschobene Kopie der ma�geblichen Digits
      // Ausblenden der Bits mit Nummern >= q-p:
      { var uintC bitcount = intDsize*len - (q-p);
        // Anzahl vorne auszublendender Bits ( >=0, <= intDsize-1 + intDsize-1 )
        if (bitcount>=intDsize)
          { bitcount -= intDsize; msshrink(newMSDptr); len -= 1; } // intDsize Bits ausblenden
        // Noch 0 <= bitcount < intDsize Bits auszublenden:
        if (bitcount > 0)
          { mspref(newMSDptr,0) &= (uintD)(bit(intDsize-bitcount)-1); }
      }
      // Jetzt enth�lt die UDS newMSDptr/len/.. die extrahierten Bits.
      return UDS_to_I(newMSDptr,len); // UDS in Integer umwandeln
    }

}  // namespace cln
