#include <iostream>
using namespace std;

int main() {
	const float pi = 3.14;
	float a, r;
	cin >> a >> r;

	float sq = a * a;
	float c = pi * r * r;

	cout << (sq > c ? sq : c) << endl;
}