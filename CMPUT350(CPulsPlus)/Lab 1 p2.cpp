/*
  Write C++ program p2.cpp that reads a sequence of int array pairs from stdin
  and prints their component-wise sum to stdout.
*/

#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// helper function:
// free array, print error message to stderr, and
// exit program with value 1 - indicating an error

void error(int *A)
{
  delete [] A;
  cerr << "input error" << endl;
  exit(1);
}


// solve problem instance (array size n)

void solve_instance(int n)
{
  if (n <= 0) {
    error(nullptr);
  }
  
  // allocate and read first array
  
  int *A = new int[n];
  
  for (int i=0; i < n; ++i) {
    cin >> A[i];
  }

  // did any error occur when reading the first array?
  if (!cin) {
    error(A);
  }

  cout << n << endl;
    
  // read second array and print component-wise sum
  for (int i=0; i < n; ++i) {

    int b;

    if (!(cin >> b)) {
      error(A);
    }
    cout << (b+A[i]) << " ";
  }

  cout << endl;

  // clean up 
  delete [] A;
}


int main()
{
  int n;

  while (cin >> n) {
    
    // handle one input instance
    
    // n = read number of array elements

    solve_instance(n);
  }

  if (!cin.eof()) {
    // read error
    error(nullptr);
  }

  return 0;
}
