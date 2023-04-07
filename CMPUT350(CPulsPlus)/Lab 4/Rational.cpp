#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Rational.h"

using namespace std;

Rational::Rational() {			//initialise a rational number with numerator = 0, denominator = 1
	this->num = 0;
	this->den = 1;
}

Rational::Rational(int num) {  //initialise a rational number with numerator = num, denominator = 1
	this->num = num;
	this->den = 1;
}

Rational::Rational(int num, int den) {  //initialise a rational number with numerator = num, denominator = den
	assert(den != 0);
	if ((num < 0) && (den < 0)) {
		this->num = -1*num;
		this->den = -1*den;
	}
	this->num = num;
	this->den = den;
}

Rational::~Rational() {                       // destructor
	delete num;
	delete den;
}

Rational::Rational(const Rational& r) {            // copy constructor
	if (this != r) {
		this->num = r.num;
		this->den = r.den;
	}	
}
Rational& Rational::operator=(const Rational& r) { // assignment operator
	if (this != r) {
		this->num = r.num;
		this->den = r.den;
	}
	return this;
}
Rational& Rational::operator*(const Rational& r) { //multiplication of 2 Rational types
	this->num *= r.num;
	this->den *= r.den;
	return this;
}
Rational& Rational::operator/(const Rational& r) { //division of 2 Rational types
	assert(r.num != 0);
	this->num *= r.den;
	this->den *= r.num;
	return this;
}
Rational& Rational::operator+(const Rational& r) { //addition of 2 Rational types
	if (this->den != r.den) {
		this->num *= r.den;
		this->den *= r.den;
	}
	this->num += r.num;
	return this;
}
Rational& Rational::operator-(const Rational& r) { //substraction of 2 Rational types
	if (this->den != r.den) {
		this->num *= r.den;
		this->den *= r.den;
	}
	this->num -= r.num;
	return this;
}
bool Rational::operator==(const Rational& r) { //equals
	bool state;
	//implement equals
	if (this->den == r.den) {
		if (this->num == r.num) {
			state = true;
		}
	}
	else if (this->den != r.den) {
		if ((this->num * r.den) == (r.num * this->den)) {
			state = true;
		}
	}
	else {
		state = false;
	}
	return state;
}
bool Rational::operator!=(const Rational& r) { //not equals
	bool state;
	//implement not equals
	if (this->den == r.den) {
		if (this->num == r.num) {
			state = false;
		}
	}
	else if (this->den != r.den) {
		if ((this->num * r.den) == (r.num * this->den)) {
			state = false;
		}
	}
	else {
		state = true;
	}
	return state;
}

Rational& Rational::operator++() { //pre increment
	this->num += this->den;
	return this;
}
Rational& Rational::operator--() { //pre decrement
	this->num -= this->den;
	return this;
}
Rational Rational::operator++(int) { //post increment
	Rational copy(*this);
	operator++();
	return copy;
}
Rational Rational::operator--(int) { //pre increment
	Rational copy(*this);
	operator--();
	return copy;
}

ostream& Rational::operator<<(ostream& os, const Rational& r)
{
	// returns result of << (a reference to an ostream)
	// could also write: return os; after output
	os << "[" << r.num << ", " << r.den << "]";
	return os;
}

istream& Rational::operator>>(istream& is, Rational& r)
{
	// returns result of >> (a reference to an istream)
	// could also write: return is; after input
	is >> r.num >> r.den;
	return is;
}