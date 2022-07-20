// BURAK KOCAUSTA 1901042605

#ifndef BASEITERATOR_H
#define BASEITERATOR_H

#include <memory>

namespace IterableGTU 
{
	// Base iterator class which can be derived for various iterator.
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	class BaseIterator
	{
	public:
	    typedef T         value_type;
	    typedef Distance  difference_type;
	    typedef Pointer   pointer;
	    typedef Reference reference;
	    typedef Category  iterator_category;		
	};
}

#endif //BASEITERATOR_H