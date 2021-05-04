#include "Dandelion.h"
#include <iostream>

Dandelion::Dandelion(World& world, int pos_x, int pos_y)
	:Plant(world, pos_x, pos_y, 0, 0, "mlecz", DANDELION) {
}

void Dandelion::draw() {
	std::cout << "\033[33m" << (char)15 << "\033[0m";
}
void Dandelion::action() {
	for (int i = 0;i < 3; i++) {	// trzykrotna proba rozsadzenia sie
		if (world.drawTruth(PLANT_GROWTH)) {
			Position tmpPos = getNextAvailablePosition(this->getPosition(), RIGHT);
			if (tmpPos.state == AVAILABLE) {
				world.addOrganism(this->getOrganismType(), tmpPos);
			}
		}
	}
}