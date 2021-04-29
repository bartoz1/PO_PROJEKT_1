#include "Animal.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */

Animal::Animal(World& world, int pos_x, int pos_y, int initiative, int strenght)
	:Organism(world, pos_x, pos_y, initiative, strenght){

}
void Animal::action() {
	DIRECTION move_to = (DIRECTION) (rand() % 4);
	Position next_pos = world.getNextPosition(getPosition(), move_to);
	Organism* enemy;

	switch (next_pos.state)	{
	case NOTAVAILABLE:
		// brak mozliwosci ruchu
		break;
	case OCCUPIED:
		// fight lub rozmnazanie
		enemy = world.getOrganismByPos(next_pos);
		if (enemy->willSurviveAttack(*this)) {
			// smierc tego zwierzecia
		}
		else {
			// usuniecie enemy

		}
		break;
	case AVAILABLE:
		// wykonanie ruchu
		std::cout << "move: (" << next_pos.x << ", " << next_pos.y << ") \n";
		world.moveOrganismOnMap(this, next_pos);
		this->setPosition(next_pos);
		break;
	default:
		std::cout << "Wystapil blad podczas wybierania nowej pozycji";
		break;
	}
}

void Animal::collision() {

}