#include "Antelope.h"
#include <iostream>

Antelope::Antelope(World& world, int pos_x, int pos_y) 
	:Animal(world, pos_x, pos_y, 4, 4, "antylopa", ANTELOPE) {

}

void Antelope::draw() {
	std::cout << "A";
}

Position Antelope::getNextPosition(DIRECTION desired_dir) {
	Position tmp;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		for (int j = 2; j > 0; j--) {
			tmp = this->getPosition();
			switch (desired_dir) {
			case LEFT:
				tmp.x-=j;
				break;
			case RIGHT:
				tmp.x+= j;
				break;
			case TOP:
				tmp.y-= j;
				break;
			case BOTTOM:
				tmp.y+= j;
				break;
			}
			tmp.state = world.getFieldState(&tmp);
			if (tmp.state != BORDER) {
				return tmp;

			}
			desired_dir = (DIRECTION)((desired_dir + 1) % 4);
		}
	}
	tmp = this->getPosition();
	tmp.state = NOTAVAILABLE;
	return tmp;
}
void Antelope::collision(Organism* otherOrganism) {

	if (isSameAnimalType(otherOrganism)) {
		if (otherOrganism->getAge() > 3 && this->getAge() > 3)
			giveBirth(otherOrganism);
		else
			std::cout << "rozmnazanie " << this->getName() << " z " << otherOrganism->getName() << " jest niemozliwe ze wzgledu na wiek\n";
	}
	else {
		if (world.drawTruth(50)) {
			Position tmp = this->getPosition();
			Position next_pos = this->getNextAvailablePosition(tmp, LEFT);
			if (world.areDifferentPos(next_pos, this->getPosition())) {
				std::cout << this->getName() << " uciekla przed " << otherOrganism->getName() << "\n";
				world.moveOrganismOnMap(this, next_pos);
				world.moveOrganismOnMap(otherOrganism, tmp);
				return;
			};
		}
		if (this->willSurviveAttack(*otherOrganism)) {
			// smierc atakujacego zwierzecia
			std::cout << otherOrganism->getName() << " zmarl wykonujac atak na " << this->getName() << "\n";
			world.killOrganism(otherOrganism);
		}
		else {
			std::cout << otherOrganism->getName() << " zabilo " << this->getName() << "\n";
			world.moveOrganismOnMap(otherOrganism, this->getPosition());
			world.killOrganism(this);

		}
	}
	
}