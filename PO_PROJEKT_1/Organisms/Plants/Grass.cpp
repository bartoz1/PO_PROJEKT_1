#include "Grass.h"
#include <iostream>

Grass::Grass(World& world, int pos_x, int pos_y)
	:Plant(world, pos_x, pos_y, 0, 0, "trawa", GRASS){
}

void Grass::draw()const {
	std::cout << "\033[32m" << (char)05<< "\033[0m";
}
