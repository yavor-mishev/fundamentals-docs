/*
Chapter 12 - Exercise 12.5

Task:

*/

#include <iostream>
using namespace std;

int main() {
	int x, y;
	cin >> x >> y;

	if (x % 2 == 0) cout << x * y;
	else cout << x - y;

	return 0;
}