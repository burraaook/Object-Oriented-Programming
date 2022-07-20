// BURAK KOCAUSTA 1901042065

#ifndef GTUSET_H
#define GTUSET_H

#include "iterable.h"
#include "gtuiterator.h"
#include "gtuiteratorconst.h"
#include "exceptionsgtu.h"
#include <memory>
#include <algorithm>

namespace IterableGTU
{
	// GTUSets are containers that store unique elements following a specific order.
	// Big 5 is defined in this class.
	// Exceptions can be thrown WİTH usage of invalid iterator with erase().
	template <class T>
	class GTUSet : public Iterable<T>
	{
	public:

		// No parameter constructor		
		GTUSet ( ) : size_(0), capacity_(50) 
		{
			std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
			set_ptr_ = temp;			
		}

		// Copy constructor
		GTUSet (const GTUSet<T>& other) : size_(other.size_), capacity_(other.capacity_)
		{
			std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
			set_ptr_ = temp;			
			for (size_t i = 0; i < size_; ++i)
				set_ptr_.get()[i] = other.set_ptr_.get()[i];
		}
		
		// Move constructor
		GTUSet (GTUSet<T>&& other) : size_(std::move(other.size_)), capacity_(std::move(other.capacity_)), set_ptr_(std::move(other.set_ptr_))
		{
			other.set_ptr_ = nullptr;	other.size_ = 0;	other.capacity_ = 0;
		}

		// Virtual destructor
		virtual ~GTUSet ( ) { }

		// Copy assignment
		GTUSet<T>& operator =(const GTUSet<T>& other)  noexcept
		{
			if (this != &other) 
			{	
				std::shared_ptr<T> temp(new T[other.capacity_],std::default_delete<T[]>());
				set_ptr_ = temp;

				capacity_ = other.capacity_; 
				size_ = other.size_;
				for (size_t i = 0; i < size_; ++i)
				{
					set_ptr_.get()[i] = other.set_ptr_.get()[i];
				}
			}
			return *this;
		}
		
		// Move assignment
		GTUSet<T>& operator =(GTUSet<T>&& other) noexcept
		{
			if (this != &other) // checking self assignment.
			{
				set_ptr_ = other.set_ptr_; 	capacity_ = other.capacity_; 	size_ = other.size_;
				other.set_ptr_ = nullptr;	other.size_ = 0;	other.capacity_ = 0;			
			}

			return *this;	
		}

		virtual bool empty ( ) noexcept
		{
			return (size_ == 0);
		}

		virtual size_t size ( ) noexcept
		{
			return size_;
		}

		virtual size_t erase (const T& val) noexcept
		{
			for (decltype(size_) i = 0; i < size_; ++i) 
			{
				if (set_ptr_.get()[i] == val)
				{
					while (i + 1 < size_)
					{
						set_ptr_.get()[i] = set_ptr_.get()[i+1];	++i;
					}
					size_--;
				}
			}
			return size_;		
		} 		
		
		virtual GTUIterator<T> erase (const GTUIterator<T>& position)
		{
			auto flag = false;
			auto it = this->begin();
			for ( ; it != this->end(); ++it)
			{
				if (it == position)	// iterator found
				{
					flag = true;
					while (it + static_cast<std::ptrdiff_t>(1) != this->end())	// slide the values.
					{
						*it = *(it + static_cast<std::ptrdiff_t>(1));
						++it;
					}
					size_--;
					break;
				}
			}
			if (!flag)
				throw ExceptionsGTU::InvalidIterator(); // throw invalid iterator.

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
						throw ExceptionsGTU::InvalidIterator(); // throw invalid iterator.
					
					if(counter != 0) 
					{
						int i = 0;	flag = true;
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
				throw ExceptionsGTU::InvalidIterator(); // throw invalid iterator.

			return it;			
		}
		virtual void clear ( ) {size_ = 0;}

		virtual GTUIterator<T> begin ( ) noexcept
		{
			return GTUIterator<T>(set_ptr_.get());
		}

	    virtual GTUIterator<T> end( ) noexcept
	    {
	    	return GTUIterator<T>(set_ptr_.get() + size_);
	    }

		virtual GTUIteratorConst<T> cbegin ( ) const
		{
			return GTUIteratorConst<T>(set_ptr_.get());
		}

		virtual GTUIteratorConst<T> cend( ) const
		{
			return GTUIteratorConst<T>(set_ptr_.get() + size_);
		}

		GTUIterator<T> search (const T& val) noexcept
		{
			for (auto it = this->begin(); it != this->end(); ++it)
			{
				if (*it == val)
				{
					return it;
				}
			}
			return this->begin();
		}

		void add (const T& val) noexcept
		{
			for (decltype(size_) i = 0; i < size_; ++i)
			{
				if (set_ptr_.get()[i] == val) return;
			}

			if(size_ >= capacity_-1)		// check if capacity is full.
			{
				capacity_ += 50;	
				std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
				for(int i = 0; i < size_; ++i)
					temp.get()[i] = set_ptr_.get()[i];
				set_ptr_ = temp;				
			}
			set_ptr_.get()[size_] = val;
			size_++;
			std::sort(this->begin(),this->end());	
		}
		
		void add (T&& val) noexcept			// stole the resources of val(move).
		{
			for (decltype(size_) i = 0; i < size_; ++i)
			{
				if (set_ptr_.get()[i] == val) return;
			}

			if(size_ >= capacity_-1)
			{
				capacity_ += 50;	
				std::shared_ptr<T> temp(new T[capacity_],std::default_delete<T[]>());
				for(int i = 0; i < size_; ++i)
					temp.get()[i] = set_ptr_.get()[i];
				set_ptr_ = temp;				
			}
			set_ptr_.get()[size_] = std::move(val);
			size_++;
			std::sort(this->begin(),this->end());			
		}

		void deleteElement (const T& val) noexcept
		{
			this->erase(val);
		}

		GTUSet<T> intersect (const GTUSet<T>& other) noexcept
		{
			GTUSet<T> intersectionSet;

			for(decltype(size_) i = 0; i < size_; ++i) 
			{
				auto flag = true;
				for (decltype(i) j = 0; j < other.size_ && flag; ++j) 	// find the same dates, and add it to the array.
					if (set_ptr_.get()[i] == other.set_ptr_.get()[j])
						flag = false;
				
				if(!flag) 
					intersectionSet.add(set_ptr_.get()[i]);				// If it is found, add it.
			}

			return intersectionSet;
		}

		GTUSet<T> unionSet (const GTUSet<T>& other) noexcept
		{
			GTUSet<T> unionSet = other;

			for(decltype(size_) i = 0; i < size_; ++i) 
					unionSet.add(set_ptr_.get()[i]);			// It handles duplication.
			
			return unionSet;
		}
	private:
		std::shared_ptr<T> set_ptr_;
		size_t size_;
		size_t capacity_;
	}; //End of class
}//End of namespace
#endif //GTUSET_H