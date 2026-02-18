#include <iostream>
using namespace std;

/*
	The only real diff between a class and a struct is the visibility of the members.
	Class -> private by default
	Struct -> public by default
*/

struct Player {
	int x, y;
	int speed;

	void Move(int xa, int ya) {
		x += xa;
		y += ya;
	}
};

int main() {
	Player nicole;
	nicole.x = 0;
	nicole.y = 0;

	nicole.Move(2, 2);
	cout << "Nicole's x position: " << nicole.x << endl
		<< "Nicole's y position: " << nicole.y;
}