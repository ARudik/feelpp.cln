// cl_random implementation

#ifndef _CL_RANDOM_IMPL_H
#define _CL_RANDOM_IMPL_H

#include "cln/random.h"

namespace cln {

// random_UDS(randomstate,MSDptr,len) f�llt die UDS MSDptr/len/..
// mit len Zufallsdigits.
// > randomstate: ein Random-State, wird ver�ndert
// > MSDptr/len/..: wo die Zufallsdigits abgelegt werden sollen
// > len: gew�nschte Anzahl von Zufallsdigits
extern void random_UDS (random_state& randomstate, uintD* MSDptr, uintC len);

// testrandom_UDS(randomstate,MSDptr,len) f�llt die UDS MSDptr/len/..
// mit len Zufallsdigits, mit relativ langen Bl�cken von Nullen und Einsen.
// > randomstate: ein Random-State, wird ver�ndert
// > MSDptr/len/..: wo die Zufallsdigits abgelegt werden sollen
// > len: gew�nschte Anzahl von Zufallsdigits
extern void testrandom_UDS (random_state& randomstate, uintD* MSDptr, uintC len);

}  // namespace cln

#endif /* _CL_RANDOM_IMPL_H */
