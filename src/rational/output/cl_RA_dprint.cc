// print_rational().

// General includes.
#include "cl_sysdep.h"

// Specification.
#include "cl_rational_io.h"


// Implementation.

#include "cl_output.h"
#include "cl_integer_io.h"
#include "cl_rational.h"
#include "cl_RA.h"

void print_rational (cl_ostream stream, const cl_print_rational_flags& flags, const cl_RA& z)
{
	var unsigned int base = flags.rational_base;
	if (flags.rational_readably)
		// Radix-Specifier ausgeben:
		switch (base) {
		case 2:
			fprintchar(stream,'#');
			fprintchar(stream,'b');
			break;
		case 8:
			fprintchar(stream,'#');
			fprintchar(stream,'o');
			break;
		case 16:
			fprintchar(stream,'#');
			fprintchar(stream,'x');
			break;
		case 10:
			if (integerp(z)) {
				DeclareType(cl_I,z);
				// Basis 10 bei Integers durch
				// nachgestellten Punkt kennzeichnen:
				print_integer(stream,base,z);
				fprintchar(stream,'.');
				return;
			}
		default:
			// Basis in #nR-Schreibweise ausgeben:
			fprintchar(stream,'#');
			print_integer(stream,10,base);
			fprintchar(stream,'r');
			break;
		}
	if (integerp(z)) {
		DeclareType(cl_I,z);
		// Integer in Basis base ausgeben:
		print_integer(stream,base,z);
	} else {
		DeclareType(cl_RT,z);
		// Ratio in Basis base ausgeben; Z�hler / Nenner
		print_integer(stream,base,numerator(z));
		fprintchar(stream,'/');
		print_integer(stream,base,denominator(z));
	}
}
