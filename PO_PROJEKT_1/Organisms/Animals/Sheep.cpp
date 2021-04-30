#include "Sheep.h"
#include <iostream>

Sheep::Sheep(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 4, 4, "Owca", SHEEP) {
}
void Sheep::draw() {
	std::cout << "\033[97m" << "O" << "\033[0m";
}
/*
void Sheep::giveBirth(Organism* parent2) {
	std::cout << "maja potomstwo " << parent2->getName() << " z " << this->getName() << endl;
	Position next_pos;
	next_pos = getNextAvailablePosition(this->getPosition(), (DIRECTION)(rand() % 4));
	if (!world.areDifferentPos(next_pos, this->getPosition())) {
		next_pos = getNextAvailablePosition(parent2->getPosition(), (DIRECTION)(rand() % 4));
	}
	if (!world.areDifferentPos(next_pos, parent2->getPosition())) {
		std::cout << "Nowe zwierze nie znalazlo miejsca obok rodzicow wiec umarlo :(\n";
		return;
	}

	world.addOrganism(SHEEP, next_pos);

}*/