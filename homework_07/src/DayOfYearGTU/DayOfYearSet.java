package DayOfYearGTU;
import java.util.ArrayList; // used as constructor parameter.

/**
* A class which represents a set of DayOfYear objects.
* It can dynamically shrink and grow.
* Every element is unique.
* @author Burak Kocausta
* @version 1.0 (03/01/2022)
*/
public class DayOfYearSet
{
	/**
	* A class which holds date information as integers(day_f, month_f).
	* @author Burak Kocausta
	* @version 1.0 (03/01/2022)
	*/
	public static class DayOfYear
	{
		private int day_f;
		private int month_f;

		/**
		* No parameter constructor.	
		* day and month will assigned to 1 by default.
		*/
		public DayOfYear ( )
		{
			this(1,1);
		}

		/**
		* DayOfYear constructor which takes 2 parameter.
		* @param day day parameter.
		* @param month month parameter.	
		*/		
		public DayOfYear( int day, int month )
		{
			if ( checkDate( day, month ) ) 
			{
				this.day_f = day;
				this.month_f = month;
			}
			else
			{
				System.out.println( "Invalid date is entered! Date is set to default(1,1).\n" );
				day_f = 1;
				month_f = 1;
			}
		}

		/**
		* Sets the given date. If parameters aren't valid, it does nothing. 
		* setDate constructor which takes 2 parameter.
		* @param day day parameter.
		* @param month month parameter.	
		*/			
		public void setDate ( int day, int month )
		{
			if ( checkDate( day, month) )
			{
				this.day_f = day;
				this.month_f = month;
			}
		}

		/**
		* Simple getter which returns the day_f.
		* @return returns the day as an integer.
		*/			
		public int getDay( )
		{
			return day_f;
		}
		
		/**
		* Simple getter which returns the month_f.
		* @return returns the month as an integer.
		*/	
		public int getMonth( )
		{
			return month_f;
		}

		/**
		* Overriden toString method.
		* @return returns string as formatted properly(Ex: "1 February").
		*/
		@Override
		public String toString ( )
		{
			String day;

			switch ( this.getMonth() )			// Print month name properly.
			{
				case 1:
					day = "January"; break;
				case 2:
					day = "February"; break;
				case 3:
					day = "March"; break;
				case 4:
					day = "April"; break;
				case 5:
					day = "May"; break;
				case 6:
					day = "Jun"; break;
				case 7:
					day = "July"; break;
				case 8:
					day = "August"; break;
				case 9:
					day = "September"; break;
				case 10:
					day = "October"; break;
				case 11:
					day = "November"; break;
				case 12:
					day = "December"; break;
				default:
					day = "-"; break;
			}
			return String.format( "%-2d %-11s", day_f, day);
		}

		/**
		* Overriden equals method.
		* @param other must be DayOfYear class object.
		* @return returns true if dates are equal, otherwise false.
		*/
		@Override
		public boolean equals (Object other)
		{
			if (other != null && other instanceof DayOfYear)
			{
				final DayOfYear otherDate = (DayOfYear) other;
				if (this.day_f == otherDate.day_f && this.month_f == otherDate.month_f)
					return true;
				else
					return false;
			}

			return false;
		}

	}// End Of DayOfYear class

	private static int totalDOYObjects = 0;	
	private DayOfYear[] days_f;
	private int used_f;
	
	/**
	* No parameter constructor.
	*/
	public DayOfYearSet ( )
	{

		DayOfYear[] temp = new DayOfYear[50];
		this.days_f = temp;

		for ( int i = 0; i < this.used_f; ++i)
		{
			this.days_f[i] = new DayOfYear();
		}
		this.used_f = 0;
	}
	
	/**
	* Constructor takes ArrayList of DayOfYear objects.
	* @param days includes DayOfYear Objects, and its size shouldn't exceed 365.
	*/	
	public DayOfYearSet ( ArrayList<DayOfYear> days )
	{
		if ( days != null && days.size() <= 365 )
		{
			DayOfYear[] temp = new DayOfYear[days.size()];
			this.days_f = temp;
			this.used_f = 0;
			for ( var date : days)
			{
				this.days_f[this.used_f] = new DayOfYear( date.getDay(), date.getMonth() );
				this.used_f++;
			}
			totalDOYObjects += this.used_f;
		}
		else
		{
			System.out.println( "Invalid ArrayList is entered! Terminating...\n" );
			System.exit(1);
		}
	}
	
