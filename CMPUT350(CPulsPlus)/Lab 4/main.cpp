#include <iostream>
#include <cassert>
#include "Rational.h"

using namespace std;


int main()
{
    Rational u;         // value 0
    Rational v(2);      // value 2
    Rational w(-3, -4); // value 3/4

    Rational x(v);
    Rational y;
    y = w;

    Rational a = x;
    Rational b = y;
    Rational c = ++++a;
    Rational d = b++;

    cout << "u=" << u << endl;
    cout << "v=" << v << endl;
    cout << "w=" << w << endl;
    cout << "x=" << x << endl;
    cout << "y=" << y << endl;

    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "c=" << c << endl;
    cout << "d=" << d << endl;

    cout << "result1=" << u + v - w / x * y
        << " result2=" << w + x
        << endl;

    if (x == x && x != y) {
        cout << "==,!= work" << endl;
    }
    else {
        cout << "==,!= don't work" << endl;
    }

    if (x == v) {
        cout << "CC works" << endl;
    }
    else {
        cout << "CC doesn't work" << endl;
    }

    if (y != w) {
        cout << "AO doesn't work" << endl;
    }
    else {
        cout << "AO works" << endl;
    }

    // more test code that checks assertions
    // ...

    Rational f;
    Rational e(3);


    Rational g(3, 0);

    return 0;
}