udacity CPP notes

`#include <iostream>`

`using namespace std;` // when cmd's not explicity defined, might accidentally reference a cmd from a diff lib

`sizeof(variableName);` // returns bytes allocated for variable
```cpp
cont int weightGoal = 100; // variable weightGoal will forever be 100, immutable, aka read-only
enum type_name {
	value 1,
	value2
} object_names; // new variable type with a finite number of values assigned to it

enum MONTH {Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
Jan = 0; // etc; http://www.cplusplus.com/doc/tutorial/other_data_types/
```

Some cout formatting
```cpp
#include <iomanip> 	//setw(n) sets width to n
std::cout<<"Ints"<<std::setw(10)<<"Floats "<<std::setw(10)<<"Doubles"<<"\n"; // Ints      Floats    Doubles
```

Working with files
```cpp
#include <fstream> // dir for reading and writing files
ofstream myfile; // output stream writing
ifstream myfile; // input stream reading, opened during creation of iftsream
fstream mfyile; // r-w
myfile.open; // if doesn't exist, will be created
myfile.close();

if (myfile.is_open()) {myfile<<"add text\n";}
myfile.clear(); myfile.seekg(0, ios::beg); // reset to beginning of file, removes eof tag, in C++11 seekg does automatically
```

header files - .hpp ext - contain info about how to complete a task

`std::getline(std::cin, variableName);` // will retrieve all chars till \n is detected and store in `variableName`

```cpp
#include <sstream>
std::getline(std::cin, stringVariable); std::stringstream(stringVariable) >> numericVariable;
```