// cl_FF_to_LF().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_F.h"


// Implementation.

#include "cl_FF.h"
#include "cl_LF.h"
#include "cl_LF_impl.h"
#include "cl_DS.h"

const cl_LF cl_FF_to_LF (const cl_FF& x, uintC len)
{
	// x entpacken:
	var cl_signean sign;
	var sintL exp;
	#if (intDsize==64)
	var uint64 mant;
	#else
	var uint32 mant;
	#endif
	FF_decode(x, { return encode_LF0(len); }, sign=,exp=(sintL),mant=);
	// Long-Float allozieren,
	// Mantisse mit intDsize*len-FF_mant_len-1 Nullbits auff�llen:
	var Lfloat y = allocate_lfloat(len,exp+LF_exp_mid,sign);
	var uintD* ptr = arrayMSDptr(TheLfloat(y)->data,len);
	// erste k := ceiling(FF_mant_len+1,intDsize) Digits mit mant f�llen:
	mant = mant << (ceiling(FF_mant_len+1,intDsize)*intDsize-(FF_mant_len+1));
	#if (intDsize==64)
	set_max64_Dptr(FF_mant_len+1,ptr,mant);
	#else
	set_max32_Dptr(FF_mant_len+1,ptr,mant);
	#endif
	clear_loop_msp(ptr mspop ceiling(FF_mant_len+1,intDsize),len-ceiling(FF_mant_len+1,intDsize));
	return y;
}