	/**
	* Copy Constructor that takes DayOfYearSet object.
	* @param other instance of the same class.
	*/		
	public DayOfYearSet ( DayOfYearSet other )
	{
		if ( other != null)
		{
			this.used_f = other.used_f;
			DayOfYear[] temp = new  DayOfYear[other.days_f.length];
			days_f = temp;
			for ( int i = 0; i < this.used_f; ++i)
				this.days_f[i] = new DayOfYear( other.days_f[i].getDay(), other.days_f[i].getMonth() );

			totalDOYObjects += this.used_f;
		}
		else
		{
			System.out.println( "null object cannot be used in copy constructor! Terminating...\n" );
			System.exit(1);
		}
	}

	/**
	* Overriden toString method.
	* Returns the string which has the DayOfYearSet details, which are number of elements in the set, and each date(Ex: 1 February).
	* @return returns string as formatted properly(Ex: "1 February").
	*/
	@Override
	public String toString ( ) 
	{

		if ( this.used_f == 0)
		{
			return String.format ( "DayOfYearSet is empty.\n" );
		}

		String days = new String();
		days = String.format ( "There are %d dates are in this DayOfYearSet object. Dates are: \n", this.used_f);
		for (int i = 0; i < this.used_f; ++i)
		{
			days += String.format ("%s\n", this.days_f[i]);
		}

		return days;	
	}

	/**
	* Overriden equals method.
	* Sets doesn't have to be ordered same, but their elements must be equal.
	* @param other must be DayOfYearSet class object.
	* @return returns true if sets are equal, otherwise false.
	*/
	@Override
	public boolean equals ( Object other )
	{
		if ( other != null && other instanceof DayOfYearSet )
		{
			final DayOfYearSet otherSet = (DayOfYearSet) other;

			if ( this.used_f == otherSet.used_f )
			{
				for ( int i = 0; i < this.used_f; ++i )
				{
					var flag = false;
					for ( int j = 0; j < this.used_f && !flag; ++j)
					{
						if ( this.days_f[i].equals(otherSet.days_f[j]) )	// they don't have to be ordered same, so compare from start.
							flag = true;					
					}
					if ( !flag )
						return false;
				}
				return true;
			}
		}
		return false;
	}

	/**
	* Method takes DayOfYear object, and adds it to the array.
	* If capacity is full it dynamically increases its size.
	* It handles the duplication, there is no duplication every element is unique.
	* @param date DayOfYear class which holds day and month information.
	*/	
	public void add ( DayOfYear date )
	{
		if (date != null)
		{
			for ( int i = 0; i < this.used_f; ++i )	// If array includes the date, return.
			{	
				if(date.equals(this.days_f[i]))
					return;
			}

			if ( this.used_f >= this.days_f.length )		// If capacity is filled, make reallocation.
			{					
				var tempLen = this.days_f.length;
				tempLen += 15;
				DayOfYear[] temp = new DayOfYear[tempLen];

				for ( int i = 0; i < this.used_f; ++i )
					temp[i] = new DayOfYear( this.days_f[i].getDay(), this.days_f[i].getMonth() );

				days_f = temp;						// point to the new address.
			}
			this.days_f[used_f] = new DayOfYear( date.getDay(), date.getMonth() );
			this.used_f++;
			totalDOYObjects++;					// increment the total object number.			
		}
		
	}

	/**
	* Method takes day and month information, checks validity and adds to array.
	* If capacity is full it dynamically increases its size.
	* It handles the duplication, there is no duplication every element is unique.
	* @param day day information, february is assumed 28 day.
	* @param month month information.
	*/	
	public void add ( int day, int month)
	{
		if ( checkDate(day, month) )
		{
			var temp = new DayOfYear(day, month);
			this.add( temp );
		}
	}

	/**
	* Method pops the last date.
	*/	
	public void remove ( )
	{
		if(this.used_f > 0)
		{
			this.used_f--;
			totalDOYObjects--;
		}		
	}

	/**
	* Method removes the given date.
	* @param date DayOfYear class parameter.
	*/
	public void remove ( DayOfYear date )
	{
		for ( int i = 0; i < this.used_f; ++i )
		{
			if ( days_f[i].equals(date) )
			{
				for ( var j = i; j + 1 < this.used_f; ++j) // slide all elements
				{
					var temp = new DayOfYear( days_f[j].getDay(), days_f[j].getMonth() );
					days_f[j].setDate( days_f[j+1].getDay(), days_f[j+1].getMonth() );
					days_f[j+1].setDate( temp.getDay(), temp.getMonth() );
				}
				this.used_f--;
				totalDOYObjects--;
				break;
			}
		}
	}

