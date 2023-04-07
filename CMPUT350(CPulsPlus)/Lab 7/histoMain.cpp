#include "Histo.h"

using namespace std;

int main()
{
    Histogram test;
    std::string s;
    for (;;) {
        cin >> s;
        test.count(s);
        if (!cin) {
            break;
        }
    }

    if (!cin.eof()) {
        cerr << "input error" << endl;
        exit(1);
    }

    test.print(cout);


    return 0;
}