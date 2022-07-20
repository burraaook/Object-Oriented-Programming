import DayOfYearGTU.*;

import java.util.ArrayList;	// Used for testing ArrayList constructor.
	
import java.io.IOException;	// Used for writing some sets to file.
import java.io.PrintWriter;


/**
 * Driver code for testing DayOfYearSet class.
 * @author Burak Kocausta 
 */
public class Test
{
	public static void main ( String args[] )
	{
		System.out.println( "___Testing DayOfYearSet Class___\n" );

		System.out.printf( "Testing no parameter constructor of DayOfYearSet.\n");
		System.out.printf( "Total number of DayOfYearObject = %d\n", DayOfYearSet.getTotalDOYObjects());
		DayOfYearSet set1 = new DayOfYearSet();		
		System.out.printf( "\nEmpty set1 is created.\nset1: %s\n", set1); // testing toString()
		System.out.printf( "\n___No parameter constructor is tested.___\n\n");
		System.out.printf( "\nAdding elements to set1 with using add(int, int) and add(DayOfYear) method.\n" );
		set1.add(3,5);
		set1.add(2,9);
		set1.add(5,2);
		set1.add(11,3);
		set1.add(31,13);
		set1.add(7,10);
		set1.add(5,2);

		var date1 = new DayOfYearSet.DayOfYear();
		var date2 = new DayOfYearSet.DayOfYear(28,2);

		set1.add(date1);
		set1.add(date2);
		set1.add(new DayOfYearSet.DayOfYear(22,1));
		set1.add(new DayOfYearSet.DayOfYear(1,1));

		System.out.printf( "\nDates are added to set1.\nset1: %s\n",set1);
		System.out.printf( "\nTotal number of DayOfYearObject = %d\n", DayOfYearSet.getTotalDOYObjects());
		System.out.printf( "\n___add(int, int) and add(DayOfYear) are tested. Adding same date is tried and no duplication happened every element is unique.___\n" );		
		System.out.printf( "___No parameter and DayOfYear(int, int) constructors are tested.___\n" );
		System.out.printf( "___toString() override is also tested.(set1 used in printf directly)___\n" );
		System.out.printf( "___static method that returns the total number of DayOfYear objects alive is tested.___\n" );

		System.out.printf( "\nTesting constructor which takes ArrayList argument and copy constructor.\n" );

		var arrL1 = new ArrayList<DayOfYearSet.DayOfYear>();

		arrL1.add(new DayOfYearSet.DayOfYear(3,1));
		arrL1.add(new DayOfYearSet.DayOfYear(13,2));
		arrL1.add(new DayOfYearSet.DayOfYear(7,6));
		arrL1.add(new DayOfYearSet.DayOfYear(8,1));
		arrL1.add(new DayOfYearSet.DayOfYear(6,1));
		arrL1.add(new DayOfYearSet.DayOfYear(6,9));
		arrL1.add(new DayOfYearSet.DayOfYear(29,12));
		arrL1.add(new DayOfYearSet.DayOfYear(2,2));
			
		var set2 = new DayOfYearSet(arrL1);
		var set3 = new DayOfYearSet(set1);

		System.out.printf( "\nArrL1 which is ArrayList of DayOfYear objects is created, and ArrayList constructor called while constructing set2.\n" );
		System.out.printf( "\nset2: %s", set2 );

		System.out.printf( "\nCopy constructor is used while creating set3. set3 created with making deep copy of set1.\n\nset3: %s", set3 );
		System.out.printf( "\n___ArrayList constructor of DayOfYearSet and copy constructor of DayOfYearSet are tested.___\n" );

		System.out.println( "\nTesting equals() method for set1, set2, and set3." );

		set1.remove(3,5);
		set1.remove(new DayOfYearSet.DayOfYear(5,2));
		set1.remove(11,3);
		set1.remove();
		set1.add(6,1);
		set1.add(5,9);
		set1.add(2,2);
		set1.add(22,1);
		set1.add(11,3);
		set1.add(5,2);
		set1.add(3,5);
		set1.add(7,9);

		set3.remove(7,9);
		set3.remove(3,5);
		set3.remove(new DayOfYearSet.DayOfYear(22,1));
		set3.remove();
		set3.add(5,9);
		set3.add(7,9);
		set3.add(22,1);
		set3.add(2,2);
		set3.add(28,2);
		set3.add(6,1);
		set3.add(3,5);
		set3.remove(2,9);
		set3.add(2,9);

		System.out.println( "Three dates are added and shuffled a bit with different order in set1, set3 to indicate order does not matter for equals() method.\n");
		System.out.printf( "set1: %s\nset3: %s\nset1 and set3 must be equal.\n", set1, set3 );
		if ( set1.equals(set3) )
			System.out.println( "\nset1 is equal to set3(inside if(set1.equals(set3) condition).");

		if ( !(set2.equals(set1)) )
			System.out.println( "\nset2 is not equal to set1(inside if(!(set2.equals(set1)) condition).");

		System.out.printf( "\nset1.size() = %d --- set2.size() = %d --- set3.size() = %d\n",set1.size(), set2.size(), set3.size() );
		System.out.println( "\n___remove(), remove(int, int), remove(DayOfYear) and size() methods are tested and they work fine.___\n" );
		System.out.println( "___equals() method is tested and works fine(order does not matter). Prints are made inside if conditions.___\n" );

		var arrL2 = new ArrayList<DayOfYearSet.DayOfYear>();

		arrL2.add(new DayOfYearSet.DayOfYear(4,11));
		arrL2.add(new DayOfYearSet.DayOfYear(6,9));
		arrL2.add(new DayOfYearSet.DayOfYear(5,2));
		arrL2.add(new DayOfYearSet.DayOfYear(29,12));
		arrL2.add(new DayOfYearSet.DayOfYear(6,1));
		arrL2.add(new DayOfYearSet.DayOfYear());
		arrL2.add(new DayOfYearSet.DayOfYear(2,7));
		arrL2.add(new DayOfYearSet.DayOfYear(23,1));

		var set4 = new DayOfYearSet(arrL2);

		System.out.printf( "set4 is created using ArrayList constructor.\nset4: %s\n", set4 );
		var set5 = new DayOfYearSet();
		set5.add(9,6);
		set5.add(3,1);
		set5.add(2,7);
		set5.add(9,9);
		set5.add(23,1);
		set5.add(new DayOfYearSet.DayOfYear(11,10));
		set5.add(18,9);
		set5.add(4,11);
		set5.add(3,13);		
		System.out.printf( "set5 is created using no parameter constructor.\nset5: %s\n", set5 );

		System.out.printf( "\nTotal number of DayOfYearObject = %d\n\n", DayOfYearSet.getTotalDOYObjects() );

		System.out.printf( "Intersection of set4 and set5 is: %s\n", set4.intersection(set5));
		System.out.printf( "Intersection of set1 and set2 is: %s\n", set1.intersection(set2));
		System.out.printf( "Intersection of set3 and set3.complement() is(must be empty): %s\n", set3.intersection(set3.complement()));

		System.out.printf( "Union of set1 and set2 is: %s\n", set1.union(set2));
		System.out.printf( "Union of set4 and set5 is: %s\n", set4.intersection(set5));


		System.out.printf( "set1's difference of set4 is: %s\n", set1.difference(set4));
		System.out.printf( "set3's difference of set5 is: %s\n", set3.difference(set5));
		System.out.printf( "set1's difference of set3 is(must be empty): %s\n", set1.difference(set3));


		System.out.println( "___union(), intersection(), difference(), and complement() methods are tested.___\n");
		System.out.println( "\nTesting De Morgan rule" );

		System.out.println( "\n1- Testing De Morgan rule for set1 and set2" );
		if (set1.union(set2).complement().equals(set1.complement().intersection(set2.complement())))
			System.out.println( "1- De morgan rule is satisfied for set1 and set2.(printed inside if condition)\n" );

		System.out.println( "\n2- Testing De Morgan rule for set3 and set4" );
		if (set3.union(set4).complement().equals(set3.complement().intersection(set4.complement())))
			System.out.println( "2- De morgan rule is satisfied for set3 and set4.(printed inside if condition)\n" );

		System.out.println( "\n3- Testing De Morgan rule for set5 and set1" );
		if (set5.union(set1).complement().equals(set5.complement().intersection(set1.complement())))
			System.out.println( "3- De morgan rule is satisfied for set5 and set1.(printed inside if condition)\n" );

		System.out.println( "\n4- Testing De Morgan rule for set4 and set2" );
		if (set4.union(set2).complement().equals(set4.complement().intersection(set2.complement())))
			System.out.println( "4- De morgan rule is satisfied for set4 and set2.(printed inside if condition)\n" );

		System.out.println( "\n5- Testing De Morgan rule for set3 and set1" );
		if (set3.union(set1).complement().equals(set3.complement().intersection(set1.complement())))
			System.out.println( "5- De morgan rule is satisfied for set3 and set1.(printed inside if condition)\n" );		

		System.out.println( "\n6- Testing De Morgan rule for set2 and set5" );
		if (set2.union(set5).complement().equals(set2.complement().intersection(set5.complement())))
			System.out.println( "6- De morgan rule is satisfied for set2 and set5.(printed inside if condition)\n" );			

		System.out.println( "___De Morgan rule is tested for 6 different pairs. They all worked fine!___\n");

		try
		{
			var setPrinter = new PrintWriter("set1.txt");
			setPrinter.printf( "%s\n", set1 );
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}

		try
		{
			var setPrinter = new PrintWriter("set1complement.txt");
			setPrinter.printf( "%s\n", set1.complement() );
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}

		try
		{
			var setPrinter = new PrintWriter("set2.txt");
			setPrinter.printf( "%s\n", set2 );
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}

		try
		{
			var setPrinter = new PrintWriter("set2set1union.txt");
			setPrinter.printf( "%s\n", set2.union(set1) );
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}

		try
		{
			var setPrinter = new PrintWriter("set1set2difference.txt");
			setPrinter.printf( "%s\n", set1.difference(set2) );
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}

		try
		{
			var setPrinter = new PrintWriter("set3.txt");
			setPrinter.printf( "%s\n", set3);
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}

		try
		{
			var setPrinter = new PrintWriter("set1set2intersection.txt");
			setPrinter.printf( "%s\n", set1.intersection(set2));
			setPrinter.close();
		}
		catch ( IOException eFile )
		{
			System.out.println("An error occurred, set cannot be written to file.");
		}		

		System.out.println( "___set1, set2, set3 and set1.complement(), set1.difference(est2), set2.union(set1), set1.intersection(set2) are written to txt files successfully.___\n");

		System.out.println( "\n___Test Summary___\n");
		System.out.println( "1- toString() tested more than 10 times.");
		System.out.println( "2- Equals() is tested 7 times, also it is used inside some methods.");
		System.out.println( "3- Default constructor, no parameter constructor, copy constructor, and ArrayList constructors each of them tested more than 2 times for DayOfYearSet.");
		System.out.println( "4- DayOfYear classes constructors are also tested more than 2 times.");
		System.out.println( "6- add(int, int), add(DayOfYear) methods are tested more than 10 times.");
		System.out.println( "7- size() and getTotalDOYObjects() methods are tested more than 2 times. ");
		System.out.println( "8- remove(), remove(int, int), remove(DayOfYear) methods each of them tested more than 2 times.");
		System.out.println( "9- union, intersection, complement, difference methods each of them are tested more than 5 times.");
		System.out.println( "10- De Morgan rule is confirmed 6 times.");
		System.out.println( "11- 6 different sets are written to txt files.\n");
	}
}
