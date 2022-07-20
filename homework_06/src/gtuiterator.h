	
#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include <memory>
#include "baseiterator.h"

namespace IterableGTU
{
	// An iterator class which is derived from BaseIterator.
	// This is random access iterator.
	// All necessary operator overloadings done.
	template < class T >
	class GTUIterator : public BaseIterator<std::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&>
	{
	public:

		GTUIterator ( ) : itr_pt(nullptr) {}
		GTUIterator (const GTUIterator<T>& other) : itr_pt(other.itr_pt) {}
		GTUIterator (T* other) : itr_pt(other) {}
		~GTUIterator ( ) {}
		
		GTUIterator<T>& operator = (const GTUIterator& other) 
		{
			itr_pt = other.itr_pt; return *this;
		}
		
		GTUIterator<T>& operator =(GTUIterator* other)	
		{
			itr_pt = other;	return (*this);
		}
		
		T& operator * ( ) {return *itr_pt;}
		
		T* operator -> ( ) {return itr_pt;}
		
		GTUIterator<T> operator ++ ( ) 
		{
			++itr_pt; return *this;
		}
		
		GTUIterator<T> operator ++ (int dummy) 	
		{
			GTUIterator<T> temp = itr_pt; 
			++itr_pt; 
			return temp;
		}
		
		GTUIterator<T> operator -- ( ) 	
		{
			--itr_pt; 	return *this;
		}
		
		GTUIterator<T> operator -- (int dummy) 
		{
			GTUIterator<T> temp = itr_pt; 
			--itr_pt; 
			return temp;
		}
		
		GTUIterator<T>&  operator +=(const std::ptrdiff_t& mvar)	
		{
			itr_pt += mvar; 	return (*this);
		}
		
		GTUIterator<T>&  operator -=(const std::ptrdiff_t& mvar)	
		{
			itr_pt -= mvar; 	return (*this);
		}			
		
		GTUIterator<T> operator - (const std::ptrdiff_t& mvar) 
		{
			auto tmp_pt = itr_pt;	itr_pt -= mvar;  auto temp(*this); itr_pt = tmp_pt;	return temp;
		}		
		GTUIterator<T> operator + (const std::ptrdiff_t& mvar) 
		{
			auto tmp_pt = itr_pt; itr_pt += mvar; auto temp(*this); itr_pt = tmp_pt; return temp;
		}	
		std::ptrdiff_t operator -(const GTUIterator<T>& other)	{return std::distance(other.itr_pt,itr_pt);}
		
		operator bool ( )	const	{return itr_pt != nullptr;}
		
		bool operator == (const GTUIterator<T>& other) const {return itr_pt == other.itr_pt;}
		
		bool operator != (const GTUIterator<T>& other) const	{return !(*this == other); }

	protected:
		T* itr_pt;
	};	
}
	
#endif //GTUITERATOR_H