// driver: counts words on stdin and prints histogramm

#include "Histo_sol.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
  Histo h;

  for (;;) {
    string w;
    cin >> w;
    if (!cin) {
      // eof or error      
      break;
    }

    // update histogram    
    h.count(w); 
  }

  // print histogram
  h.print(cout); 
  return 0;
}
