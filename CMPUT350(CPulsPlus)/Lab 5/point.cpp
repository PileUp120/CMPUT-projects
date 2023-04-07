#include <iostream>
#include <vector>

template <typename T>
struct Point
{
	T x = T();
	T y = T();

	Point(T& x0, T& y0) : x(x0), y(y0)
	{}

	void print() {
		std::cout << "x,y = " << x << "," << y << "\n";
	}

	bool &operator==(const Point& rhs) const {
		return ((x == rhs.x) && (y == rhs.x));
	}
};

template <typename T>
Point sum(const T& A, size_t n) {
	Point sum_point;
	for (size_t i = 0; i < n; i++) {
		sum_point->x += A[i].x;
		sum_point->y += A[i].y;
	}
	return sum_point;
}
template <typename T>
size_t find(const T& a, size_t n) {
	size_t found_index = -1;
	for (size_t i = 0; i < n; i++) {

	}
	return found_index;
}

int main() {

	return 0;
}