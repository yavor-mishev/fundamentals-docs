#include <iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;

	int age = b - a;
	if (age < 16) cout << "No";
	else if (age >= 16 && age <= 18) cout << "S pridrujitel";
	else cout << "Yes";

	return 0;
}