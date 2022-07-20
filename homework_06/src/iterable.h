// BURAK KOCAUSTA 1901042605

#ifndef ITERABLE_H
#define ITERABLE_H

#include "gtuiterator.h"
#include "gtuiteratorconst.h"

namespace IterableGTU
{
	//An abstract class to creating templated classes like vector, array, set.
	template < class T >
	class Iterable
	{
	public:
		
		// Tests whether the container is empty 
		virtual bool empty ( ) = 0;
		
		// Returns the containers size
		virtual size_t size ( ) = 0;

		// Erases the iterator according to the given position.
		virtual GTUIterator<T> erase (const GTUIterator<T>& position) = 0;
		
		// Erases the iterator(s) between first and last.
		virtual GTUIterator<T> erase (const GTUIterator<T>& first, const GTUIterator<T>& last) = 0;
		
		// Clears the container.
		virtual void clear ( ) = 0;
		
		//	Returns the iterator to the container's beginning.
		virtual GTUIterator<T> begin ( ) = 0;

		//	Returns the iterator to the container's end.
	    virtual GTUIterator<T> end( ) = 0;
		
		//	Returns the constant iterator to the container's beginning.
		virtual GTUIteratorConst<T> cbegin ( ) const = 0;
		
		//	Returns the constant iterator to the container's end.
		virtual GTUIteratorConst<T> cend( ) const = 0;		
		
		// virtual destructor
		virtual ~Iterable ( ) { /*intentionally left empty*/ } 
	};
}

#endif // ITERABLE_H
