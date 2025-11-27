#include "../vector/Stack.hpp"
#include <iostream>



int main(){
    StackArray<int> s;
    assert(s.empty());
    s.push(2);
    s.push(4);
    assert(s.size() == 2);
    assert(s.top() == 4);
    s.pop();
    assert(s.size() == 1);
    assert(s.top() == 2);

    StackArray<int> s2 = std::move(s);
    assert(s2.size() == 1);
    assert(s.empty());
    std::cout << "Pass all tests.";
    return 0;
}