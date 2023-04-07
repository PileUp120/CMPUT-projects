#include <iostream>
#include "Stack.h"
#include <vector>

template <typename T>
using StkBase = std::vector<T>;

using Base = StkBase<T>;

bool Stack::empty() const
{ 
	return Base::empty(); 
}

void Stack::push(const T& x)
{
	Base::push_back(x);
}

T& Stack::top() 
{ 
	assert(!empty()); 
	return Base::back(); 
}

void Stack::pop() 
{ 
	assert(!empty());
	Base::pop_back(); 
}

void Stack::clear() {
	while (!this.empty())
	{
		this.pop();
	}
}

int main() {

	Stack r; //create empty stack

	std::cout << r.empty(); //ask if r is empty, must return true
	r.top(); //ask to return reference to top element in r, must fail because r is empty
	r.pop(); //ask to pop top element in r, must fail because r is empty

	r.push(4); //push int 4 into r
	std::cout << r.empty() << "\n"; //must now return false

	std::cout << r.top() << "\n"; //must print 4
	r.pop(); //now these fucntions must work

	r.push(3);
	r.push(7);
	r.push(8);
	r.push(1);
	r.push(2);
	r.push(6); //push several elements into r

	std::cout << r; //must print 6 2 1 8 7 3

	reverse_stack(r); //reverse order of elements in r

	std::cout << r; //must print 3 7 8 1 2 6

	r.clear(); //empty the stack
	std::cout << r.empty(); //this should be true once again

	return 0;
}
