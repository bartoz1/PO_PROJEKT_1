#include "Sheep.h"
#include <iostream>

Sheep::Sheep(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 4, 4, "Owca", SHEEP) {
}
void Sheep::draw() {
	std::cout << "\033[97m" << "O" << "\033[0m";
}