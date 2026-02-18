#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a, b, c;
	cout << "A= ";
	cin >> a;
	cout << "B= ";
	cin >> b;
	cout << "C= ";
	cin >> c;

	double p = (a + b + c) / 2;
	cout << "The area of the triangle is: " << sqrt(p * (p - a) * (p - b) * (p - c)) << endl;
}