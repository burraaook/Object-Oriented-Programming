/*
** hw4_main.cpp:
**
** The test/driver program.
**
** Burak Kocausta 1901042605
** 
*/

#include "dayofyear.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using DayOfYearGTU::DayOfYearSet;
using std::endl;
using std::cout;
using std::vector;
using std::string;

// Function calls objects by reference and changes the objects data.
void callSetsByRef(DayOfYearSet& set1, DayOfYearSet& set2) { 
	DayOfYearSet temp;

	temp = set1;
	set1 = set2;
	set2 = temp;

	set1.add(13,12);
	set2.add(25,2);
}
// Function calls objects by value their data changes inside function but not outside.
void callSetsByValue(DayOfYearSet set1, DayOfYearSet set2) { 
	DayOfYearSet temp;

	temp = set1;
	set1 = set2;
	set2 = temp;

	set1.add(13,12);
	set2.add(25,2);	
}

// Function reads set from days vector and returns it.
// This is for constructor which takes vector parameter.
DayOfYearSet readSetFromVector() {
	vector<DayOfYearSet::DayOfYear> days {DayOfYearSet::DayOfYear(5,6),DayOfYearSet::DayOfYear(15,9),
		DayOfYearSet::DayOfYear(28,2),DayOfYearSet::DayOfYear(),DayOfYearSet::DayOfYear(3,5),DayOfYearSet::DayOfYear(7,7) ,
		DayOfYearSet::DayOfYear(8,6),DayOfYearSet::DayOfYear(9,1),DayOfYearSet::DayOfYear(1,8),DayOfYearSet::DayOfYear(10)
	};

	DayOfYearSet set1(days);			// vector parameter constructor indicated
	return set1;
}

// Function checks De Morgan's Rule.
void checkDeMorgan(DayOfYearSet set1, DayOfYearSet set2) {
	
	if((!(set1+set2)) == (!set1 ^ !set2))
		cout << "De Morgan's Rule satisfied." << endl;
	
	else
		cout << ":("<< endl;			// This line must never printed, if class is well constructed.
}

// Function writes set to a given file name.
// It overwrites.
void WriteSetToFile(const DayOfYearSet& set,const string& filename) { // constant reference
	using std::ofstream;

	ofstream outFile;

	outFile.open(filename);

	if(outFile.is_open()) {
		outFile << set;
		outFile.close();
	}
}

