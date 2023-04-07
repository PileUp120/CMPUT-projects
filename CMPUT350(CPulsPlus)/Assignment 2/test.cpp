/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <random>

struct Vec
{
  Vec(double x_=0, double y_=0)
    : x(x_), y(y_)
  { }
  
  double x, y;
};

struct Tai {
  int f,g;
  Vec v;
  Tai(int f_, int g_, Vec v_) : f(f_), g(g_), v(v_){}
};

int main()
{
    std::vector<Tai*> tais;
    std::vector<Tai*> tais2;
    Vec g(6,7);
    Tai r(2,3,g);
    Vec i(1,2);
    Tai t(6,4,i);
    Vec h(5,8);
    Tai s(7,9,h);
    tais.push_back(&r);
    tais.push_back(&s);
    tais.push_back(&t);
    
    std::cout << tais.size() << "\n";
    
    auto iter = begin(tais);
    for (; iter != tais.end(); iter++) {         //iterate through the vector of units and adds them if they can be attacked
        if ((*iter)->f < (*iter)->g){
            tais2.push_back(*iter);
        }
    }
    
    std::cout << tais2.size() << "\n";
    
    return 0;
}
