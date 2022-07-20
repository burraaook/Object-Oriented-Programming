// BURAK KOCAUSTA 1901042605

#ifndef GTUVECTOR_H
#define GTUVECTOR_H

#include "iterable.h"
#include "gtuiterator.h"
#include "gtuiteratorconst.h"
#include "exceptionsgtu.h"
#include <memory>

namespace IterableGTU
{
	// GTUVectors are sequence containers representing arrays that can change in size.
	// Big 5 is defined in this class.
	// Exceptions can be thrown if array exceeds or usage of invalid iterator with erase().

	template < class T >
	class GTUVector : public Iterable<T>
	{
	public:

		// No parameter constructor
		GTUVector ( ) : size_(0), capacity_(50)
		{
			std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
			vec_ptr_ = temp;
		}

		// Copy constructor
		GTUVector (GTUVector<T> const& other) : size_(other.size_), capacity_(other.capacity_)
		{
			std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
			vec_ptr_ = temp;			
			for (size_t i = 0; i < size_; ++i)
				vec_ptr_.get()[i] = other.vec_ptr_.get()[i];
		}

		// Move constructor
		GTUVector (GTUVector<T>&& other) : size_(std::move(other.size_)), capacity_(std::move(other.capacity_)), vec_ptr_(std::move(other.vec_ptr_)) 
		{
			other.size_ = 0; 	other.capacity_ = 0;	other.vec_ptr_ = nullptr;		
		}
		
		// Fill Constructor
		explicit GTUVector (size_t size_new) : size_(size_new), capacity_(size_new + 50)
		{
			std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
			vec_ptr_ = temp;
		} 

		// Fill constructor with value
		GTUVector (size_t size_new, const T& val) : size_(size_new), capacity_(size_new + 50)
		{
			std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
			for (decltype(size_) i = 0; i < size_; ++i)
				temp.get()[i] = val;
			vec_ptr_ = temp;
		} 

		// Virtual destructor
		virtual ~GTUVector ( ) {}

		// Copy assignment
		GTUVector<T>& operator =(const GTUVector<T>& other) noexcept
		{
			if (this != &other) 
			{	
				std::shared_ptr<T> temp(new T[other.capacity_],std::default_delete<T[]>());
				vec_ptr_ = temp;

				capacity_ = other.capacity_; 
				size_ = other.size_;

				for (size_t i = 0; i < size_; ++i)
				{
					vec_ptr_.get()[i] = other.vec_ptr_.get()[i];
				}
			}
			return *this;
		}
		
		// Move assignment
		GTUVector<T>& operator =(GTUVector<T>&& other) noexcept
		{
			if (this != &other)		// check self assignment
			{
				vec_ptr_ = std::move(other.vec_ptr_); 	capacity_ = std::move(other.capacity_); 	size_ = std::move(other.size_);
				other.size_ = 0; 	other.capacity_ = 0;	other.vec_ptr_ = nullptr;				
			}

			return *this;
		}

		virtual bool empty ( ) noexcept
		{
			return (size_ == 0);
		}

		virtual size_t size ( ) noexcept {return size_;}

		virtual GTUIterator<T> erase (const GTUIterator<T>& position)
		{
			auto flag = false;
			auto it = this->begin();
			for ( ; it != this->end(); ++it)
			{
				if (it == position)	// if iterator found
				{
					flag = true;
					while (it + static_cast<std::ptrdiff_t>(1) != this->end())	// slide the values
					{
						*it = *(it + static_cast<std::ptrdiff_t>(1));
						++it;
					}
					size_--;
					break;
				}
			}
			if (!flag)
				throw ExceptionsGTU::InvalidIterator();		// throw invalid iterator.
			return it;			
		}

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
					{
						throw ExceptionsGTU::InvalidIterator(); // throw invalid iterator
					}

					if(counter != 0) 
					{
						int i = 0; flag = true;
						while (i < counter && it != this->end())
						{
							this->erase(it);
							++i;			
						}
					}
					break;
				}
			}
			if (!flag)
				throw ExceptionsGTU::InvalidIterator(); // throw invalid iterator

			return it;	
		}

		virtual void clear ( ) noexcept
		{
			size_ = 0;
		}
		virtual GTUIterator<T> begin ( ) noexcept
		{
			return GTUIterator<T>(vec_ptr_.get());
		}

	    virtual GTUIterator<T> end( ) noexcept
	    {
	    	return GTUIterator<T>(vec_ptr_.get()+size_);
	    }

		virtual GTUIteratorConst<T> cbegin ( ) const noexcept
		{
			return GTUIteratorConst<T>(vec_ptr_.get());
		}
		virtual GTUIteratorConst<T> cend( ) const noexcept
		{
			return GTUIteratorConst<T>(vec_ptr_.get()+size_);
		}

		T& operator[] (size_t index)			// lvalue
		{
			if (index > size_)
			{
				throw ExceptionsGTU::OutOfRange();
			}
			return vec_ptr_.get()[index];		
		}

		const T& operator[] (size_t index) const  // rvalue
		{
			if (index > size_)
			{
				throw ExceptionsGTU::OutOfRange();
			}
			return vec_ptr_.get()[index];			
		}

		void add (const T& val) noexcept
		{
			if(size_ < capacity_-1)				// check if capacity is full.
				vec_ptr_.get()[size_] = val;
			else
			{
				capacity_ += 50;
				std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
				
				for(size_t i = 0; i < size_; ++i)
					temp.get()[i] = vec_ptr_.get()[i];
				temp.get()[size_] = val;

				vec_ptr_ = temp;
			}
			size_++;	
		}

		void add (T&& val) noexcept 	// stole the resources of val(move).
		{
			if (size_ < capacity_-1)
				vec_ptr_.get()[size_] = std::move(val);
			else
			{
				capacity_ += 50;
				std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
				
				for(size_t i = 0; i < size_; ++i)
					temp.get()[i] = vec_ptr_.get()[i];
				temp.get()[size_] = std::move(val);

				vec_ptr_ = temp;
			}
			size_++;		
		}
	private:
		std::shared_ptr <T> vec_ptr_;
		size_t size_;
		size_t capacity_;
	};//End of class
}//End of namespace
#endif // GTUVECTOR_H