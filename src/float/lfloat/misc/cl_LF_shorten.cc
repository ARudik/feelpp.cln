// shorten().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_LF.h"


// Implementation.

#include "cl_LF_impl.h"
#include "cl_DS.h"
#include "cl_F.h"

const cl_LF shorten (const cl_LF& x, uintC len)
{
      // x = 0.0 braucht nicht abgefangen zu werden, da bei Mantisse 0 dann
      // sowieso abgerundet wird, die Mantisse also 0 bleibt.
      var Lfloat y = allocate_lfloat(len,TheLfloat(x)->expo,TheLfloat(x)->sign); // neues LF
      { var uintC oldlen = TheLfloat(x)->len; // alte L�nge, > len
        // Mantisse von x nach y kopieren:
        copy_loop_msp(arrayMSDptr(TheLfloat(x)->data,oldlen),arrayMSDptr(TheLfloat(y)->data,len),len);
        // Entscheiden, ob auf- oder abrunden:
        var uintD* ptr = arrayMSDptr(TheLfloat(x)->data,oldlen) mspop len;
        if ( ((sintD)mspref(ptr,0) >= 0) // n�chstes Bit eine 0 -> abrunden
             || ( ((mspref(ptr,0) & ((uintD)bit(intDsize-1)-1)) ==0) // eine 1 und alles weitere Nullen?
                  && !test_loop_msp(ptr mspop 1,oldlen-len-1)
                  // round-to-even
                  && ((lspref(ptr,0) & bit(0)) ==0)
           )    )
          // abrunden
          {}
          else
          // aufrunden
          { if ( inc_loop_lsp(arrayLSDptr(TheLfloat(y)->data,len),len) )
              // �bertrag durch Aufrunden
              { mspref(arrayMSDptr(TheLfloat(y)->data,len),0) = bit(intDsize-1); // Mantisse := 10...0
                // Exponent erh�hen:
                if (++(TheLfloat(y)->expo) == LF_exp_high+1) { cl_error_floating_point_overflow(); }
          }   }
      }
      return y;
}
