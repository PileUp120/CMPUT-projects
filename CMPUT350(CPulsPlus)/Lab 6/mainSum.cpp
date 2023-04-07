using namespace std;

template <typename T>
struct Sum
{
	//prevents T from being negative or a non int type at compile time
	static_assert(!Test<T>::value, "T cannot be negative or double");
	T value = 0;
	while (T != 0)
	{
		value += Sum<T-1>
	}

};

template <typename T>
struct Test
{
	value = 0;
	if (T < 0) {
		value = 1;
	}
};


int main()
{
	cout << Sum<0>::value << endl;  // 0
	cout << Sum<10>::value << endl;  // 55
	cout << Sum<20>::value << endl;  // 210
	cout << Sum<100>::value << endl; // 5050
	// etc.
	return 0;
}