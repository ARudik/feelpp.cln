// I/O of floats.

#ifndef _CL_FLOAT_IO_H
#define _CL_FLOAT_IO_H

#include "cl_number_io.h"
#include "cl_float.h"


// Undocumented input functions

// Wandelt eine Zeichenkette mit Float-Syntax in ein Float um.
// read_float(base,sign,string,index1,index4,index2,index3)
// > base: Lesebasis (=10)
// > sign: Vorzeichen (/=0 falls negativ)
// > string: Simple-String (enth�lt Ziffern und evtl. Punkt und Exponentmarker)
// > index1: Index vom Mantissenanfang (excl. Vorzeichen)
// > index4: Index nach dem Mantissenende
// > index2: Index beim Ende der Characters
// > index3: Index nach dem Dezimalpunkt (=index4 falls keiner da)
//   (also Mantisse mit index4-index1 Characters: Ziffern und max. 1 '.')
//   (also index4-index3 Nachkommaziffern)
//   (also bei index4<index2: index4 = Index des Exponent-Markers,
//    index4+1 = Index des Exponenten-Vorzeichens oder der ersten
//    Exponenten-Ziffer)
// < ergebnis: Float
extern const cl_F read_float (unsigned int base, cl_float_format_t prec,
                  cl_signean sign, const char * string, uintL index1, uintL index4, uintL index2, uintL index3);

// The following does strictly the same as the general read_complex.
// It is here only so that you don't need the complex and rational number
// readers in order to read a float number. ("Treeshaking")
extern const cl_F read_float (const cl_read_flags& flags, const char * string, const char * string_limit, const char * * end_of_parse);
extern const cl_F read_float (cl_istream stream, const cl_read_flags& flags);

// Documented input functions

inline cl_istream operator>> (cl_istream stream, cl_F& result)
{
	extern cl_read_flags cl_F_read_flags;
	result = read_float(stream,cl_F_read_flags);
	return stream;
}


// Undocumented output functions


// Documented output functions

// Gibt ein Float aus.
// print_float(stream,z);
// > z: Float
// > stream: Stream
extern void print_float (cl_ostream stream, const cl_print_flags& flags, const cl_F& z);
extern void print_float (cl_ostream stream, const cl_print_number_flags& flags, const cl_F& z);
extern void print_float (cl_ostream stream, const cl_print_real_flags& flags, const cl_F& z);
extern void print_float (cl_ostream stream, const cl_print_float_flags& flags, const cl_F& z);

// Gibt ein Float bin�r (sehr primitiv) aus.
// print_float_binary(stream,z);
// > z: Float
// > stream: Stream
extern void print_float_binary (cl_ostream stream, const cl_F& z);

// The following does strictly the same as the general `fprint' for numbers.
// It is here only so that you don't need the complex printer
// in order to print a float. ("Treeshaking")

inline void fprint (cl_ostream stream, const cl_F& x)
{
	extern cl_print_flags cl_default_print_flags;
	print_float(stream,cl_default_print_flags,x);
}

CL_DEFINE_PRINT_OPERATOR(cl_F)


#endif /* _CL_FLOAT_IO_H */
