// BURAK KOCAUSTA 1901042605

#ifndef EXCEPTIONSGTU_H
#define EXCEPTIONSGTU_H

#include <string>
namespace ExceptionsGTU
{
	// Can be thrown when, out of bound occurs.
	class OutOfRange {
	public:
		OutOfRange ( ) {}
		std::string what ( )
		{
			return "Array subscript exceeds its allowed range!";	
		}
	};

	// Can be thrown when entered iterator is invalid.
	class InvalidIterator {
	public:
		InvalidIterator( ) {}
		std::string what ( )
		{
			return "Invalid iterator is entered!";
		}
	};
}

#endif // EXCEPTIONSGTU_H