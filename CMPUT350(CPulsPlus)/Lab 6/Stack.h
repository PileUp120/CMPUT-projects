#pragma once
#include <cassert>
#include <vector>

template <typename T>
using StkBase = std::vector<T>;

template <typename T>
class Stack
    : private StkBase<T>
{
public:

    using Base = StkBase<T>;

    // returns true iff queue is empty
    bool empty() const; 

    // push element to end of queue
    void push(const T& x);

    // returns reference to front element (pre-cond: !empty)
    T& top();

    // removes front element (pred-cond: !empty)
    void pop();

    void clear();

    // default constr, CC, AO, destructor should work because vector class must take care of itself
};

std::ostream& operator<<(std::ostream& os, const Stack& rhs);
{
    Stack temp(rhs);
    while (!temp.empty()) {
        os << temp.top();
        temp.pop();
    }
    return os;
}

Stack& reverse_stack(Stack& rhs) {
    //reverse given stack
}