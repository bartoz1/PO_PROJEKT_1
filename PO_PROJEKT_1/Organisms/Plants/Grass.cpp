#include "Grass.h"
#include <iostream>

Grass::Grass(World& world, int pos_x, int pos_y)
	:Plant(world, pos_x, pos_y, 0, 0, "trawa", GRASS){
}

void Grass::draw() {
	std::cout << (char)05;
}
