#include "Animal.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */

Animal::Animal(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type)
	:Organism(world, pos_x, pos_y, initiative, strenght, name, type){

}
void Animal::action() {
	DIRECTION move_to = (DIRECTION) (rand() % 4);
	Position next_pos = getNextPosition(move_to);
	Organism* otherOrganism;

	switch (next_pos.state)	{
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
		std::cout <<this->getName()<< " pozostal na swojej pozycji\n";
		break;
	}
	//this->incrementAge();
}

void Animal::collision(Organism* otherOrganism) {

	if (isSameAnimalType(otherOrganism)) {

		giveBirth(otherOrganism);

	}
	else if (this->willSurviveAttack(*otherOrganism)) {
		// smierc atakujacego zwierzecia
		std::cout <<otherOrganism->getName()<< " zmarl wykonujac atak na"<<this->getName()<<"\n";
		world.deleteOrganism(otherOrganism);
	}
	else {
		std::cout <<otherOrganism->getName() << " zabilo "<<this->getName()<<"\n";
		Position tmp = this->getPosition();
		world.moveOrganismOnMap(otherOrganism, tmp);
		world.deleteOrganism(this);

	}
}

Position Animal::getNextPosition(DIRECTION desired_dir) {
	Position tmp;
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
/*
Position Animal::getNextAvailablePosition(Position current, DIRECTION desired_dir) {
	Position tmp;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		tmp = current;
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
		if (world.getFieldState(&tmp) == AVAILABLE)
			return tmp;
	}
	return current;
}*/

bool Animal::isSameAnimalType(Organism* animal2) {
	if (this->getName() == animal2->getName())
		return true;
	return false;
}

void Animal::giveBirth(Organism* parent2) {
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

	world.addOrganism(this->getOrganismType(), next_pos);
}

