/*
First Steps in Programing with C/C++
Chapter 12 - Exercise 1

Task:
Да се състави програма KOREN.cpp, която намира корена на уравнението a*x=b, където a и b са дадени чила.

Concepts:
- if-else statements
*/

#include <iostream>
using namespace std;

int main() {
	float a, b, x;
	cin >> a >> b;
	
	if (a == 0) {
		if (b == 0) {
			cout << "All values of x are a solution to a*x=b.";
		}
		else {
			cout << "Dividing by 0 is undefined!";
		}
	}
	else {
		x = b / a;
		cout << "The value of x is: " << x;
	}
	return 0;
}