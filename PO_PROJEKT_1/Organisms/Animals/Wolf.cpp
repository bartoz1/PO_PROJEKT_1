#include "Wolf.h"
#include <iostream>
Wolf::Wolf(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 5, 9, "wilk", WOLF) {
}
void Wolf::draw()const {
	std::cout << "W";
}

