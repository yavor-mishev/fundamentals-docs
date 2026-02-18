#include <iostream>
using namespace std;

int main() {
	int a, ha = 0;
	cin >> a;

	if (a == 1) ha = 15;
	if (a == 2) ha = 24;
	if (a < 19) ha = 24 + (a - 2) * 4;
	if (a > 18) ha = 88 + (a - 18) * 3;

	cout << ha;
}