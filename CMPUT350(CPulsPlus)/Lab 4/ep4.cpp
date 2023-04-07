#include <iostream>

using namespace std;

struct Point
{
	int x, y;

	friend ostream& operator<< (ostream& os, const Point& p);
	friend istream& operator>> (istream& is, Point& p);

	bool operator== (const Point& p) {
		return ((this->x == p.x) && (this->y == p.y));
	}

	bool operator> (const Point& p) {
		return ((this->x > p.x) || (this->y > p.y));
	}

	bool operator>= (const Point& p) {
		bool greaterEq;
		greaterEq = ((this->x >= p.x));
		if (!greaterEq) {
			greaterEq = ((this->y >= p.y));
		}
		return greaterEq;
	}

	Point operator++() {
		this->x += 1;
		return *this;
	}

	Point operator--() {
		this->x -= 1;
		return *this;
	}

	Point operator++(int) {
		Point copy(*this);
		operator++();
		return copy;
	}

	Point operator--(int) {
		Point copy(*this);
		operator--();
		return copy;
	}
};

istream& operator>> (istream& is, Point& p) {
	is >> p.x >> p.y;
	return is;
}

ostream& operator<< (ostream& os, Point& p) {
	os << "(" << p.x << ", " << p.y << ")\n";
	return os;
}

int main() {

	Point p;
	cin >> p;
	cout << p << endl;

	return 0;
}

