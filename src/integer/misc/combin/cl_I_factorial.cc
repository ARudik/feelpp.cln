// factorial().

// General includes.
#include "cl_sysdep.h"

CL_PROVIDE(cl_I_factorial)

// Specification.
#include "cln/integer.h"


// Implementation.

#include "cl_I.h"
#include "cl_I_combin.h"

namespace cln {

  // Methode:
  // n <= 10 -> Ergebnis (Fixnum) aus Tabelle
  // Sonst:
  //   Zweierpotenzen extra am Schlu� durch einen Shift um
  //   ord2(n!) = sum(k>=1, floor(n/2^k) ) = n - logcount(n)  Bits.
  //   F�r k>=1 wird jede ungerade Zahl m im Intervall n/2^k < m <= n/2^(k-1)
  //   genau k mal gebraucht (als ungerader Anteil von m*2^0,...,m*2^(k-1) ).
  //   Zur Bestimmung des Produkts aller ungeraden Zahlen in einem Intervall
  //   a < m <= b verwenden wir eine rekursive Funktion, die nach Divide-and-
  //   Conquer das Produkt �ber die Intervalle a < m <= c und c < m <= b
  //   (c := floor((a+b)/2)) bestimmt und beide zusammenmultipliziert. Dies
  //   vermeidet, da� oft gro�e Zahlen mit ganz kleinen Zahlen multipliziert
  //   werden.

static cl_I const fakul_table [] = {
        L_to_FN(1),
        L_to_FN(1UL),
        L_to_FN(1UL*2),
        #if (cl_value_len>=4)
        L_to_FN(1UL*2*3),
        #if (cl_value_len>=6)
        L_to_FN(1UL*2*3*4),
        #if (cl_value_len>=8)
        L_to_FN(1UL*2*3*4*5),
        #if (cl_value_len>=11)
        L_to_FN(1UL*2*3*4*5*6),
        #if (cl_value_len>=14)
        L_to_FN(1UL*2*3*4*5*6*7),
        #if (cl_value_len>=17)
        L_to_FN(1UL*2*3*4*5*6*7*8),
        #if (cl_value_len>=20)
        L_to_FN(1UL*2*3*4*5*6*7*8*9),
        #if (cl_value_len>=23)
        L_to_FN(1UL*2*3*4*5*6*7*8*9*10),
        #if (cl_value_len>=27)
        L_to_FN(1UL*2*3*4*5*6*7*8*9*10*11),
        #if (cl_value_len>=30)
        L_to_FN(1UL*2*3*4*5*6*7*8*9*10*11*12),
        #if (cl_value_len>=34)
        ...
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
        #endif
};

const cl_I factorial (uintL n) // assume n >= 0 small
{
      if (n < sizeof(fakul_table)/sizeof(cl_I))
        { return fakul_table[n]; }
        else
        { var cl_I prod = 1; // bisheriges Produkt := 1
          var uintL k = 1;
          var uintL A = n;
          var uintL B = n; // obere Intervallgrenze floor(n/2^(k-1))
          loop
            { // 'A' enth�lt floor(n/2^(k-1)).
              A = A >> 1; // untere Grenze floor(n/2^k)
              // 'A' enth�lt floor(n/2^k).
              // Bilde Teilprodukt prod(A < i <= B & oddp(i), i)
              //       = prod(floor((A-1)/2) < i <= floor((B-1)/2), 2*i+1)
              // wobei B = floor(n/2^(k-1)), A = floor(n/2^k) = floor(B/2).
              { var uintL b = floor(B-1,2);
                if (b==0) break; // B=2 oder B=1 -> Produkt fertig
                var uintL a = floor(A-1,2);
                prod = expt_pos(cl_I_prod_ungerade(a,b),k) * prod; // aufmultiplizieren
              }
              k = k+1;
              B = A;
            }
          return prod << (n - logcount(n));
        }
}
// Bit complexity (N := n): O(log(N)^2*M(N)).

}  // namespace cln

CL_PROVIDE_END(cl_I_factorial)
