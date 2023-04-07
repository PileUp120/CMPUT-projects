#include <iostream>

using namespace std;

struct Point
{
	int x, y;

	friend ostream& operator<< (ostream& os, const Point& p);
	friend istream& operator>> (istream& is, Point& p);
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

