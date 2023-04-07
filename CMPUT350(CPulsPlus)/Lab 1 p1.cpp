/*
  
Write C++ program p1.cpp which implements and tests function

  void rotate_left(int A[], int n);

rotate_left shifts all elements of n-element array A one location to the
left, and stores the original left-most entry into the right-most position.

Examples:

A[] before call:    1 2 3 4 5 6
A[] after call:     2 3 4 5 6 1
after another call: 3 4 5 6 1 2
etc.

Test your function using a couple of test cases in main() including one which
rotates an n-element array n times and checks whether the resulting array is
the same as the one you started with.

*/

#include <iostream>
#include <cassert>
#include <cstdlib>

// rotate array A that contains n elements one position to the left
void rotate_left(int A[], int n)
{
  assert(n > 0);

  int left = A[0];
  for (int i=0; i < n-1; ++i) {
    A[i] = A[i+1];
  }
  A[n-1] = left;
}

// print array elements separated by space in one line
void print(int A[], int n)
{
  for (int i=0; i < n; ++i) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
}

int main()
{
  // create 2 arrays containing 0..N-1
  const int N = 20;
  int A[N], B[N];

  for (int i=0; i < N; ++i) {
    A[i] = B[i] = i;
  }

  print(A, N);

  // rotate_right A N times and print array after each
  // rotation for visual inspection
  for (int i=0; i < N; ++i) {
    rotate_left(A, N);
    print(A, N);
  }

  // compare with original array
  for (int i=0; i < N; ++i) {
    if (A[i] != B[i]) {
      std::cerr << " oops " << std::endl;
      exit(1);
    }
  }
  return 0;
}
