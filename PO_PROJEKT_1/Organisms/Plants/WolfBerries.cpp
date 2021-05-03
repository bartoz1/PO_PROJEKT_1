#include "WolfBerries.h"
#include <iostream>

WolfBerries::WolfBerries(World& world, int pos_x, int pos_y)
	:Plant(world, pos_x, pos_y, 0, 99, "wilcze jagody", WOLF_BERRIES) {
}

void WolfBerries::draw(){
	std::cout << "\033[34m" << "J" << "\033[0m";
}

void WolfBerries::collision(Organism* otherOrganism) {
	std::cout << otherOrganism->getName() << " zjadl " << this->getName() << " i umarl"<< "\n";
	world.moveOrganismOnMap(otherOrganism, this->getPosition());
	world.killOrganism(otherOrganism);
	world.killOrganism(this);
}