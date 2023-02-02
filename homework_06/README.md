## Compilation
``` make ```
## Run
``` ./hw6 ```

## Description
- Implementing Templated Vector, Set, Array Container Classes which are derived from abstract Iterable class.
- These classes are similar to STL classes. It is compatible with all std algorithms.  

# Test Results
## Array
```
___Testing GTUArray class___


Testing No parameter constructor for integer type.
Object is constructed fine. operator [] works fine as lvalue.
arr1 : 3 5 6 8 

Testing Copy constructor.
Object is constructed fine.
arr2(copy of arr1) : 3 5 6 8 
cbegin() end cend() member functions works fine(used while printing).

Testing move constructor.
tempArr(string): tomato apple car bread happy 
After calling the move constructor for arr3.
arr3: tomato apple car bread happy 

tempArr's resources are stolen.Move constructor tested.

Testing assignment operator(arr3 = arr4).

arr4: coin house black nine movie 
arr3: coin house black nine movie 
Assignment done well.

Testing move assingment operator for arr5(double).
tempArr2: 3.1 2.6 7.1 2.2 8.3 
After the move assingment arr5 = std::move(tempArr2)
arr5: 3.1 2.6 7.1 2.2 8.3 
tempArr2's resources are stolen well. Move assigment is tested.

Testing [] operator for arr3 as rvalue.
arr3: coin house black nine movie 
operator [] works fine as rvalue.

Testing erase() functions and range based for loop(assigns default value of given type).
Before erasing first element
arr6(int): 5 7 2 1 8 

After calling arr6.erase(arr6.begin())
arr6: 0 7 2 1 8 

After calling arr6.erase(arr.begin(), arr.begin()+2)
arr6: 0 0 2 1 8 
After calling arr6.clear( )
arr1: 0 0 0 0 0 
begin(), clear(), range based for loop, erase() and its overloaded version works fine.

Testing at() functions as lvalue and rvalue.
Before assignment
arr1: 3 5 6 8 
After using as lvalue.
arr1: 10 12 16 55 
at() function works fine as lvalue and rvalue.

Testing arr7 for std::sort.
Before
arr7: 3 5 4 2 12 1 7 6 22 3 3 8 
After calling std::sort(arr7.begin(),arr7.end())
arr7: 1 2 3 3 3 4 5 6 7 8 12 22 
After calling std::sort(arr7.begin(), arr7.end(), std::greater<int>())
arr7: 22 12 8 7 6 5 4 3 3 3 2 1 

std::sort works fine, end() works fine and iterators are tested.

Testing arr7 for std::find function.
After auto itr = std::find(arr7.begin(), arr7.end(),1); statement
*itr = 1
std::find is tested.

Testing std::for_each

before(will be printed with std::for_each)
arr7: 22 12 8 7 6 5 4 3 3 3 2 1 
after(incrementing with std::for_each)
arr7: 23 13 9 8 7 6 5 4 4 4 3 2 
std::for_each is tested and works fine.

Testing GTUArray exceptions.

samplearr1: 0 2 4 6 8 
trying to access 6th element of 5 sized array with at(6).
exception: Array subscript exceeds its allowed range!
samplearr2: 0 2 4 6 8 
trying to erase invalid iterator.
exception: Invalid iterator is entered!
All exceptions are tested.

_____All GTUArray classes functions, STL library functions, and exceptions are tested.___
```

