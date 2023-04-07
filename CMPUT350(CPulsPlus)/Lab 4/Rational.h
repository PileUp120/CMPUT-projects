#ifndef Rational_H
#define Rational_H

#include <iostream>

class Rational {
public:
	Rational();			//initialise a rational number with numerator = 0, denominator = 1
	Rational(int num);  //initialise a rational number with numerator = num, denominator = 1
	Rational(int num, int den);  //initialise a rational number with numerator = num, denominator = den
	
	~Rational ();                       // destructor
	
	Rational(const Rational& r);            // copy constructor
	Rational& operator=(const Rational& r); // assignment operator

	Rational& operator+(const Rational& r); //addition of 2 Rational types
	Rational& operator-(const Rational& r); //substraction of 2 Rational types
	Rational& operator*(const Rational& r); //multiplication of 2 Rational types
	Rational& operator/(const Rational& r); //division of 2 Rational types
	bool operator==(const Rational& r); //equals
	bool operator!=(const Rational& r); //not equals
	
	Rational& operator++(); //pre increment
	Rational& operator--(); //pre decrement
	Rational operator++(int); //post increment
	Rational operator--(int); //pre increment

	friend ostream& operator<< (ostream& os, const Rational& r);
	friend istream& operator>> (istream& is, Rational& r);

private:
	int num, den;
};

#endif