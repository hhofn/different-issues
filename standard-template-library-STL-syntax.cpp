#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <deque>
#include <forward_list>

int main() {
    // 1. Containers

    // Vector (dynamic array)
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // List (doubly linked list)
    std::list<int> lst = {1, 2, 3, 4, 5};

    // Forward List (singly linked list)
    std::forward_list<int> flst = {1, 2, 3, 4, 5};

    // Deque (double-ended queue)
    std::deque<int> dq = {1, 2, 3, 4, 5};

    // Set (ordered unique elements)
    std::set<int> st = {1, 2, 3, 4, 5};

    // Multiset (ordered elements, allows duplicates)
    std::multiset<int> mst = {1, 2, 2, 3, 4, 5};

    // Map (key-value pairs)
    std::map<std::string, int> mp = {{"Alice", 25}, {"Bob", 30}};

    // Multimap (key-value pairs, allows duplicate keys)
    std::multimap<std::string, int> mmap = {{"Alice", 25}, {"Alice", 26}, {"Bob", 30}};

    // Unordered Map (hash table)
    std::unordered_map<std::string, int> ump = {{"Charlie", 35}, {"David", 40}};

    // Unordered Set (hash set)
    std::unordered_set<int> us = {5, 4, 3, 2, 1};

    // Queue
    std::queue<int> q;
    q.push(1); q.push(2); q.push(3);

    // Stack
    std::stack<int> stk;
    stk.push(1); stk.push(2); stk.push(3);

    // Priority Queue
    std::priority_queue<int> pq;
    pq.push(3); pq.push(1); pq.push(2);

    // Tuple
    std::tuple<int, std::string, double> tpl(1, "Hello", 3.14);

    // 2. Iterators
    std::vector<int>::iterator it = vec.begin();
    std::advance(it, 2);  // Move iterator 2 positions

    // 3. Algorithms
    std::sort(vec.begin(), vec.end());  // Sort vector
    int count = std::count(vec.begin(), vec.end(), 3);  // Count occurrences of 3
    std::reverse(lst.begin(), lst.end());  // Reverse list

    // 4. Functors (Function Objects)
    std::function<int(int, int)> add = [](int a, int b) { return a + b; };
    int result = add(3, 4);

    // 5. Numeric Algorithms
    int sum = std::accumulate(vec.begin(), vec.end(), 0);  // Sum of vector elements

    // 6. Searching and Querying
    auto pos = std::find(vec.begin(), vec.end(), 3);  // Find element in vector
    bool exists = std::binary_search(st.begin(), st.end(), 3);  // Binary search in set

    // 7. Lambda Expressions
    std::for_each(vec.begin(), vec.end(), [](int &n){ n++; });  // Increment each element of vector

    return 0;
}