// Function tests each constructor(no parameter, vector parameter, copy constructor)
// It tests add, and remove functions with all their overloadings.
// It tests ^,+,-,!,[],==,!=,=,<< operators.
// It tests size() member function.
// It tests De Morgan's Rule 5 for 5 different sets.
// It tests static function.
// Writes set to a txt file also.
void test1() {
	cout << "_____TEST 1 Started_____" << endl;
	cout << "Total number of days is(none of the objects are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	DayOfYearSet s1,s2;    		// no parameter constructor usage
	s2 = readSetFromVector();   // function to indicate vector parameter constructor

	for(int i = 1; i < 10; ++i) 
		s1.add(i*2,i+1);
	
	cout << "set1: " << endl << s1 << endl;
	cout << "set2(read from vector)---------------: " << endl
	 	 << s2 << endl;

	cout << "Total number of days is(set1, set2 alive)(calling static function) " 
	     << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	if(s1 != s2)			// to indicate inequality operator
		cout << "set1 and set2 are not equal(inequality operator checked)---------------.\n" << endl;
	
	DayOfYearSet s3(s1); 	// copy constructor

	cout << "set3(created with copy constructor set1 is the parameter)---------------: " << endl << s3 << endl;

	cout << "Total number of days is(set1, set2, set3 alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;
	if(s3 == s1)
		cout << "set1 and set3 are equal(copy constructor works fine)---------------.\n" << endl;

	DayOfYearSet s4;

	s4 = s3;	// to indicate assignment operator
	cout << "set4(set3 is assigned to set4)---------------: " << endl << s4 << endl;

	if(s4 == s3) 
		cout << "set4 and set3 are equal(assignment operator works fine)---------------.\n" << endl;

	cout << "Total number of days is(set1, set2, set3, set4 alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	DayOfYearSet s5;

	s5.add(2,11);
	s5.add(9,10);
	s5.add(16,1);
	s5.add(16,1); 	// it won't add, no duplication allowed!
	s5.add(35,15); 	// it won't add, invalid date
	s5.add(12,3);
	s5.add(2,2);
	s5.add(6,7);
	s5.add(9,9);
	
	cout << "\nSet5 Before remove and add operation---------------: \n" << s5 << endl;
	s5.remove();     // removes the last date.
	s5.remove(16,1); // removes the chosen date.
	s5.remove(DayOfYearSet::DayOfYear(2,11)); // it can be removed like that
	s5.add(DayOfYearSet::DayOfYear(3,9));
	s5.add(12,12);
	s5[1] = DayOfYearSet::DayOfYear(5,5);	// testing index operator 

	cout << "Set5 After remove and add operation---------------: \n" << s5 << endl;
 	
 	cout << "Total number of days is(set1, set2, set3, set4, set5 alive)(calling static function) " 
 	     << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	cout << "\nset1: " << endl << s1 << endl;
	{
		DayOfYearSet u1,d1,i1;

		u1 = s5+s1;
		d1 = s1-s5;
		i1 = (s5 ^ s1);

		cout << "Union of set5 and set1 is: " << endl << u1 << endl;
		cout << "set1-set5(difference) is: " << endl << d1 << endl;
		cout << "Intersection of set5 and set1 is: " << endl << i1 << endl;		
	}


	cout << "Intersection of set5 and set5's complement(must be empty, proves complement(!) works fine.---------------: " 
		 << endl << (s5 ^ !s5) << endl;

	cout << "Total number of days in set5 is(using size()) " << s5.size() << endl;
	cout << "Total number of days in complement of set5 is " << (!s5).size() << endl << endl;
 	
  	cout << "Checking De Morgan Rule for set1 and set2: " << endl;
	checkDeMorgan(s1,s2);
	cout << "Checking De Morgan Rule for set2 and set5: " << endl;
	checkDeMorgan(s2,s5);
	cout << "Checking De Morgan Rule for set3 and set1: " << endl;
	checkDeMorgan(s3,s1);
	cout << "Checking De Morgan Rule for set5 and set1: " << endl;
	checkDeMorgan(s5,s1);
	cout << "Checking De Morgan Rule for set5 and set3: " << endl;
	checkDeMorgan(s5,s3);

	WriteSetToFile(!s2,"sampleset.txt");

	cout << "_____TEST 1 END_____" << endl;
}

// Function tests if class can perform call by value, and call by reference.
// It tests de morgan's law again and writes the one of the set to file.
// It tests static value.
void test2() {
	cout << "_____TEST 2 Started_____" << endl;
	cout << "Total number of days is(none of the objects are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;
	
	DayOfYearSet setA,setB;
	
	setA.add(1,1);
	setB.add(3,6);
	setA.add(31,1);
	setA.add(22,4);
	setB.add(30,5);
	setA.add(3,3);
	setA.add(3,3);
	setB.add(3,3);
	setB.add(15,2);
	setA.add(15,2);
	setA.add(28,2);
	setA.add(29,2);
	
	cout << "\n----------------------------Before Calling sets by reference: " << endl
		 << "setA: " << endl << setA << endl
		 << "setB: " << endl << setB << endl;

	cout << "Total number of days is(setA, setB alive)(calling static function) " 
	     << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	callSetsByRef(setA, setB);

	cout << "\n----------------------------After Calling sets by reference: " << endl
		 << "setA: " << endl << setA << endl
		 << "setB: " << endl << setB << endl;

	cout << "Total number of days is(setA, setB alive)(calling static function) " 
	     << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	cout << "\n----------------------------Before Calling sets by value: " << endl
		 << "setA: " << endl << setA << endl
		 << "setB: " << endl << setB << endl;

	cout << "Total number of days is(setA, setB alive)(calling static function) " 
	     << DayOfYearSet::getTotalDOYobjects() << "." << endl;
	
	callSetsByValue(setA, setB);

	cout << "----------------------------After Calling sets by value: " << endl
		 << "setA: " << endl << setA << endl
		 << "setB: " << endl << setB << endl;	
	
	cout << "Total number of days is(setA, setB alive)(calling static function) " 
	     << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	cout << "Capacity of SetA is " << setA.getCapacity()
		 << endl << "Capacity of SetB is " << setB.getCapacity() << endl;

	cout << "Checking De Morgan Rule for setA and setB: " << endl;
	checkDeMorgan(setA,setB);
	WriteSetToFile(setA,"SetA.txt");
	cout << "_____TEST 2 END_____" << endl;
}

