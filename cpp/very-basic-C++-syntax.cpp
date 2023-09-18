// 1. Comments
// This is a single-line comment

/* This is a 
   multi-line comment */

// 2. Preprocessor Directives
#include <iostream>  // Include header files

#define PI 3.14159   // Define a macro

// 3. Data Types
int integerVar = 10;
double doubleVar = 20.5;
char charVar = 'A';
bool boolVar = true;

// 4. Constants
const int constantVar = 100;

// 5. Enumerations
enum Days {Sun, Mon, Tue, Wed, Thu, Fri, Sat};

// 6. Arrays
int arrayVar[5] = {1, 2, 3, 4, 5};

// 7. Conditional Statements
if (integerVar > 5) {
    // Do something
} else if (integerVar < 5) {
    // Do something else
} else {
    // Do another thing
}

// 8. Loops
for (int i = 0; i < 5; i++) {
    // Repeatedly do something
}

while (boolVar) {
    // Do something while condition is true
}

do {
    // Do something at least once
} while (boolVar);

// 9. Functions
void myFunction() {
    // Function body
}

int add(int a, int b) {
    return a + b;
}

// 10. Classes and Objects
class MyClass {
public:
    int myVar;
    void myMethod() {
        // Method body
    }
};

MyClass obj;  // Create an object of MyClass

// 11. Pointers and References
int* pointerVar = &integerVar;  // Pointer to an integer
int& referenceVar = integerVar; // Reference to an integer

// 12. Dynamic Memory
int* dynamicVar = new int;      // Allocate memory
delete dynamicVar;              // Deallocate memory

// 13. Exception Handling
try {
    // Code that might throw an exception
} catch (int e) {
    std::cout << "An exception occurred: " << e << std::endl;
}

// 14. Namespaces
namespace MyNamespace {
    int namespaceVar = 50;
}

// Using the namespace
using namespace MyNamespace;

// 15. Input/Output
std::cout << "Output text";     // Output to console
std::cin >> integerVar;         // Input from console
