// Formatted output functions � la Common Lisp.

#ifndef _CL_FORMAT_H
#define _CL_FORMAT_H

#include "cln/number.h"
#include "cln/io.h"
#include "cln/float.h"

namespace cln {

// gibt arg als r�mische Zahl auf stream aus, z.B. 4 als IIII.
extern void format_old_roman (cl_ostream stream, const cl_I& arg);

// gibt arg als r�mische Zahl auf stream aus, z.B. 4 als IV.
extern void format_new_roman (cl_ostream stream, const cl_I& arg);

extern const char * const cl_format_tens [10];

// gibt die ganze Zahl arg im Klartext auf englisch auf den Stream aus.
extern void format_cardinal (cl_ostream stream, const cl_I& arg);

// gibt eine ganze Zahl arg als Abz�hlnummer im Klartext auf englisch
// auf den stream aus.
extern void format_ordinal (cl_ostream stream, const cl_I& arg);

// gibt count (>=0) Zeichen ch auf stream aus.
inline void format_padding (cl_ostream stream, sintL count, char ch)
{
	for (; count >= 0; count--)
		fprintchar(stream,ch);
}

// gibt auf den Stream stream aus:
// den String str, eventuell aufgef�llt mit Padding characters padchar.
// Und zwar so, da� die Breite mindestens mincol ist. Um das zu erreichen,
// werden mindestens minpad Zeichen eingef�gt, eventuelle weitere dann in
// Bl�cken � colinc Zeichen. Falls padleftflag, werden sie links eingef�gt,
// sonst rechts vom String.
extern void format_padded_string (cl_ostream stream, sintL mincol, sintL colinc, sintL minpad, char padchar, cl_boolean padleftflag, const char * str);

// gibt den Integer arg auf den Stream aus:
// in Zahlenbasis base, mit Vorzeichen (+ nur falls >0 und positive-sign-flag),
// bei commaflag alle drei Stellen unterbrochen durch ein Zeichen commachar.
// Das Ganze links aufgef�llt mit padchar's, so da� die Gesamtbreite mindestens
// mincol ist.
extern void format_integer (cl_ostream stream, const cl_I& arg, unsigned int base, sintL mincol, char padchar, char commachar, uintL commainterval, cl_boolean commaflag, cl_boolean positive_sign_flag);

// format_scale_exponent(arg) liefert zur Floating-Point-Zahl arg
// drei Werte: mantissa und n, mit
// ganzem n und mantissa floating-point, 0.1 <= mantissa < 1,
// arg = mantissa * 10^n * sign (also 10^(n-1) <= abs(arg) < 10^n ).
// (Bei arg=0.0: 0.0 und n=0.)
extern const decoded_float format_scale_exponent (const cl_F& arg);
CL_REQUIRE(cl_fmt_scaleexp)

// format_float_to_string(arg,width,d,k,dmin)
// ergibt einen String zum Floating-point arg:
// er hat den Wert von abs(arg)*expt(10,k), dabei mind. d Nachkommastellen
// und h�chstens die L�nge width (width<=0 -> keine Einschr�nkung).
// Trotzdem wird nicht auf weniger als dmin Stellen gerundet.
struct digits_with_dot {
	char * string; // Mit malloc_hook() alloziert, mit free_hook() freizugeben.
	uintL length; // strlen(string)
	cl_boolean dot_comes_first; // string[0] == '.' ?
	cl_boolean dot_comes_last; // string[strlen(string)-1] == '.' ?
	uintL dot_position; // string[dot_position] is '.'
// Constructor.
	digits_with_dot (char* s, uintL l, cl_boolean df, cl_boolean dl, uintL dp)
		: string(s), length(l), dot_comes_first(df), dot_comes_last(dl), dot_position(dp) {}
};
extern const digits_with_dot format_float_to_string (const cl_F& arg, const sintL width, const sintL d, const sintL k, const sintL dmin);
CL_REQUIRE(cl_fmt_floatstring)

}  // namespace cln

#endif /* _CL_FORMAT_H */