// Function tests equality in different ordered equal sets.
// Function tests [] array operator as lval,rval.
void test3() {
	cout << "_____TEST 3 Started_____" << endl;
	cout << "Total number of days is(none of the objects are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;	
	DayOfYearSet setX, setY;

	setX.add(3,5);
	setX.add(1,2);
	setX.add(7,6);
	setX.add(13,3);

	setY.add(13,3);
	setY.add(7,6);
	setY.add(1,2);
	setY.add(3,5);
	
	cout << "\nSetX(printed with index operator)---------------: " << endl;
	for(int i = 0; i < setX.size(); ++i) 
		cout << setX[i] << endl;			// testing index operator

	cout << "\nSetY(printed with index operator)---------------: " << endl;
	for(int i = 0; i < setY.size(); ++i)
		cout << setY[i] << endl;			// testing index operator

	cout << "\nTotal number of days is(SetX,SetY are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;
	
	cout << "\nTesting search member function(isThere)." << endl;
	if(setY.isThere(3,5)) {
		cout << DayOfYearSet::DayOfYear(3,5) << " is inside that set." << endl;	
	}
	if(setY.isThere(12,12) == false) 
		cout << DayOfYearSet::DayOfYear(12,12) << " is not inside that set." << endl;		


	if(setX == setY) 
		cout << "\nSetX and SetY are equal.---------Equality with different order checked." << endl;
	else
		cout << "SetX and SetY are not equal." << endl;

	if(setX + setY == (setY ^ setX)) 
		cout << "Intersection of SetX and SetY are equal with their union.--------------(checked with if condition)" << endl;
	
	cout << "\nDifference of SetX and SetY is(must be empty): \n" << setX - setY << endl;

	DayOfYearSet setZ;

	setZ.add(12,2);
	setZ.add(13,3);
	setZ.add(16,2);
	setZ.add(3,5);
	setZ.add(7,6);
	setZ.add(15,5);

	cout << "SetZ(printed with index operator)--------------: " << endl;
	for(int i = 0; i < setZ.size(); ++i)
		cout << setZ[i] << endl;				// testing index operator
	cout << "Total number of days is(SetX, SetY, SetZ are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	cout << "\nUnion of SetX and SetY and SetZ is: \n" << setX + setY + setZ << endl
		 << "Intersection of SetX and SetY and SetZ is: \n" << ((setX ^ setY) ^ setZ) << endl
		 << "Difference of SetZ and SetX is: \n" << setZ - setX << endl;	
	
	cout << "Checking De Morgan Rule for setX and setY: " << endl;
	checkDeMorgan(setX,setY);
	cout << "Checking De Morgan Rule for setX and setZ: " << endl;
	checkDeMorgan(setX,setZ);
	cout << "Checking De Morgan Rule for setZ and setY: " << endl;
	checkDeMorgan(setZ,setY);

	setX = setX; // self assignment does not crash the program.


	for(int i = 0; i < setZ.size(); ++i) 						// testing array operator for assignment
		setZ[i] = DayOfYearSet::DayOfYear((i+1)*2,(i+1)%11);
	
	cout << "\nSetZ(testing array index operator as lvalue in an assignment)----------: " << endl
		 << setZ << endl;

	cout << "Total number of days is(SetX, SetY, SetZ are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	int sizeZ = setZ.size();
	for(int i = 0; i < sizeZ; ++i)
		setZ.remove();

	cout << "\nSetZ(after emptying the set):" << endl
		 << setZ << endl;

	cout << "Total number of days is(SetX, SetY, SetZ are alive)(calling static function) " 
		 << DayOfYearSet::getTotalDOYobjects() << "." << endl;

	cout << "_____TEST 3 END_____" << endl;
}
int main() {

	test1();
	test2();
	test3();
	return 0;
}