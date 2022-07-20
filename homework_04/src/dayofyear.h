/*
** dayofyear.h:
**
** The header file is created for class interface.
**
** Burak Kocausta	1901042605
*/

#ifndef DAYOFYEAR_H
#define DAYOFYEAR_H

#include <iostream>
#include <vector>

using std::istream;
using std::ostream;
using std::vector;

namespace DayOfYearGTU				// All class data is encapsulated in DayOfYearGTU
{
	// Class holds dayOfYear pointer for days of year set(no duplication) with its functions and necessary data(capacity,used).
	class DayOfYearSet
	{
	public:

		// Class holds day and month data(starts from 1) in private.
		// There are no pointers in this inner class.
		class DayOfYear
		{
		public:
			// No need to big three in this inner class

			DayOfYear() {day_ = 1; month_ = 1;} 	// No parameter inlined constructor
			DayOfYear(int day);
			DayOfYear(int day, int month);

			// Checks equality of two DayOfYear object.
			bool operator ==(const DayOfYear& other) const;
			// Checks inequality of two DayOfYear object.
			bool operator !=(const DayOfYear& other) const;

			// Prints the day_ and month_ properly(Ex: 1 January).
			friend ostream& operator <<(ostream& ons, const DayOfYear& date); // stream insertion

			int getDay() const {return day_;}		// Getters
			int getMonth() const {return month_;}

			void setDate(int day, int month);		// Setter
		private:
			int day_;
			int month_;
		};//End of DayOfYear

		// No Parameter constructor, creates dayOfYear pointer and sets capacity to 50.
		DayOfYearSet();

		// Vector parameter constructor, reads vector and fill data properly.
		DayOfYearSet(vector<DayOfYear> days);

		// Big three
		DayOfYearSet(const DayOfYearSet& other); 				// Copy Constructor		
		DayOfYearSet& operator =(const DayOfYearSet& other);	// It can handle self assignment.
		~DayOfYearSet();								  		// Destructor

		// Stream insertion prints number of days and each date properly.
		friend ostream& operator <<(ostream& ons, const DayOfYearSet& daySet);
		
		// Equality operator checks date by date.
		// Objects are not have to be ordered same(It does set comparing).
		bool operator ==(const DayOfYearSet& other) const;
		bool operator !=(const DayOfYearSet& other) const;

		// It returns union set(no duplication)
		const DayOfYearSet operator +(const DayOfYearSet& other) const;

		// It returns difference of two sets.
		const DayOfYearSet operator -(const DayOfYearSet& other) const;

		// It returns intersection of two sets(use it with paranthesis, because ^ can create precedence problem).
		const DayOfYearSet operator ^(const DayOfYearSet& other) const;

		// It returns complement set.
		const DayOfYearSet operator !() const;

		// It returns indexed date.
		// Function can be used as left value and right value.
		DayOfYear& operator [](int index);

		// It adds new date, by taking dayOfYear object.
		void add(const DayOfYear& newDay); 	// no duplication

		// It adds new date, by taking day and month value(start from 1).
		void add(const int& day, const int& month);

		// Function removes the last date.
		void remove();

		// Function removes according to the given dayofyear object.
		void remove(const DayOfYear& newDay);

		// Function removes according to the day and month information.
		void remove(const int& day, const int& month);

		// Getters
		int size() 	const	{return used_;}
		int getCapacity() const{return capacity_;}
		
		// Function checks if given date is in array.
		bool isThere(const int& day, const int& month) const;

		// Static function returns the total number of DayOfYear objects(inside all sets) during runtime.
		static int getTotalDOYobjects();
	private:
		DayOfYear* days_;			// Holds the date.
		int used_;					// Number of dates.
		int capacity_;				// Capacity of the array.
		static int totalDOYobjects;	// Total number of DayOfYear objects.
	}; // End of DayOfYearSet
}//End of namespace
#endif