// logeqv().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_DS.h"
#include "cl_I_log.h"

namespace cln {

// Logische Operationen auf Integers:
// Methode: aus den L�ngen der beiden Argumente eine obere Schranke f�r
// die L�nge des Ergebnisses berechnen (das Maximum der beiden L�ngen und
// FN_maxlength), so da� das MSD f�r unendlich viele Bits steht.
// Dann beide Argumente in gleichgro�e Digit sequences umwandeln, Operation
// mit einer einfachen Schleife durchf�hren.

const cl_I logeqv (const cl_I& x, const cl_I& y)
    { if (fixnump(x) && fixnump(y)) // Beides Fixnums -> ganz einfach:
        { // bitweise als Fixnum zur�ck
          return cl_I_from_word(~(x.word ^ y.word) & cl_combine(cl_FN_tag,~(cl_uint)0));
        }
        else
        { CL_ALLOCA_STACK;
          var uintC n; // Anzahl der Digits
         {var uintC nx = I_to_DS_need(x);
          var uintC ny = I_to_DS_need(y);
          n = (nx>=ny ? nx : ny);
         }
         {var uintD* xptr; I_to_DS_n(x,n,xptr=); // Pointer in DS zu x
          var uintD* yptr; I_to_DS_n(y,n,yptr=); // Pointer in DS zu y
          var uintD* zptr = xptr; // Pointer aufs Ergebnis
          eqv_loop_msp(xptr,yptr,n); // mit NOT XOR verkn�pfen
          return DS_to_I(zptr,n); // Ergebnis als Integer
    }   }}

}  // namespace cln
