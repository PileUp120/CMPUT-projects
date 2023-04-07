#include <iostream>
#include <vector>
#include <array>
#include <string>

//iterate from the end to the beginning, changing the value of index if the current value is less than the next
size_t index_of_max(const int* A, size_t n) {
	size_t index = 0;
	for (size_t i = n - 1; i >= 0; i--) {
		if ((i > 0) && (A[i] < A[i - 1])) {
			index = (i-1);
		}
	}
	//do a final check to see if the first element is the biggest and change index accordingly
	if (A[1] < A[0]) {
		index = 0;
	}
	return index;
}

//works the same way as previous, modified to support any 
template <typename T>
size_t index_of_max2(const T &A, size_t n)
{
	size_t index = 0;
	for (size_t i = n - 1; i >= 0; i--) {
		if ((i > 0) && (A[i] < A[i - 1])) {
			index = (i - 1);
		}
	}
	if (A[1] < A[0]) {
		index = 0;
	}
	return index;
}

size_t index_of_maxS(const char* A, size_t n)
{
	size_t index = 0;
	for (size_t i = n - 1; i >= 0; i--) {
		if ((i > 0) && (strcmp(A[i], A[i-1]) < 0) {
			index = (i - 1);
		}
	}
	if (strcmp(A[1], A[0]) < 0) {
		index = 0;
	}
	return index;
}

void print(const int* a, size_t n) {
	for (const int value : A) {
		std::cout << value << ' ';
	}
	std::cout << "\n";
}

template <typename T>
void print2(const T &a, size_t n) {
	for (const T& value : A) {
		std::cout << value << ' ';
	}
	std::cout << "\n";
}

int main() {
	//fill code

	int test[] = { 4,3,5,6 };
	std::cout << "index of max in test: " << index_of_max(test, 4) << "\n";
	print(test, 4);

	double test2 [] = { 4.2,3.6,5.8,6.1 };
	std::cout << "index of max in test: " << index_of_max2(test2, 4) << "\n";
	print2(test2, 4);

	char* test3[] = { "car", "fish", "cat", "fly"};
	std::cout << "index of max in test: " << index_of_maxS(test3, 4) << "\n";
	print2(test2, 4);


	return 0;
}