	/**
	* Method removes the given date.
	* @param day an integer day information.
	* @param month an integer month information.
	*/
	public void remove ( int day, int month )
	{
		if (this.used_f > 0)
			this.remove ( new DayOfYear(day, month) );
	}

	/**
	* Method returns the total number of dates.
	* @return returns an integer.
	*/
	public int size ( )
	{
		return used_f;
	}

	/**
	*	Simple getter which returns DayOfYear array.  
	*	@return DayOfYear array will be returned.
	*/ 
	public DayOfYear[] getDays ( )
	{
		return days_f;
	}
	/**
	* Static method of DayOfYearSet class which returns total number of DayOfYearObject alive.
	* @return returns an integer.
	*/	
	public static int getTotalDOYObjects ( )
	{
		return totalDOYObjects;
	}

	/**
	* A method which returns union set of two sets.
	* Example set1.union(set2) it returns set1+set2(in terms of set arithmetic).
	* @param other same instance must be argument.
	* @return returns the union set(DayOfYearSet).
	*/ 
	public DayOfYearSet union ( DayOfYearSet other )
	{
		if (other != null)
		{
			var unionSet = new DayOfYearSet(other);

			for ( int i = 0; i < this.used_f; ++i )
			{
				unionSet.add(this.days_f[i]);
			}
			return unionSet;
		}
		return other;
	}

	/**
	* A method which returns difference of two sets.
	* Example set1.difference(set2) it returns set1-set2(in terms of set arithmetic). 
	* @param other same instance must be argument.
	* @return returns the difference set(DayOfYearSet).
	*/ 
	public DayOfYearSet difference ( DayOfYearSet other )
	{
		if (other != null)
		{
			var differenceSet = new DayOfYearSet();
			for ( int i = 0; i < this.used_f; ++i )
			{
				var flag = true;

				for ( int j = 0; j < other.used_f && flag; ++j ) // check if element is inside other.
					if (this.days_f[i].equals(other.days_f[j]))
						flag = false;
				
				if(flag) 
					differenceSet.add(this.days_f[i]);	// if it is not inside other, add it. 
			}
			return differenceSet;
		}
		return other;
	}

	/**
	* A method which returns intersection of two sets.
	* Example set1.intersection(set2) it returns set1^set2(in terms of set arithmetic). 
	* @param other same instance must be argument.
	* @return returns the intersection set(DayOfYearSet).
	*/ 
	public DayOfYearSet intersection ( DayOfYearSet other )
	{
		if (other != null)
		{
			var intersectionSet = new DayOfYearSet();

			for( int i = 0; i < this.used_f; ++i ) 
			{
				var flag = true;
				
				for( int j = 0; j < other.used_f && flag; ++j ) 	// find the same dates, and add it to the array.
					if( this.days_f[i].equals(other.days_f[j]) )
						flag = false;
				
				if(!flag) 
					intersectionSet.add( days_f[i] );				// If it is found, add it.			
			}
			return intersectionSet;
		}
		return other;		
	}

	/**
	* A method which returns complement of the set.
	* Example set1.complement() it returns !set1(in terms of set arithmetic). 
	* @return returns the complement set(DayOfYearSet).
	*/ 
	public DayOfYearSet complement ( )
	{
		var complementSet = new DayOfYearSet();
			
		for ( int month = 1; month <= 12; ++month )
		{
			for( int day = 1; day <= 31; ++day ) 
				if( checkDate(day,month) && !isElement(day,month) ) // Check the dates validity, and if it is inside current object.
					complementSet.add(day,month);
		}	
		
		return complementSet;		// return the complement set.		
	}

	/**
	* A private static method which checks the validity of the given date.
	* Assumes February is 28 day.
	* @param day day parameter.
	* @param month month parameter.
	* @return true if date is valid, false if it is not valid.	
	*/	
	private static boolean checkDate( int day, int month ) 
	{
		var ans = true;
		if ( day > 0 && month > 0 && month <= 12 && day <= 31 ) 
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
			}//End Of switch.
		}
		else
			ans = false;
		return ans;
	}
	/**
	* A private method checks if given date is in the set.
	* @param day day parameter.
	* @param month month parameter.
	* @return true if date is in the set, otherwise false.	
	*/	
	private boolean isElement ( int day, int month )
	{
		for( int i = 0; i < this.used_f; ++i) 
		{
			if( days_f[i].equals( new DayOfYear(day, month) ) )		// if date is found return true.
				return true;
		}
		return false;
	}
}
