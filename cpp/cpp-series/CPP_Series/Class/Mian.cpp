#include <iostream>
using namespace std;

class Player {
public:
	int x, y;
	int speed;

	void Move(int xa, int ya) {
		x += xa;
		y += ya;
	}
};

int main() {
	Player yavor;
	yavor.x = 0;
	yavor.y= 0;

	yavor.Move(1, 1);

	cout << "Yavors x position: " << yavor.x << endl
		 << "Yavors y position: " << yavor.y;
}