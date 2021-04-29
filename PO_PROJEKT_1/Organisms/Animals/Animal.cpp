#include "Animal.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */

Animal::Animal(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name)
	:Organism(world, pos_x, pos_y, initiative, strenght, name){

}
void Animal::action() {
	DIRECTION move_to = (DIRECTION) (rand() % 4);
	Position next_pos = world.getNextPosition(getPosition(), move_to);
	Organism* otherOrganism;

	switch (next_pos.state)	{
	case NOTAVAILABLE:		// brak mozliwosci ruchu
		
		break;
	case OCCUPIED:			// fight lub rozmnazanie
		std::cout << "PROBA INTERAKCJI\n";
		otherOrganism = world.getOrganismByPos(next_pos);
		collision(otherOrganism);

		break;
	case AVAILABLE:			// wykonanie ruchu
		
		std::cout << "move: (" << next_pos.x << ", " << next_pos.y << ") \n";
		world.moveOrganismOnMap(this, next_pos);
		this->setPosition(next_pos);
		break;
	default:
		std::cout << "Wystapil blad podczas wybierania nowej pozycji";
		break;
	}
	//this->incrementAge();
}

void Animal::collision(Organism* otherOrganism) {

	if (isSameAnimalType(this, otherOrganism)) {

		giveBirth(otherOrganism);

	}
	else if (otherOrganism->willSurviveAttack(*this)) {
		// smierc tego zwierzecia
		std::cout << "Zwierze atakujace umarlo \n";
		world.deleteOrganism(this);
	}
	else {
		std::cout << "Zwierze atakujace pokonalo przeciwnika \n";
		// usuniecie enemy
		world.deleteOrganism(otherOrganism);

	}
}

bool Animal::isSameAnimalType(Organism* animal1, Organism* animal2) {
	if (animal1->getName() == animal2->getName())
		return true;
	return false;
}

