// cl_F_extendsqrt().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cl_SF.h"
#include "cl_LF.h"

const cl_F cl_F_extendsqrt (const cl_F& x)
{
// Methode:
// SF -> FF wegen 17+sqrt(17)+2 = 23.2 < 24
// FF -> DF wegen 24+sqrt(24)+2 = 30.9 < 53
// DF -> LF(4) wegen 53+sqrt(53)+2 = 62.3 < 64
// LF(n) -> LF(n+1) f�r n<=12 wegen 16n+sqrt(16n)+2 < 16(n+1)
// LF(n) -> LF(n+2) f�r n<=56 wegen 16n+sqrt(16n)+2 < 16(n+2)
// LF(n) -> LF(n+4) f�r n<=240
// LF(n) -> LF(n+8) f�r n<=992
// LF(n) -> LF(n+16) f�r n<=4032
// LF(n) -> LF(n+32) f�r n<=16256
// LF(n) -> LF(n+65) f�r n<=65535
	floatcase(x
	,	if (SF_mant_len+1<=17)
			return cl_SF_to_FF(x); // 17+sqrt(17)+2 = 23.2 < 24
		else
			return cl_SF_to_DF(x); // 24+sqrt(24)+2 = 30.9 < 53
	,	return cl_FF_to_DF(x); // 24+sqrt(24)+2 = 30.9 < 53
	,	return cl_DF_to_LF(x,ceiling(63,intDsize)); // 53+sqrt(53)+2 = 62.3 < 63
	,	return extend(x,cl_LF_len_incsqrt(TheLfloat(x)->len));
	);
}
