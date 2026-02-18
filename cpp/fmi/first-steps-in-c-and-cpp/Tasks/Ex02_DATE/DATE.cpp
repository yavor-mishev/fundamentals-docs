#include <iostream>
using namespace std;

int main() {
	short n;
	cin >> n;

	if (n > 9) cout << n - 9 << ".02.2006\n";
	else cout << n + 22 << ".01.2006\n";
	return 0;
}
