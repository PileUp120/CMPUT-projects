#include <iostream>
using namespace std;

// returns 0 if input OK, 1 otherwise
int main()
{
  // partial sum of read integers
  int sum = 0, input;
  
  while (cin >> input) {
    sum += input;
  }

  if (cin.eof()) {
    
    // eof - print sum
    cout << sum << endl;
    return 0;
    
  } else {
    
    // error
    cerr << "illegal input" << endl;
    return 1;
  }
}
