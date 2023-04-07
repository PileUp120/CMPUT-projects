// 
#include "Matrix.h"
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace std;

// construct n by n matrix and initialize elements with 0
// pre-condition: n > 0
Matrix::Matrix(int _n)
  : n(_n)
{
  assert(n > 0);
  p = new int[n*n](); // () initializes POD with 0
  // alternatively: loop 0..n*n-1 and set each element to 0
  //puts(""); // for finding line in g++ -S -O3 ... output
}

// release all resources
Matrix::~Matrix()
{
  delete [] p;
}

// CC
Matrix::Matrix(const Matrix &rhs)
  : n(rhs.n)
{
  int s = n * n;
  // allocate new array and copy rhs values over
  p = new int[s];
  for (int i=0; i < s; ++i) {
    p[i] = rhs.p[i];
  }
}

// AO
// pre-condition: rhs must have same size
Matrix &Matrix::operator=(const Matrix &rhs)
{
  if (&rhs != this) {
    assert(n == rhs.n);
    
    // sizes compatible => 
    // just copy all elements over
    int s = n * n;
    for (int i=0; i < s; ++i) {
      p[i] = rhs.p[i];
    }
  }
  return *this;
}

// set matrix element [r,c] to value
// (indexes start with 0)
// pre-condition: r,c within range
void Matrix::set(int r, int c, int value)
{
  assert(0 <= r && r < n);
  assert(0 <= c && c < n);
  p[r*n + c] = value;
}

// return size (n)
int Matrix::size() const
{
  return n;
}

// return matrix element [r,c] (indexes start with 0)
// pre-condition: r,c within range
int Matrix::get(int r, int c) const
{
  assert(0 <= r && r < n);
  assert(0 <= c && c < n);
  return p[r*n + c];
}

// print all elements to stdout - row by row, using space as separator
void Matrix::print() const
{
  for (int r=0; r < n; ++r) {
    for (int c=0; c < n; ++c) {
      cout << get(r, c) << " ";
    }
    cout << endl;
  }
}

// return true iff m has the same dimension as maxtrix and identical elements
bool Matrix::equals(const Matrix &m) const
{
  if (m.size() != n) {
    return false;
  }

  int s = n*n;

  for (int i=0; i < s; ++i) {
    if (p[i] != m.p[i]) {
      return false;
    }
  }
  return true;
}
