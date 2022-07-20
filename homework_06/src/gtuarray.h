// BURAK KOCAUSTA 1901042605

#ifndef GTUARRAY_H
#define GTUARRAY_H

#include "iterable.h"
#include "gtuiterator.h"
#include "gtuiteratorconst.h"
#include "exceptionsgtu.h"
#include <memory>

namespace IterableGTU
{
	// GTUArrays are fixed-size sequence containers: they hold a specific number of elements ordered in a strict linear sequence.
	// Big Five is defined for this class.
	// Exceptions can be thrown if array,at() exceeds or usage of invalid iterator with erase().
	template < class T, size_t N>
	class GTUArray : public Iterable<T>
	{
	public:

		// No parameter constructor		
		GTUArray ( ) 
		{
			std::shared_ptr<T> temp(new T[N],std::default_delete<T[]>());
			arr_ptr_ = temp;	
		}

		// Copy constructor
		GTUArray (const GTUArray<T,N>& other) 
		{
			std::shared_ptr<T> temp(new T[N],std::default_delete<T[]>());
			arr_ptr_ = temp;
			
			for(size_t i = 0; i < N; ++i)
			{
				arr_ptr_.get()[i] = other.arr_ptr_.get()[i];
			}
		}
		
		// Move constructor
		GTUArray (GTUArray<T,N>&& other) : arr_ptr_(std::move(other.arr_ptr_)) 
		{
			other.arr_ptr_ = nullptr;
		}
		
		// Virtual destructor
		virtual ~GTUArray () {}

		// Copy assignment
		GTUArray<T,N>& operator =(const GTUArray<T,N>& other) 
		{
			for (size_t i = 0; i < N; ++i)
			{
				arr_ptr_.get()[i] = other.arr_ptr_.get()[i];
			}
			
			return *this;		
		}

		// Move assignment
		GTUArray<T,N>& operator =(GTUArray<T,N>&& other) 
		{
			if (this != &other) 
			{
				arr_ptr_ = std::move(other.arr_ptr_);
				other.arr_ptr_ = nullptr;
			}
			return *this;
		}

		virtual bool empty ( ) 
		{
			return (N == 0);
		}

		virtual size_t size ( )
		{
			return N;
		}

		// Assigns the default value of the T to erase it.
		virtual GTUIterator<T> erase (const GTUIterator<T>& position)
		{
			auto flag = false;
			auto it = this->begin();
			for ( ; it != this->end(); ++it)
			{
				if (it == position)
				{
					flag = true;
					*it = T();
					break;
				}
			}
			
			if (!flag)
				throw ExceptionsGTU::InvalidIterator();

			return it;	
		}

		// Assigns the default value of the T to erase it.
		virtual GTUIterator<T> erase (const GTUIterator<T>& first, const GTUIterator<T>& last)
		{
			auto flag = false;
			auto it = this->begin();
			for ( ; it != this->end(); ++it)
			{
				if (it == first)
				{
					int counter = 0;
					auto temp_it = it;

					while (temp_it != last && temp_it != this->end())
					{
						temp_it++; 		counter++;						
					}

					if (last != this->end() && temp_it == this->end()) 
						throw ExceptionsGTU::InvalidIterator();

					if(counter != 0) 
					{
						flag = true;
						int i = 0;
						while (i < counter && it != this->end())
						{
							this->erase(it);
							++i;	++it;
						}						
					}
					break;
				}
			}
			if (!flag)
				throw ExceptionsGTU::InvalidIterator();
			return it;
		}
		virtual void clear ( )
		{
			std::shared_ptr<T> temp(new T[N],std::default_delete<T[]>());
			arr_ptr_ = temp;
			for (size_t i = 0; i < N; ++i)
				arr_ptr_.get()[i] = T();
		}
		virtual GTUIterator<T> begin ( )
		{
			return GTUIterator<T>(arr_ptr_.get());
		}

	    virtual GTUIterator<T> end( )
	    {
	    	return GTUIterator<T>(arr_ptr_.get()+N);
	    }
		virtual GTUIteratorConst<T> cbegin ( ) const
		{
			return GTUIteratorConst<T>(arr_ptr_.get());
		}
		virtual GTUIteratorConst<T> cend( ) const
		{
			return GTUIteratorConst<T>(arr_ptr_.get()+N);
		}

		T& operator[] (size_t index)
		{
			if (index > N)
			{
				throw ExceptionsGTU::OutOfRange();		//throw here
			}
			return arr_ptr_.get()[index];		
		}

		const T& operator[] (size_t index) const
		{
			if (index > N)
			{
				throw ExceptionsGTU::OutOfRange();		//throw here
			}
			return arr_ptr_.get()[index];
		}		

		T& at (size_t index)
		{
			if (index > N)
			{
				throw ExceptionsGTU::OutOfRange();		//throw here
			}
			return arr_ptr_.get()[index];		
		}

		const T& at (size_t index) const
		{
			if (index > N)
			{
				throw ExceptionsGTU::OutOfRange();		//throw here
			}
			return arr_ptr_.get()[index];
		}			
	private:
		std::shared_ptr <T> arr_ptr_;
	};//End of class
}//End of namespace
#endif //GTUARRAY_H