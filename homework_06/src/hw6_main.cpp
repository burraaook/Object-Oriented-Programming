
// BURAK KOCAUSTA 1901042605
// Driver code for testing containers.

#include "iterable.h"
#include "baseiterator.h"
#include "gtuiterator.h"
#include "gtuiteratorconst.h"
#include "gtuvector.h"
#include "gtuset.h"
#include "gtuarray.h"
#include "exceptionsgtu.h"
#include <algorithm>
#include <iostream>
#include <string>

// GTUVector test functions.
void testVector1 ( );
void testExceptionVector ( );
void testSTLFunctionsVector ( );

template <class T>
void printGTUVector(IterableGTU::GTUVector<T> vec) {

	for (auto it = vec.cbegin(); it != vec.cend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

// GTUSet test functions.
void testSet1 ( );
void testExceptionSet ( );
void testSTLFunctionsSet ( );

template<class T>
void printGTUSet(IterableGTU::GTUSet<T> gtuset) {
	for (auto it = gtuset.cbegin(); it != gtuset.cend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

// GTUArray test functions.
void testArray1 ( );
void testExceptionArray ( );
void testSTLFunctionsArray ( );

template<class T, size_t N>
void printGTUArray(IterableGTU::GTUArray<T,N> arr) {
	for (auto it = arr.cbegin(); it != arr.cend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}


int main ( ) {

	testVector1();
	testSet1();
	testArray1(); 

	return 0;
}


void testVector1 ( ) {
	std::ptrdiff_t k = 2;

	std::cout << "\n___Testing GTUVector class___\n\n";

	std::cout << "\nTesting No parameter constructor for integer type.\n";
	IterableGTU::GTUVector<int> vec1;
	vec1.add(5);
	vec1.add(3);
	vec1.add(8);
	std::cout << "Object is constructed fine. add() function also works fine.\nvec1 : ";
	printGTUVector(vec1);
	std::cout << "\nTesting Copy constructor.\n";
	IterableGTU::GTUVector<int> vec2(vec1);
	std::cout << "Object is constructed fine.\nvec2(copy of vec1) : ";
	printGTUVector(vec2);
	std::cout << "cbegin() end cend() member functions works fine(used while printing).\n";

	std::cout << "\nTesting fill constructor with different type(double).\n";
	IterableGTU::GTUVector<double> vec3(7);
	std::cout << "Object is constructed fine.\nvec3(double): ";
	printGTUVector(vec3);

	std::cout << "\nTesting other fill constructor which takes 2 parameter with another class(std::string).\n";
	IterableGTU::GTUVector<std::string> vec4(6,"apple");
	std::cout << "Object is constructed fine.\nvec4: ";
	printGTUVector(vec4);

	std::cout << "\nTesting move constructor with anonymous object for string type.\n";
	IterableGTU::GTUVector<std::string> vec5(std::move(IterableGTU::GTUVector<std::string>(5,"tomato")));
	std::cout << "Anonymous objects resources are stolen well.\nvec5: ";
	printGTUVector(vec5);

	std::cout << "\nTesting assignment operator(vec4 = vec5).\n";
	vec4 = vec5;
	std::cout << "Assignment done well.\nvec4: ";
	printGTUVector(vec4);

	std::cout << "\nTesting move assingment operator for vec3(double).\n";

	IterableGTU::GTUVector<double> tempVec(3,22);
	std::cout << "\nTemporary object is created.\ntempVec : ";
	printGTUVector(tempVec);

	vec3 = std::move(tempVec);
	std::cout << "Temporary object's resources are stolen well(vec3 = std::move(tempVec).\nvec3: ";
	printGTUVector(vec3);

	std::cout << "\nMove assignment is tested.\n";

	std::cout << "\nTesting [] operator for vec1 as lvalue.\n";

	for (int i = 0; i < vec1.size(); ++i)
		vec1[i] = i*2 + 1;
	std::cout << "vec1 : ";
	
	for (auto x : vec1) std::cout << x << " ";
	std::cout << "\noperator [] works fine as lvalue(vec1's values are changed). Printed with ranged based for loop.\n";
	
	std::cout << "\nTesting [] operator for vec3 as rvalue.\nvec3: ";

	for (size_t i = 0; i < vec3.size(); ++i)
		std::cout << vec3[i] << " ";
	std::cout << "\noperator [] works fine as rvalue.\n";

	std::cout << "\nTesting erase() functions and range based for loop.\n";
	IterableGTU::GTUVector<char> vec6;
	vec6.add('a');
	vec6.add('c');
	vec6.add('k');
	vec6.add('7');
	vec6.add('!');

	std::cout << "Before erasing first element\nvec6(char): ";
	for (auto x: vec6) std::cout << x << " ";

	vec6.erase(vec6.begin( ));
	
	std::cout << "\n\nAfter calling vec6.erase(vec6.begin())\nvec6: ";
	for (auto x: vec6) std::cout << x << " ";

	vec6.erase(vec6.begin(),vec6.begin()+k);
	std::cout << "\n\nAfter calling vec6.erase(vec.begin(), vec.begin()+2)\nvec6: ";
	for (auto x: vec6) std::cout << x << " ";

	vec6.clear();
	std::cout << "\nAfter calling vec6.clear( )\nsize = " << vec6.size();
	if(vec6.empty() == true)
		std::cout << "\nvec6 is empty(vec6.empty() is being called)\n";

	std::cout << "\nbegin(), clear(), size(), empty(), range based for loop, erase() and its overloaded version works fine.\n";

	testSTLFunctionsVector();
	testExceptionVector();
	std::cout << "\n_____All GTUVector classes functions, STL library functions, and exceptions are tested.___\n";
}
void testExceptionVector ( ) {
	
	std::cout << "\nTesting GTUVector exceptions.\n";

	try 
	{
		IterableGTU::GTUVector<int> vec7(5,30),vec8(3,20);
		std::cout << "vec7: ";
		for(auto x: vec7) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
		std::cout << "trying to access vec7[6].\n";
		vec7[6];
		
		auto it = vec7.begin();
		vec8.erase(it);
			for(auto x: vec8) {
			std::cout << x << " ";
		}
	}

	catch (ExceptionsGTU::InvalidIterator &iteratorException) 
	{
		std::cerr << "exception: " << iteratorException.what() << std::endl;
	}

	catch (ExceptionsGTU::OutOfRange &outOfRangeException)
	{
		std::cerr << "exception: " << outOfRangeException.what() << std::endl;
	}

	catch (...)
	{
		std::cerr << "exception: Some error occured.\n";
	}

	try 
	{
		IterableGTU::GTUVector<int> vec9(5,30),vec10(3,20);
		std::cout << "vec9: ";
		for(auto x: vec9) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
	
		auto it = vec9.begin();
		std::cout << "trying to erase invalid iterator.\n";
		vec10.erase(it);
			for(auto x: vec10) {
			std::cout << x << " ";
		}		
	}

	catch (ExceptionsGTU::InvalidIterator &iteratorException) 
	{
		std::cerr << "exception: " << iteratorException.what() << std::endl;
	}

	catch (ExceptionsGTU::OutOfRange &outOfRangeException)
	{
		std::cerr << "exception: " << outOfRangeException.what() << std::endl;
	}

	catch (...)
	{
		std::cerr << "exception: Some error occured.\n";
	}

	std::cout << "All exceptions are tested.\n";	
}

void testSTLFunctionsVector ( ) {

	std::cout << "\nTesting vec for std::sort.\n";
	IterableGTU::GTUVector<int> vec;

	vec.add(3);
	vec.add(5);
	vec.add(4);
	vec.add(2);
	vec.add(13);
	vec.add(1);
	vec.add(7);
	vec.add(6);
	vec.add(22);
	vec.add(3);
	vec.add(3);
	vec.add(8);

	std::cout << "Before\nvec: ";
	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	
	std::sort(vec.begin(),vec.end());
	std::cout << "\nAfter calling std::sort(vec.begin(),vec.end())\nvec: ";

	for (auto it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";

	
	std::cout << "\nAfter calling std::sort(vec.begin(), vec.end(), std::greater<int>())\nvec: ";
	std::sort(vec.begin(), vec.end(), std::greater<int>());
	
	for (auto x : vec)
		std::cout << x << " ";
	std::cout << std::endl;

	std::cout << "\nstd::sort works fine, end() works fine and iterators are tested.\n";

	std::cout << "\nTesting vec for std::find function.\n";

	auto itr = std::find(vec.begin(), vec.end(),1);

	std::cout << "After auto itr = std::find(vec.begin(), vec.end(),1); statement\n";
	std::cout << "*itr = " << *itr << std::endl;

	std::cout << "std::find is tested.\n";
	
	std::cout << "\nTesting std::for_each\n";
	 
	auto print = [](const int& x) { std::cout << x << " "; };
	std::cout << "\nbefore(will be printed with std::for_each)\nvec: ";
	
	std::for_each(vec.cbegin(), vec.cend(), print);

	std::cout << "\nafter(incrementing with std::for_each)\nvec: ";

	std::for_each(vec.begin(), vec.end(), [](int &x){ x++; });
	std::for_each(vec.cbegin(), vec.cend(), print);
	std::cout << "\nstd::for_each is tested and works fine.\n";
}


void testSet1 ( ) {
	std::cout << "\n___Testing GTUSet class___\n\n";

	std::cout << "\nTesting No parameter constructor for integer type.\n";
	IterableGTU::GTUSet<int> set1;
	set1.add(5);
	set1.add(3);
	set1.add(8);
	set1.add(11);
	set1.add(3);
	set1.add(2);
	std::cout << "Object is constructed fine. add() function also works fine, and it is automatically ordered.\nset1 : ";
	printGTUSet(set1);
	std::cout << "\nDuplication is tested(3 added twice) and every element is unique.\n";
	std::cout << "\nTesting Copy constructor.\n";

	IterableGTU::GTUSet<int> set2(set1);
	std::cout << "Object is constructed fine.\nset2(copy of set1) : ";
	printGTUSet(set2);
	std::cout << "cbegin() end cend() member functions works fine(used while printing).\n";


	std::cout << "\nTesting move constructor with std::string.\n";
	IterableGTU::GTUSet<std::string> temp1;
	temp1.add("apple");
	temp1.add("tomato");
	temp1.add("banana");
	std::cout << "\ntemp1: ";
	printGTUSet(temp1);

	IterableGTU::GTUSet<std::string> set4(std::move(temp1));

	std::cout << "\nafter moving temp1's resources to set4.\nset4: ";
	printGTUSet(set4);
	std::cout << "temp1's resources are stolen well. Move constructor works fine\n";

	IterableGTU::GTUSet<std::string> set3;
	set3.add("onion");
	set3.add("bread");
	std::cout << "\nset3 created\nset3: ";
	printGTUSet(set3);
	set3 = set4;
	std::cout << "\nTesting assignment operator(set3 = set4).\nset3: ";
	printGTUSet(set3);
	std::cout << "Assignment done well.\n";

	IterableGTU::GTUSet<double> set5;
	set5.add(2.1);
	set5.add(3.3);
	set5.add(5.2);
	set5.add(1.1);
	std::cout << "\nTesting move assignment operator for set5(double).\nset5: ";
	printGTUSet(set5);

	IterableGTU::GTUSet<double> tempSet;
	tempSet.add(1.3);
	tempSet.add(2.2);
	tempSet.add(5.2);
	std::cout << "\nTemporary object is created.\ntempSet : ";
	printGTUSet(tempSet);

	set5 = std::move(tempSet);
	std::cout << "Temporary object's resources are stolen well.(set5 = std::move(tempSet)\nset5: ";
	printGTUSet(set5);

	std::cout << "\nMove assignment is tested and works fine.\n";
	std::cout << "\nTesting erase() functions and range based for loop.\n";
	IterableGTU::GTUSet<char> set6;
	set6.add('a');
	set6.add('c');
	set6.add('k');
	set6.add('7');
	set6.add('!');
	set6.add('U');
	set6.add('5');

	std::cout << "Before\nset6(char): ";
	for (auto x: set6) std::cout << x << " ";

	set6.erase(set6.search('c'));
	std::ptrdiff_t k = 2;
	std::cout << "\n\nAfter calling set6.erase(set6.search('c'))\nset6: ";
	for (auto x: set6) std::cout << x << " ";

	set6.erase(set6.begin(),set6.begin()+k);
	std::cout << "\n\nAfter calling set6.erase(set.begin(), set.begin()+2)\nset6: ";
	for (auto x: set6) std::cout << x << " ";

	set6.erase('U');
	std::cout << "\n\nAfter calling set6.erase('U')\nset6: ";
	for (auto x: set6) std::cout << x << " ";

	set6.deleteElement('5');
	std::cout << "\n\nAfter calling set6.deleteElement('5')\nset6: ";
	for (auto x: set6) std::cout << x << " ";

	set6.clear();
	std::cout << "\nAfter calling set6.clear( )\nsize = " << set6.size();
	if (set6.empty() == true)
		std::cout << "\nset is empty.(testing set6.empty())";

	std::cout << "\nbegin(),search(), clear(), size(), empty(), deleteElement(), range based for loop, erase() and its overloaded versions works fine.\n";

	std::cout << "\nAdding elements to set6 again.\nset6: ";
	set6.add('a');
	set6.add('c');
	set6.add('k');
	set6.add('7');
	set6.add('!');
	set6.add('U');
	set6.add('5');
	
	for (auto x: set6)
		std::cout << x << " ";

	IterableGTU::GTUSet<char> set7;
	set7.add('b');
	set7.add('m');
	set7.add('U');
	set7.add('6');
	set7.add('5');
	set7.add('c');
	set7.add('8');
	std::cout << "\nset7: ";
	for (auto x: set7)
		std::cout << x << " ";

	std::cout << "\nunion(set6,set7): ";

	for (auto x: set6.unionSet(set7))
		std::cout << x << " ";

	std::cout << "\nintersection(set6,set7): ";

	for (auto x: set6.intersect(set7))
		std::cout << x << " ";
	std::cout << "\nunion and intersect functions are tested." <<std::endl;
	testSTLFunctionsSet();
	testExceptionSet();
	std::cout << "\n_____All GTUSet classes functions, STL library functions, and exceptions are tested.___\n";
}

void testSTLFunctionsSet ( ) {
	std::cout << "\nTesting set8 for std::sort.\n";
	IterableGTU::GTUSet<int> set8;

	set8.add(3);
	set8.add(5);
	set8.add(4);
	set8.add(2);
	set8.add(13);
	set8.add(1);
	set8.add(7);
	set8.add(6);
	set8.add(22);
	set8.add(3);
	set8.add(3);
	set8.add(8);

	std::cout << "Before\nset8: ";
	for (auto it = set8.begin(); it != set8.end(); ++it)
		std::cout << *it << " ";
	
	std::sort(set8.begin(),set8.end());
	std::cout << "\nAfter calling std::sort(set8.begin(),set8.end())\nset8: ";

	for (auto it = set8.begin(); it != set8.end(); ++it)
		std::cout << *it << " ";

	
	std::cout << "\nAfter calling std::sort(set8.begin(), set8.end(), std::greater<int>())\nset8: ";
	std::sort(set8.begin(), set8.end(), std::greater<int>());
	
	for (auto x : set8)
		std::cout << x << " ";
	std::cout << std::endl;

	std::cout << "\nstd::sort works fine, end() works fine and iterators are tested.\n";

	std::cout << "\nTesting set8 for std::find function.\n";

	auto itr = std::find(set8.begin(), set8.end(),1);

	std::cout << "After auto itr = std::find(set8.begin(), set8.end(),1); statement\n";
	std::cout << "*itr = " << *itr << std::endl;

	std::cout << "std::find is tested.\n";
	
	std::cout << "\nTesting std::for_each\n";
	 
	auto print = [](const int& x) { std::cout << x << " "; };
	std::cout << "\nbefore(will be printed with std::for_each)\nset8: ";
	
	std::for_each(set8.cbegin(), set8.cend(), print);

	std::cout << "\nafter(incrementing with std::for_each)\nset8: ";

	std::for_each(set8.begin(), set8.end(), [](int &x){ x++; });
	std::for_each(set8.cbegin(), set8.cend(), print);
	std::cout << "\nstd::for_each is tested and works fine.\n";
}

void testExceptionSet ( ) {
	std::cout << "\nTesting exceptions for GTUSet class.\n";
	try 
	{
		IterableGTU::GTUSet<int> set1, set2;

		set1.add(3);
		set1.add(5);
		set1.add(6);

		set2.add(3);
		set2.add(5);
		std::cout << "sample set: ";
		for(auto x: set1) 
		{
			std::cout << x << " ";
		}
		std::cout << std::endl;
		
		auto it = set1.begin();
		
		std::cout << "Trying to erase invalid iterator.\n";
		set2.erase(it);
		for(auto x: set2) 
		{
			std::cout << x << " ";
		}		
	}

	catch (ExceptionsGTU::InvalidIterator &iteratorException) 
	{
		std::cerr << "exception: " << iteratorException.what() << std::endl;
	}

	catch (ExceptionsGTU::OutOfRange &outOfRangeException)
	{
		std::cerr << "exception: " << outOfRangeException.what() << std::endl;
	}

	catch (...)
	{
		std::cerr << "exception: Some error occured.\n";
	}	
}

void testArray1 ( ) {
	std::cout << "\n___Testing GTUArray class___\n\n";

	std::cout << "\nTesting No parameter constructor for integer type.\n";
	IterableGTU::GTUArray<int,4> arr1;
	arr1[0] = 3;
	arr1[1] = 5;
	arr1[2] = 6;
	arr1[3] = 8;

	std::cout << "Object is constructed fine. operator [] works fine as lvalue.\narr1 : ";
	printGTUArray(arr1);
	std::cout << "\nTesting Copy constructor.\n";
	
	IterableGTU::GTUArray<int,4> arr2(arr1);
	std::cout << "Object is constructed fine.\narr2(copy of arr1) : ";
	printGTUArray(arr2);
	std::cout << "cbegin() end cend() member functions works fine(used while printing).\n";

	IterableGTU::GTUArray<std::string,5> tempArr;
	
	tempArr[0] = "tomato";
	tempArr[1] = "apple";
	tempArr[2] = "car";
	tempArr[3] = "bread";
	tempArr[4] = "happy";

	
	std::cout << "\nTesting move constructor.\ntempArr(string): ";
	printGTUArray(tempArr);

	IterableGTU::GTUArray<std::string,5> arr3(std::move(tempArr));
	std::cout << "After calling the move constructor for arr3.\narr3: ";
	printGTUArray(arr3);
	std::cout << "\ntempArr's resources are stolen.Move constructor tested.\n";



	std::cout << "\nTesting assignment operator(arr3 = arr4).\n";
	
	IterableGTU::GTUArray<std::string,5> arr4;

	arr4[0] = "coin";
	arr4[1] = "house";
	arr4[2] = "black";
	arr4[3] = "nine";
	arr4[4] = "movie";

	std::cout << "\narr4: ";
	for (auto x: arr4)
		std::cout << x << " ";

	arr3 = arr4;
		
	std::cout << "\narr3: ";
	for (auto x: arr3)
		std::cout << x << " ";	

	std::cout << "\nAssignment done well.\n";

	IterableGTU::GTUArray<double,5> tempArr2;
	tempArr2[0] = 3.1;
	tempArr2[1] = 2.6;
	tempArr2[2] = 7.1;
	tempArr2[3] = 2.2;
	tempArr2[4] = 8.3;
	IterableGTU::GTUArray<double,5> arr5;

	std::cout << "\nTesting move assingment operator for arr5(double).\ntempArr2: ";
	for (auto x: tempArr2)
		std::cout << x << " ";	

	arr5 = std::move(tempArr2);

	std::cout << "\nAfter the move assingment arr5 = std::move(tempArr2)\narr5: ";
	for (auto x: arr5)
		std::cout << x << " ";		

	std::cout << "\ntempArr2's resources are stolen well. Move assigment is tested.\n";
	
	std::cout << "\nTesting [] operator for arr3 as rvalue.\narr3: ";

	for (size_t i = 0; i < arr3.size(); ++i)
		std::cout << arr3[i] << " ";
	std::cout << "\noperator [] works fine as rvalue.\n";

	std::cout << "\nTesting erase() functions and range based for loop(assigns default value of given type).\n";
	IterableGTU::GTUArray<int,5> arr6;
	arr6[0] = 5;
	arr6[1] = 7;
	arr6[2] = 2;
	arr6[3] = 1;
	arr6[4] = 8;

	std::cout << "Before erasing first element\narr6(int): ";
	for (auto x: arr6) std::cout << x << " ";

	arr6.erase(arr6.begin( ));
	
	std::cout << "\n\nAfter calling arr6.erase(arr6.begin())\narr6: ";
	for (auto x: arr6) std::cout << x << " ";
	std::ptrdiff_t k = 2;
	arr6.erase(arr6.begin(),arr6.begin()+k);
	std::cout << "\n\nAfter calling arr6.erase(arr.begin(), arr.begin()+2)\narr6: ";
	for (auto x: arr6) std::cout << x << " ";

	arr6.clear();
	std::cout << "\nAfter calling arr6.clear( )\narr1: ";
	for (auto x: arr6) std::cout << x << " ";
	std::cout << "\nbegin(), clear(), range based for loop, erase() and its overloaded version works fine.\n";


	std::cout << "\nTesting at() functions as lvalue and rvalue.\nBefore assignment\narr1: ";

	for (size_t i = 0; i < arr1.size(); ++i)
		std::cout << arr1.at(i) << " ";
	
	arr1.at(0) = 10;
	arr1.at(1) = 12;
	arr1.at(2) = 16;
	arr1.at(3) = 55;

	std::cout << "\nAfter using as lvalue.\narr1: ";
	for (size_t i = 0; i < arr1.size(); ++i)
		std::cout << arr1.at(i) << " ";

	std::cout << "\nat() function works fine as lvalue and rvalue.\n";

	testSTLFunctionsArray();
	testExceptionArray();
	std::cout << "\n_____All GTUArray classes functions, STL library functions, and exceptions are tested.___\n";
}
void testSTLFunctionsArray ( ) {
	std::cout << "\nTesting arr7 for std::sort.\n";
	IterableGTU::GTUArray<int,12> arr7;

	arr7[0] = 3;
	arr7[1] = 5;
	arr7[2] = 4;
	arr7[3] = 2;
	arr7[4] = 12;
	arr7[5] = 1;
	arr7[6] = 7;
	arr7[7] = 6;
	arr7[8] = 22;
	arr7[9] = 3;
	arr7[10] = 3;
	arr7[11] = 8;

	std::cout << "Before\narr7: ";
	for (auto it = arr7.begin(); it != arr7.end(); ++it)
		std::cout << *it << " ";
	
	std::sort(arr7.begin(),arr7.end());
	std::cout << "\nAfter calling std::sort(arr7.begin(),arr7.end())\narr7: ";

	for (auto it = arr7.begin(); it != arr7.end(); ++it)
		std::cout << *it << " ";

	
	std::cout << "\nAfter calling std::sort(arr7.begin(), arr7.end(), std::greater<int>())\narr7: ";
	std::sort(arr7.begin(), arr7.end(), std::greater<int>());
	
	for (auto x : arr7)
		std::cout << x << " ";
	std::cout << std::endl;

	std::cout << "\nstd::sort works fine, end() works fine and iterators are tested.\n";

	std::cout << "\nTesting arr7 for std::find function.\n";

	auto itr = std::find(arr7.begin(), arr7.end(),1);

	std::cout << "After auto itr = std::find(arr7.begin(), arr7.end(),1); statement\n";
	std::cout << "*itr = " << *itr << std::endl;

	std::cout << "std::find is tested.\n";
	
	std::cout << "\nTesting std::for_each\n";
	 
	auto print = [](const int& x) { std::cout << x << " "; };
	std::cout << "\nbefore(will be printed with std::for_each)\narr7: ";
	
	std::for_each(arr7.cbegin(), arr7.cend(), print);

	std::cout << "\nafter(incrementing with std::for_each)\narr7: ";

	std::for_each(arr7.begin(), arr7.end(), [](int &x){ x++; });
	std::for_each(arr7.cbegin(), arr7.cend(), print);
	std::cout << "\nstd::for_each is tested and works fine.\n";
}
void testExceptionArray ( ) {

	std::cout << "\nTesting GTUArray exceptions.\n";
	try
	{
		IterableGTU::GTUArray<int,5> arr1,arr2;
		std::cout << "\nsamplearr1: ";
		for (int i = 0; i < 5; ++i) arr1[i] = i*2;
		for(auto x: arr1) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
		std::cout << "trying to access 6th element of 5 sized array with at(6).\n";
		arr1.at(6);
		auto it = arr1.begin();
		arr2.erase(it);
			for(auto x: arr2) {
			std::cout << x << " ";
		}
	}

	catch (ExceptionsGTU::InvalidIterator &iteratorException) 
	{
		std::cerr << "exception: " << iteratorException.what() << std::endl;
	}

	catch (ExceptionsGTU::OutOfRange &outOfRangeException)
	{
		std::cerr << "exception: " << outOfRangeException.what() << std::endl;
	}

	catch (...)
	{
		std::cerr << "exception: Some error occured.\n";
	}

	try 
	{
		IterableGTU::GTUArray<int,5> arr1,arr2;
		for (int i = 0; i < 5; ++i) arr1[i] = i*2;
		std::cout << "\nsamplearr2: ";
		for(auto x: arr1) {
			std::cout << x << " ";
		}
		std::cout << std::endl;
		
		auto it = arr1.begin();
		std::cout << "trying to erase invalid iterator.\n";
		arr2.erase(it);
		for(auto x: arr2) {
			std::cout << x << " ";
		}		
	}

	catch (ExceptionsGTU::InvalidIterator &iteratorException) 
	{
		std::cerr << "exception: " << iteratorException.what() << std::endl;
	}

	catch (ExceptionsGTU::OutOfRange &outOfRangeException)
	{
		std::cerr << "exception: " << outOfRangeException.what() << std::endl;
	}

	catch (...)
	{
		std::cerr << "exception: Some error occured.\n";
	}

	std::cout << "\nAll exceptions are tested.\n";		
}