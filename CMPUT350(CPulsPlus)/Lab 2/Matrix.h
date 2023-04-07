#pragma once

class Matrix
{
public:
  
  // construct n by n matrix and initialize elements with 0
  // pre-condition: _n > 0
  Matrix(int _n);

  // release all resources
  ~Matrix();

  // CC
  Matrix(const Matrix &rhs);

  // AO
  // pre-condition: rhs must have same size
  Matrix &operator=(const Matrix &rhs);

  // return size (n)
  int size() const;
  
  // set matrix element (r,c) to value
  // (indexes start with 0)
  // pre-condition: r,c within range
  void set(int r, int c, int value);

  // return matrix element (r,c)
  // (indexes start with 0)
  // pre-condition: r,c within range
  int get(int r, int c) const;

  // print all elements to stdout - row by row, using space as separator
  void print() const;

  // return true iff m has the same size as maxtrix and identical
  // elements
  bool equals(const Matrix &m) const;
              
private:

  // data
  int n;  // size
  int *p; // sole owner of n*n ints
};
