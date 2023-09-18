#include <iostream>

// 1. Variadic Function Templates

// Base case
template <typename T>
T adder(T v) {
    return v;
}

// Recursive variadic function
template <typename T, typename... Args>
T adder(T first, Args... args) {
    return first + adder(args...);
}

// Usage
int sum = adder(1, 2, 3, 4, 5);  // Returns 15

// 2. Variadic Class Templates (less common, but possible)

template <typename... Values>
class Tuple;

// Specialization for at least one type
template <typename Head, typename... Tail>
class Tuple<Head, Tail...> {
private:
    Head head;
    Tuple<Tail...> tail;
public:
    Tuple(Head h, Tail... t) : head(h), tail(t...) {}
    // ... (methods to access or manipulate the tuple)
};

// Usage
Tuple<int, double, std::string> t(1, 3.14, "Hello");

// 3. Expanding Variadic Template Arguments

template <typename... Args>
void printAll(Args... args) {
    // Using fold expression (C++17 feature) to expand and print all arguments
    (std::cout << ... << args) << '\n';
}

// Usage
printAll(1, "Hello", 3.14, 'A');

// 4. Type Traits with Variadic Templates

// Check if a set of types are all integral
template <typename... Args>
struct are_integral {
    static const bool value = (... && std::is_integral_v<Args>);
};

// Usage
bool check1 = are_integral<int, char, long>::value;  // true
bool check2 = are_integral<int, char, double>::value; // false
