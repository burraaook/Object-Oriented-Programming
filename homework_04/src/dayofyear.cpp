/*
** dayofyear.cpp:
**
** The implementation file is created for implementing DayofYearSet class functions.
**
** Burak Kocausta 1901042605
** 
*/
#include "dayofyear.h"
#include <cstdlib>

using std::istream;
using std::ostream;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

int DayOfYearGTU::DayOfYearSet::totalDOYobjects = 0;	// Static object to hold total number of dates in all objects.

namespace 	// unnamed namespace for helper functions.
{
	using DayOfYearGTU::DayOfYearSet;

	// Checks if date is valid or not.
	bool checkDate(int day, int month) {
		auto ans = true;
		if(day > 0 && month > 0 && month <= 12 && day <= 31) 
		{
			switch(month) 
			{
				case 1:
				case 3:
				case 5:
				case 7:
				case 8:
				case 10:
				case 12:
					if(day > 31) ans = false;	
					break;
				case 2:
					if(day > 28) ans = false;	
					break;
				default:
					if(day > 30) ans = false;	
					break;
			}
		}
		else
			ans = false;
		return ans;
	}

	// Swaps the given elements values.
	void swapElements(DayOfYearSet::DayOfYear& first, DayOfYearSet::DayOfYear& second) {
		DayOfYearSet::DayOfYear temp;

		temp = first;
		first = second;
		second = temp;
	}
}// End of unnamed namespace.

namespace DayOfYearGTU 
{
	// assign 1 to month automatically.
	DayOfYearSet::DayOfYear::DayOfYear(int day) : month_(1) {
		if(checkDate(day,month_)) day_ = day;

		// if date is not valid terminate the program.
		else{		
			 cerr << "ERROR! Day must between 1 and 30(included). Terminating..." << endl;
			 exit(1);
		}
	}

	DayOfYearSet::DayOfYear::DayOfYear(int day, int month) {
		
		if(checkDate(day,month)) {	// Check date's validity.	
			day_ = day;
			month_ = month;
		}
		else {
			cerr << "ERROR! Invalid date entered. Object cannot be constructed! Terminating..." << endl;
		 	exit(1);
		}
	}

	void DayOfYearSet::DayOfYear::setDate(int day, int month) {
		if(checkDate(day,month)) {	// Check date's validity.
			day_ = day;
			month_ = month;			
		}
		else 						// do not terminate the program.
			cerr << "ERROR! Invalid date entered. Values cannot be assigned." << endl;		 	
	}
	bool DayOfYearSet::DayOfYear::operator ==(const DayOfYear& other) const {
		return ((other.month_ == month_) && (other.day_ == day_));
	}
	bool DayOfYearSet::DayOfYear::operator !=(const DayOfYear& other) const {
		return !(*this == other);	// equality operator already defined.
	}
	ostream& operator <<(ostream& ons,const DayOfYearSet::DayOfYear& date) {
		ons << date.getDay() << " ";
		switch(date.getMonth())			// Print month name properly.
		{
			case 1:
				ons << "January"; break;
			case 2:
				ons << "February"; break;
			case 3:
				ons << "March"; break;
			case 4:
				ons << "April"; break;
			case 5:
				ons << "May"; break;
			case 6:
				ons << "Jun"; break;
			case 7:
				ons << "July"; break;
			case 8:
				ons << "August"; break;
			case 9:
				ons << "September"; break;
			case 10:
				ons << "October"; break;
			case 11:
				ons << "November"; break;
			case 12:
				ons << "December"; break;
		}
		return ons;
	}

	// 50 is automatically assigned to capacity.
	DayOfYearSet::DayOfYearSet() : capacity_(50) {
		days_ = new DayOfYear[capacity_];
		used_ = 0;
	}
 	DayOfYearSet::DayOfYearSet(vector<DayOfYear> days) {

		capacity_ = 50;						// maximum is 365
		days_ = new DayOfYear[capacity_];
		used_ = 0;
		auto sizeVec = days.size();

		for(decltype(sizeVec) i = 0; i < sizeVec; ++i) 
			add(days[i]);	// It handles duplication
 	}
 	DayOfYearSet::~DayOfYearSet() {
 	 	totalDOYobjects -= used_;	// before dying, decrement total number of dayOfYear object.
 	 	delete [] days_;
 	}
 	DayOfYearSet::DayOfYearSet(const DayOfYearSet& other) : used_(other.size()), capacity_(other.getCapacity()) {
 		days_ = new DayOfYear[capacity_];
 		totalDOYobjects += used_;
 		for(int i = 0; i < used_; ++i)		// copy the constructor information without copying the address.
 			days_[i] = other.days_[i];
 	}

