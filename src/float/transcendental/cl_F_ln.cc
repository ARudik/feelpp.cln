// ln().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_float.h"


// Implementation.

#include "cl_F_tran.h"
#include "cl_F.h"
#include "cl_SF.h"
#include "cl_integer.h"
#include "cl_lfloat.h"
#include "cl_LF.h"

const cl_F ln (const cl_F& x)
{
// Methode:
// d := (float-digits x),
// Genauigkeit um sqrt(d)+max(integer-length(e)) Bits erh�hen,
// (m,e) := (decode-float x), so da� 1/2 <= m < 1.
// m<2/3 -> m:=2m, e:=e-1, so da� 2/3 <= m <= 4/3.
// ln(m) errechnen, ln(x)=ln(m)+e*ln(2) als Ergebnis.

	// Rechengenauigkeit erh�hen und m,e,s bestimmen:
	if (longfloatp(x) && (TheLfloat(x)->len >= 110)) {
		DeclareType(cl_LF,x);
		var cl_decoded_lfloat m_e_s = decode_float(extend(x,TheLfloat(x)->len+1));
		var cl_LF& m = m_e_s.mantissa;
		var cl_I& e = m_e_s.exponent;
		if (m < make_SF(0,0+SF_exp_mid,floor(bit(SF_mant_len+2),3))) { // Short-Float 2/3
			m = scale_float(m,1); // m verdoppeln
			e = minus1(e); // e decrementieren
		}
		var cl_F res = lnx_ratseries(m);
		if (!zerop(e))
			res = res + cl_float(e,m)*cl_ln2(m); // ln(m)+e*ln(2)
		return cl_float(res,x);
	} else {
		var cl_decoded_float m_e_s = decode_float(cl_F_extendsqrtx(x));
		var cl_F& m = m_e_s.mantissa;
		var cl_I& e = m_e_s.exponent;
		if (m < make_SF(0,0+SF_exp_mid,floor(bit(SF_mant_len+2),3))) { // Short-Float 2/3
			m = scale_float(m,1); // m verdoppeln
			e = minus1(e); // e decrementieren
		}
		var cl_F res = lnx_naive(m);
		if (!zerop(e))
			res = res + cl_float(e,m)*cl_ln2(m); // ln(m)+e*ln(2)
		return cl_float(res,x);
	}
}
