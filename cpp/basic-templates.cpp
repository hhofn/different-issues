// 1. Function Templates

// Template declaration
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Usage
int sumInt = add<int>(3, 4);         // Explicit type specification
double sumDouble = add(3.5, 4.5);   // Implicit type deduction

// 2. Class Templates

// Template declaration
template <typename T>
class Box {
private:
    T content;
public:
    Box(T c) : content(c) {}
    T getContent() {
        return content;
    }
};

// Usage
Box<int> intBox(10);
Box<std::string> stringBox("Hello, Templates!");

// 3. Multiple Template Parameters

template <typename T, typename U>
class Pair {
private:
    T first;
    U second;
public:
    Pair(T f, U s) : first(f), second(s) {}
    T getFirst() { return first; }
    U getSecond() { return second; }
};

// Usage
Pair<int, std::string> pair(1, "One");

// 4. Template Specialization

// General template
template <typename T>
class Checker {
public:
    bool isEqual(T a, T b) {
        return a == b;
    }
};

// Specialization for char*
template <>
class Checker<char*> {
public:
    bool isEqual(char* a, char* b) {
        return strcmp(a, b) == 0;
    }
};

// Usage
Checker<int> intChecker;
bool result = intChecker.isEqual(5, 5);

Checker<char*> stringChecker;
bool stringResult = stringChecker.isEqual("hello", "hello");

// 5. Default Template Arguments

template <typename T = int>
class DefaultBox {
private:
    T content;
public:
    DefaultBox(T c) : content(c) {}
    T getContent() {
        return content;
    }
};

// Usage
DefaultBox<> defaultIntBox(20);  // Uses default int type
DefaultBox<std::string> defaultStringBox("Default Template");
