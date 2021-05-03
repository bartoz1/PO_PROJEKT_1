#include "Turtle.h"
#include <iostream>

Turtle::Turtle(World& world, int pos_x, int pos_y) 
	:Animal(world, pos_x, pos_y, 1, 2, "zolw", TURTLE) {
}
void Turtle::draw() {
	std::cout << "Z";
}
Position Turtle::getNextPosition(DIRECTION desired_dir) {
	Position tmp;
	if (world.drawTruth(75)) {
		return this->getPosition();
	}
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		tmp = this->getPosition();
		switch (desired_dir) {
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
		tmp.state = world.getFieldState(&tmp);
		if (tmp.state != BORDER) {
			return tmp;

		}
		desired_dir = (DIRECTION)((desired_dir + 1) % 4);
	}
	tmp = this->getPosition();
	tmp.state = NOTAVAILABLE;
	return tmp;
}
void Turtle::collision(Organism* otherOrganism) {

	if (isSameAnimalType(otherOrganism)) {
		if (otherOrganism->getAge() > 3 && this->getAge() > 3)
			giveBirth(otherOrganism);
		else
			std::cout << "rozmnazanie " << this->getName() << " z " << otherOrganism->getName() << "jest niemozliwe ze wzgledu na wiek\n";
	}
	else if (otherOrganism->getStrenght() < 5) {
		std::cout << "Zolw przezyl atak " << otherOrganism->getName() << "\n";

	}
	else {
		std::cout << otherOrganism->getName() << " zabilo " << this->getName() << "\n";
		world.moveOrganismOnMap(otherOrganism, this->getPosition());
		world.killOrganism(this);

	}
}
