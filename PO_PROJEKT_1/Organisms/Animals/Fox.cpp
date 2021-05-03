#include "Fox.h"
#include <iostream>
Fox::Fox(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 7, 3, "lis", FOX) {
}
void Fox::draw()const {
	std::cout << "L";
}

Position Fox::getNextPosition(DIRECTION desired_dir) {
	Position tmp;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		tmp = this->getPosition();
		switch (desired_dir) {
		case LEFT:
			tmp.x--;
			break;
		case RIGHT:
			tmp.x++;
			break;
		case TOP:
			tmp.y--;
			break;
		case BOTTOM:
			tmp.y++;
			break;
		}
		if (world.getFieldState(&tmp) != BORDER) {
			if (world.getFieldState(&tmp) == OCCUPIED && world.getOrganismByPos(tmp)->getInitiative() <= this->getInitiative()
				|| world.getFieldState(&tmp) == AVAILABLE) {
				return tmp;
			}
		}
		desired_dir = (DIRECTION)((desired_dir + 1) % 4);
	}
	tmp = this->getPosition();
	tmp.state = NOTAVAILABLE;
	return tmp;
}
