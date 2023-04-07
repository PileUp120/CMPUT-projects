#ifndef Bar_H
#define Bar_H

#include "Foo.h"

struct Bar
{
  // constructor
  Bar();

  // destructor
  ~Bar();

  // CC
  Bar(const Bar &rhs);

  // AO
  Bar &operator= (const Bar &rhs);

  // data
  static const int N = 10;
  Foo x;
  Foo *p; // always pointing to N solely owned Foos
};

#endif