 	// It can handle self assignment
 	DayOfYearSet& DayOfYearSet::operator =(const DayOfYearSet& other) {

		if(capacity_ != other.capacity_){   // it also checks (this == &other)
			delete [] days_;
			days_ = new DayOfYear[other.capacity_];

		}
		totalDOYobjects -= used_;			// decrement total
		capacity_ = other.capacity_;
		used_ = other.used_;
		totalDOYobjects += used_;			// increment total

		for(decltype(used_) i = 0; i < used_; ++i)
			days_[i] = other.days_[i];
		
		return *this; // or return other 		
 	}
 	ostream& operator <<(ostream& ons, const DayOfYearSet& daySet) {

 		if(daySet.used_ == 0) {
 			ons << "This is an empty set." << endl;
 			return ons;
 		}
 		ons << "There are " << daySet.used_ << " dates in this set. Dates are:" << endl;
 		
 		for(int i = 0; i < daySet.used_; ++i) 
 			ons << daySet.days_[i] << endl; // it is already overloaded for DayOfYear class, so this can be done.

 		return ons;
 	}
	bool DayOfYearSet::operator ==(const DayOfYearSet& other) const {
		auto ans = true;

		if(used_ == other.used_) // check their size first
		{
			for(decltype(used_) i = 0; i < used_ && ans; ++i) {
				auto flag = false;
				for(decltype(i) j = 0; j < other.used_ && !flag; ++j) // they don't have to be ordered same, so compare from start.
				{
					if(days_[i] == other.days_[j])
						flag = true;
				}
				if(!flag) ans = false;
			}
		}
		else
			ans = false;

		return ans;
	}
	bool DayOfYearSet::operator !=(const DayOfYearSet& other) const {
		return !(*this == other);				// equality operator is already assigned use it.
	}

	const DayOfYearSet DayOfYearSet::operator +(const DayOfYearSet& other) const {
		DayOfYearSet unionSet = other;

		for(decltype(used_) i = 0; i < used_; ++i) 
				unionSet.add(days_[i]);		// It handles duplication.
		
		return unionSet;
	}
	const DayOfYearSet DayOfYearSet::operator -(const DayOfYearSet& other) const {
		DayOfYearSet differenceSet;

		for(decltype(used_) i = 0; i < used_; ++i) {
			auto flag = true;
			for(decltype(i) j = 0; j < other.used_ && flag; ++j) // check if element is inside other.
				if(days_[i] == other.days_[j])
					flag = false;
			
			if(flag) 
				differenceSet.add(days_[i]);	// if it is not inside other, add it. 
		}
		return differenceSet;
	}
	const DayOfYearSet DayOfYearSet::operator ^(const DayOfYearSet& other) const {
		DayOfYearSet intersectionSet;

		for(decltype(used_) i = 0; i < used_; ++i) {
			auto flag = true;
			for(decltype(i) j = 0; j < other.used_ && flag; ++j) // find the same dates, and add it to the array.
				if(days_[i] == other.days_[j])
					flag = false;
			
			if(!flag) 
				intersectionSet.add(days_[i]);			// If it is found, add it.
		}

		return intersectionSet;
	}
	const DayOfYearSet DayOfYearSet::operator !() const {
		DayOfYearSet complementSet;
			
			for(decltype (used_) month = 1; month <= 12; ++month) {

				for(decltype(used_) day = 1; day <= 31; ++day) 
					if(checkDate(day,month) && !isThere(day,month) ) // Check the dates validity, and if it is inside current object.
						complementSet.add(day,month);		
			}	
		
		return complementSet;		// return the complement set.
	}

	DayOfYearSet::DayOfYear& DayOfYearSet::operator [](int index) {
		if(index < used_)
			return days_[index];	// return wanted date.
		cerr << index << " is bigger than this sets size! Segmentation fault preveneted. Terminating..." << endl;
		exit(1);	
	}

	void DayOfYearSet::add(const DayOfYear& newDay) {
		for(decltype(used_) i = 0; i < used_; ++i) {	// If array includes the date, return.
			if(days_[i] == newDay)
				return;
		}

		if(used_ >= capacity_){					// If capacity is filled, make reallocation.

			capacity_ += 20;
			DayOfYear *temp = new DayOfYear[capacity_];

			for(decltype(used_) i = 0; i < used_; ++i)
				temp[i] = days_[i];

			delete [] days_;					// delete old array.
			days_ = temp;						// point to the new address.
		}

		days_[used_] = newDay;
		used_++;
		totalDOYobjects++;					// increment the total object number.
	}
	void DayOfYearSet::add(const int& day, const int& month) {
		if(checkDate(day,month)) // check the dates validity.
			add(DayOfYear(day, month));
	}
	void DayOfYearSet::remove() {	// directly remove the last object.
		if(used_ > 0){
			used_--;
			totalDOYobjects--;
		}
	}
	void DayOfYearSet::remove(const DayOfYear& newDay) {
		for(decltype(used_) i = 0; i < used_; ++i) {

			if(days_[i] == newDay) 		// search the given date.
			{
				for(auto j = i; j+1 < used_; ++j)
					swapElements(days_[j], days_[j+1]);		// glide all elements to right.
				used_--;
				totalDOYobjects--;
				break;
			}
		}
	}
	void DayOfYearSet::remove(const int& day, const int& month) {

		if(checkDate(day,month)) 
			remove(DayOfYear(day, month));	// anonymous object can be sent as a parameter here.
	}
	bool DayOfYearSet::isThere(const int& day, const int& month) const {
		for(decltype(used_) i = 0; i < used_; ++i) {
			if(days_[i].getDay() == day && days_[i].getMonth() == month)	// if date is found return true.
				return true;
		}
		return false;
	}
	int DayOfYearSet::getTotalDOYobjects() {return totalDOYobjects;}		// return the total number of all day of year objects.
}//End of DayOfYearGTU namespace.

