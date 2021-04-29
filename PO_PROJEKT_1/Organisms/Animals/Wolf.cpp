#include "Wolf.h"
#include <iostream>
Wolf::Wolf(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 1, 2) {
}
void Wolf::draw() {
	std::cout << "W";
}
