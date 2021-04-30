#include "Human.h"
#include <iostream>
Human::Human(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 1, 2, "czlowiek", HUMAN) {
}
void Human::draw() {
	std::cout << "C";
}
