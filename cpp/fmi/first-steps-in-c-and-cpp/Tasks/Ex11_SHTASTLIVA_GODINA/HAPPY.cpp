#include <iostream>
using namespace std;

int main() {
	int year;
	cin >> year;

	int a, b, c, d;
	a = year % 10;
	year /= 10;
	b = year % 10;
	year /= 10;
	c = year % 10;
	year /= 10;
	d = year;
	if (a == b || a == c || a == d || b == c || b == d || c == d) cout << "Yes";
	else cout << "No";

	return 0;
}