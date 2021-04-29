#include "Sheep.h"

Sheep::Sheep(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 4, 4, "Owca") {
}
void Sheep::draw() {
	std::cout << "O";
}
void Sheep::giveBirth(Organism* parent2) {
	Position next_pos;
	next_pos = world.getNextAvailablePosition(this->getPosition(), (DIRECTION)(rand() % 4));
	if (!world.areDifferentPos(next_pos, this->getPosition())) {
		next_pos = world.getNextAvailablePosition(parent2->getPosition(), (DIRECTION)(rand() % 4));
	}
	if (!world.areDifferentPos(next_pos, parent2->getPosition())) {
		std::cout << "Nowe zwierze nie znalazlo miejsca obok prodzicow wiec umarlo :(\n";
		return;
	}

	world.addOrganism(SHEEP, next_pos);

}