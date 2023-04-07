#include "Bar.h"
#include <cassert>

// prefix Bar:: tells the compiler that we are defining
// methods for class Bar

// constructor
Bar::Bar()
{
  // x implicetely constructed here
  p = new Foo[N];
}

// descructor
Bar::~Bar() {
  delete [] p;
  // x implicitely destroyed here
}

// CC
Bar::Bar(const Bar &rhs)
  : x(rhs.x) // copy construct x from rhs.x
{
  p = new Foo[N];
  for (int i=0; i < N; ++i) {
    p[i] = rhs.p[i];
  }
}

// AO
Bar &Bar::operator= (const Bar &rhs)
{
  if (this != &rhs) {
    x = rhs.x;
    // assume: array size always N
    // => copying OK (no need to release memory first)
    for (int i=0; i < N; ++i) {
      p[i] = rhs.p[i];
    }
  }
  return *this;
}