## Vector
```

___Testing GTUVector class___


Testing No parameter constructor for integer type.
Object is constructed fine. add() function also works fine.
vec1 : 5 3 8 

Testing Copy constructor.
Object is constructed fine.
vec2(copy of vec1) : 5 3 8 
cbegin() end cend() member functions works fine(used while printing).

Testing fill constructor with different type(double).
Object is constructed fine.
vec3(double): 0 0 0 0 0 0 0 

Testing other fill constructor which takes 2 parameter with another class(std::string).
Object is constructed fine.
vec4: apple apple apple apple apple apple 

Testing move constructor with anonymous object for string type.
Anonymous objects resources are stolen well.
vec5: tomato tomato tomato tomato tomato 

Testing assignment operator(vec4 = vec5).
Assignment done well.
vec4: tomato tomato tomato tomato tomato 

Testing move assingment operator for vec3(double).

Temporary object is created.
tempVec : 22 22 22 
Temporary object's resources are stolen well(vec3 = std::move(tempVec).
vec3: 22 22 22 

Move assignment is tested.

Testing [] operator for vec1 as lvalue.
vec1 : 1 3 5 
operator [] works fine as lvalue(vec1's values are changed). Printed with ranged based for loop.

Testing [] operator for vec3 as rvalue.
vec3: 22 22 22 
operator [] works fine as rvalue.

Testing erase() functions and range based for loop.
Before erasing first element
vec6(char): a c k 7 ! 

After calling vec6.erase(vec6.begin())
vec6: c k 7 ! 

After calling vec6.erase(vec.begin(), vec.begin()+2)
vec6: 7 ! 
After calling vec6.clear( )
size = 0
vec6 is empty(vec6.empty() is being called)

begin(), clear(), size(), empty(), range based for loop, erase() and its overloaded version works fine.

Testing vec for std::sort.
Before
vec: 3 5 4 2 13 1 7 6 22 3 3 8 
After calling std::sort(vec.begin(),vec.end())
vec: 1 2 3 3 3 4 5 6 7 8 13 22 
After calling std::sort(vec.begin(), vec.end(), std::greater<int>())
vec: 22 13 8 7 6 5 4 3 3 3 2 1 

std::sort works fine, end() works fine and iterators are tested.

Testing vec for std::find function.
After auto itr = std::find(vec.begin(), vec.end(),1); statement
*itr = 1
std::find is tested.

Testing std::for_each

before(will be printed with std::for_each)
vec: 22 13 8 7 6 5 4 3 3 3 2 1 
after(incrementing with std::for_each)
vec: 23 14 9 8 7 6 5 4 4 4 3 2 
std::for_each is tested and works fine.

Testing GTUVector exceptions.
vec7: 30 30 30 30 30 
trying to access vec7[6].
exception: Array subscript exceeds its allowed range!
vec9: 30 30 30 30 30 
trying to erase invalid iterator.
exception: Invalid iterator is entered!
All exceptions are tested.

_____All GTUVector classes functions, STL library functions, and exceptions are tested.___
```
## Set
```

___Testing GTUSet class___


Testing No parameter constructor for integer type.
Object is constructed fine. add() function also works fine, and it is automatically ordered.
set1 : 2 3 5 8 11 

Duplication is tested(3 added twice) and every element is unique.

Testing Copy constructor.
Object is constructed fine.
set2(copy of set1) : 2 3 5 8 11 
cbegin() end cend() member functions works fine(used while printing).

Testing move constructor with std::string.

temp1: apple banana tomato 

after moving temp1's resources to set4.
set4: apple banana tomato 
temp1's resources are stolen well. Move constructor works fine

set3 created
set3: bread onion 

Testing assignment operator(set3 = set4).
set3: apple banana tomato 
Assignment done well.

Testing move assignment operator for set5(double).
set5: 1.1 2.1 3.3 5.2 

Temporary object is created.
tempSet : 1.3 2.2 5.2 
Temporary object's resources are stolen well.(set5 = std::move(tempSet)
set5: 1.3 2.2 5.2 

Move assignment is tested and works fine.

Testing erase() functions and range based for loop.
Before
set6(char): ! 5 7 U a c k 

After calling set6.erase(set6.search('c'))
set6: ! 5 7 U a k 

After calling set6.erase(set.begin(), set.begin()+2)
set6: 7 U a k 

After calling set6.erase('U')
set6: 7 a k 

After calling set6.deleteElement('5')
set6: 7 a k 
After calling set6.clear( )
size = 0
set is empty.(testing set6.empty())
begin(),search(), clear(), size(), empty(), deleteElement(), range based for loop, erase() and its overloaded versions works fine.

Adding elements to set6 again.
set6: ! 5 7 U a c k 
set7: 5 6 8 U b c m 
union(set6,set7): ! 5 6 7 8 U a b c k m 
intersection(set6,set7): 5 U c 
union and intersect functions are tested.

Testing set8 for std::sort.
Before
set8: 1 2 3 4 5 6 7 8 13 22 
After calling std::sort(set8.begin(),set8.end())
set8: 1 2 3 4 5 6 7 8 13 22 
After calling std::sort(set8.begin(), set8.end(), std::greater<int>())
set8: 22 13 8 7 6 5 4 3 2 1 

std::sort works fine, end() works fine and iterators are tested.

Testing set8 for std::find function.
After auto itr = std::find(set8.begin(), set8.end(),1); statement
*itr = 1
std::find is tested.

Testing std::for_each

before(will be printed with std::for_each)
set8: 22 13 8 7 6 5 4 3 2 1 
after(incrementing with std::for_each)
set8: 23 14 9 8 7 6 5 4 3 2 
std::for_each is tested and works fine.

Testing exceptions for GTUSet class.
sample set: 3 5 6 
Trying to erase invalid iterator.
exception: Invalid iterator is entered!

_____All GTUSet classes functions, STL library functions, and exceptions are tested.___
```
