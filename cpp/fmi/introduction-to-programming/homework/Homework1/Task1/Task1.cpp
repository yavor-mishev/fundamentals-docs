//#include <iostream>
//#include <cmath>
//using namespace std;
//
//int main() {
//	int x1, y1, x2, y2, x3, y3, x4, y4;
//	cout << "x1= "; cin >> x1;
//	cout << "y1= "; cin >> y1;
//	cout << "x2= "; cin >> x2;
//	cout << "y2= "; cin >> y2;
//	cout << "x3= "; cin >> x3;
//	cout << "y3= "; cin >> y3;
//	cout << "x4= "; cin >> x4;
//	cout << "y4= "; cin >> y4;
//
//	int s1 = abs(x1 - x2) == 0 ? abs(y1 - y2) : abs(x1 - x2);
//	int s2 = abs(y2 - y3) == 0 ? abs(x2 - x3) : abs(y2 - y3);
//	int s3 = abs(x3 - x4) == 0 ? abs(y3 - y4) : abs(x3 - x4);
//	int s4 = abs(x1 - x4) == 0 ? abs(y1 - y4) : abs(x1 - x4);
//
//	int d1 = s1 * s1 + s2 * s2;
//	int d2 = s3 * s3 + s4 * s4;
//
//	if (s1 == s2 && s2 == s3 && s3 == s4 && s1 == s4 && d1 == d2) cout << "Square";
//
//	return 0;
//}