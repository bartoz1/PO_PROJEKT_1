#include "PineBorscht.h"
#include <iostream>

PineBorscht::PineBorscht(World& world, int pos_x, int pos_y)
	:Plant(world, pos_x, pos_y, 0, 99, "barszcz sosnowskiego", PINE_BORSCHT) {
}

void PineBorscht::draw() {
	std::cout << "\033[31m" << "B" << "\033[0m";
}

void PineBorscht::collision(Organism* otherOrganism) {
	std::cout << otherOrganism->getName() << " zjadl " << this->getName() << " i umarl" << "\n";
	world.moveOrganismOnMap(otherOrganism, this->getPosition());
	world.killOrganism(otherOrganism);
	world.killOrganism(this);
}
void PineBorscht::action() {

	this->killNearAnimals();

	// rozszadzanie (5% prawdopodobienstwa)
	if (!world.drawTruth(5))
		return;

	Position tmpPos = getNextAvailablePosition(this->getPosition(), RIGHT);
	if (tmpPos.state == AVAILABLE) {
		world.addOrganism(this->getOrganismType(), tmpPos);
	}
}

void PineBorscht::killNearAnimals() {
	Position tmp;
	DIRECTION desired_dir = LEFT;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich sasiednich polach
		tmp = this->getPosition();
		desired_dir = (DIRECTION)((desired_dir + 1) % 4);
		switch (desired_dir)
		{
		case LEFT:
			tmp.x--;
			break;
		case RIGHT:
			tmp.x++;
			break;
		case TOP:
			tmp.y--;
			break;
		case BOTTOM:
			tmp.y++;
			break;
		}
		if (world.getFieldState(&tmp) == OCCUPIED) {	// jezeli na polu tmp znajduje sie organizm
			ORGANISMS type = world.getOrganismByPos(tmp)->getOrganismType();
			if (type == HUMAN || type == WOLF || type == SHEEP ||
				type == FOX || type == TURTLE || type == ANTELOPE) {
				std::cout << this->getName() << " zabil sasiednie zwierze: " << world.getOrganismByPos(tmp)->getName() << "\n";
				world.killOrganism(world.getOrganismByPos(tmp));
			}
		}

	}
	
}
