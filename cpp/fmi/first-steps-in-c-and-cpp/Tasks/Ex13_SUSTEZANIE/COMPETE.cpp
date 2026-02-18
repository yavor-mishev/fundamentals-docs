#include <iostream>
using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c;

	int m = a;
	if (b > m) m = b;
	if (c > m) m = c;

	cout << m;
	return 0;
}