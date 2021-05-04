#include "Plant.h"
#include <iostream>

Plant::Plant(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type)
	:Organism(world, pos_x, pos_y, initiative, strenght, name, type){
}

void Plant::action() {
	if (!world.drawTruth(PLANT_GROWTH))
		return;

	Position tmpPos = getNextAvailablePosition(this->getPosition(), RIGHT);
	if (tmpPos.state == AVAILABLE) {
		world.addOrganism(this->getOrganismType(), tmpPos);
	}
}

void Plant::collision(Organism* otherOrganism) {
	std::cout << otherOrganism->getName() << " zjadl " << this->getName() << "\n";
	world.moveOrganismOnMap(otherOrganism, this->getPosition());
	world.killOrganism(this);
}
