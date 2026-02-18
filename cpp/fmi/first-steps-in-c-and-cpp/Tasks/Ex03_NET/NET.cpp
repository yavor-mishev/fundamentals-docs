#include <iostream>
using namespace std;

int main() {
	char ch;
	int count = 0;

	cin >> ch;
	if (ch == 'N' || ch == 'n' || ch == 'E' || ch == 'e' || ch == 'T' || ch == 't') count++;
	cin >> ch;
	if (ch == 'N' || ch == 'n' || ch == 'E' || ch == 'e' || ch == 'T' || ch == 't') count++;
	cin >> ch;
	if (ch == 'N' || ch == 'n' || ch == 'E' || ch == 'e' || ch == 'T' || ch == 't') count++;

	cout << count << endl;
}