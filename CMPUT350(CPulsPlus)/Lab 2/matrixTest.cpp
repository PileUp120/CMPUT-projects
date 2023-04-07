#include "Matrix.h"
#include <iostream>

using namespace std;

int main()
{
  const int n = 5;
  Matrix u(n);

  // should be all 0s
  u.print();
  cout << endl;

  Matrix v(n);
  // increasing values
  int k = 0;
  for (int r=0; r < n; ++r) {
    for (int c=0; c < n; ++c) {
      v.set(r, c, k++);
    }
  }

  v.print();

  // test equals

  if (!u.equals(u)) {
    cout << "equals oops 1" << endl;
  }
  if (u.equals(v)) {
    cout << "equals oops 2" << endl;
  }
  if (!v.equals(v)) {
    cout << "equals oops 3" << endl;
  }
  
  // test CC
  Matrix w(u);

  if (!w.equals(u)) {
    cout << "CC oops" << endl;
  }

  // test AO
  Matrix z(n);

  z = u;
  if (!z.equals(u)) {
    cout << "AO oops" << endl;
  }

  return 0;
}
