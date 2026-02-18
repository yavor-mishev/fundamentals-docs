//#include <iostream>
//using namespace std;
//
//
//int main() {
//	short d, m, y, num;
//	cin >> d >> m >> y;
//
//	num = 0;
//	num += d % 10;
//	if (d > 9) {
//		d /= 10;
//		num += d % 10;
//	}
//
//	num += m % 10;
//	if (m > 9) {
//		m /= 10;
//		num += m % 10;
//	}
//
//	num += y % 10;
//	y /= 10;
//
//	num += y % 10;
//	y /= 10;
//
//	num += y % 10;
//	y /= 10;
//
//	num += y;
//
//	if (num > 9) {
//		short x = num % 10;
//		num /= 10;
//		num += x;
//	}
//
//	cout << num;
//
//	return 0;
//}