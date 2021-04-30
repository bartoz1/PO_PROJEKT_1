#include "Guarana.h"
#include <iostream>

Guarana::Guarana(World& world, int pos_x, int pos_y)
	:Plant(world, pos_x, pos_y, 0, 0, "guarana", GUARANA) {
}

void Guarana::draw() {
	std::cout << "\033[31m" << "g" << "\033[0m";
}

void Guarana::collision(Organism* otherOrganism) {
	std::cout << otherOrganism->getName() << " zjadl " << this->getName() << "\n";
	world.moveOrganismOnMap(otherOrganism, this->getPosition());
	world.deleteOrganism(this);
	otherOrganism->setStrenght(otherOrganism->getStrenght() + 3);
}