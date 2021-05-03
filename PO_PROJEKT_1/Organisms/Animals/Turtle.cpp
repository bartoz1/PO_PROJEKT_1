#include "Turtle.h"
#include <iostream>

Turtle::Turtle(World& world, int pos_x, int pos_y) 
	:Animal(world, pos_x, pos_y, 1, 2, "zolw", TURTLE) {
}
void Turtle::draw()const {
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

		giveBirth(otherOrganism);

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
/*
void Turtle::action() {
	DIRECTION move_to = (DIRECTION)(rand() % 4);
	Position next_pos = getNextPosition(move_to);
	Organism* otherOrganism;

	switch (next_pos.state) {
	case NOTAVAILABLE:		// brak mozliwosci ruchu
		std::cout << this->getName() << "nie moze sie poruszyc\n";
		break;
	case OCCUPIED:			// fight lub rozmnazanie
		std::cout << "PROBA INTERAKCJI\n";
		otherOrganism = world.getOrganismByPos(next_pos);
		//collision(otherOrganism);
		otherOrganism->collision(this);

		break;
	case AVAILABLE:			// wykonanie ruchu

		std::cout << "move: (" << next_pos.x << ", " << next_pos.y << ") \n";
		world.moveOrganismOnMap(this, next_pos);
		this->setPosition(next_pos);
		break;
	default:
		std::cout << "Wystapil blad podczas wybierania nowej pozycji\n";
		break;
	}
	//this->incrementAge();
}
*/