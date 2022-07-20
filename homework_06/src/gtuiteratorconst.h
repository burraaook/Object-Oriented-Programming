// Burak Kocausta 1901042605

#ifndef GTUITERATORCONST_H
#define GTUITERATORCONST_H

#include <memory>
#include "baseiterator.h"

namespace IterableGTU
{
	// An iterator class which is derived from BaseIterator.
	// This is random access iterator.
	// All necessary operator overloadings done.
	template <class T>
	class GTUIteratorConst : public BaseIterator<std::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&>
	{
	public:
		
		GTUIteratorConst ( ) : itr_pt(nullptr) {}
		GTUIteratorConst (const GTUIteratorConst<T>& other) : itr_pt(other.itr_pt) {}
		GTUIteratorConst (T* other) : itr_pt(other) {}
		~GTUIteratorConst ( ) {}
		
		GTUIteratorConst<T>& operator = (const GTUIteratorConst& other) 
		{
			itr_pt = other.itr_pt; return *this;
		}
		
		GTUIteratorConst<T>& operator =(GTUIteratorConst* other)	
		{
			itr_pt = other;	return (*this);
		}
		
		const T& operator * ( ) {return *itr_pt;}
		
		const T* operator -> ( ) {return itr_pt;}
		
		GTUIteratorConst<T> operator ++ ( ) 
		{
			++itr_pt; return *this;
		}
		
		GTUIteratorConst<T> operator ++ (int dummy) 	
		{
			GTUIteratorConst<T> temp = itr_pt; 
			++itr_pt; 
			return temp;
		}
		
		GTUIteratorConst<T> operator -- ( ) 	
		{
			--itr_pt; 	return *this;
		}
		
		GTUIteratorConst<T> operator -- (int dummy) 
		{
			GTUIteratorConst<T> temp = itr_pt; 
			--itr_pt; 
			return temp;
		}
		
		GTUIteratorConst<T>&  operator +=(const std::ptrdiff_t& mvar)	
		{
			itr_pt += mvar; 	return (*this);
		}
		
		GTUIteratorConst<T>&  operator -=(const std::ptrdiff_t& mvar)	
		{
			itr_pt -= mvar; 	return (*this);
		}			
		
		GTUIteratorConst<T> operator - (const std::ptrdiff_t& mvar) 
		{
			auto tmp_pt = itr_pt;	itr_pt -= mvar;  auto temp(*this); itr_pt = tmp_pt;	return temp;
		}
		GTUIteratorConst<T> operator + (const std::ptrdiff_t& mvar) 
		{
			auto tmp_pt = itr_pt; itr_pt += mvar; auto temp(*this); itr_pt = tmp_pt; return temp;
		}
		std::ptrdiff_t operator -(const GTUIteratorConst<T>& other)	{return std::distance(other.itr_pt,itr_pt);}
		
		operator bool ( )	const	{return itr_pt != nullptr;}
		
		bool operator == (const GTUIteratorConst<T>& other) const {return itr_pt == other.itr_pt;}
		
		bool operator != (const GTUIteratorConst<T>& other) const	{return !(*this == other); }
	protected:
		T* itr_pt;
	};	
}

#endif //GTUITERATORCONST_H