#include "Animal.h"
#include <stdlib.h>     /* srand, rand */

Animal::Animal(World& world, Position& position, int initiative, int strenght)
	:Organism(world, position, initiative, strenght){

}
void Animal::action() {
	DIRECTION move_to = (DIRECTION) (rand() % 4);
	Position next_pos = world.getNextAvailablePosition(getPosition(), move_to);

	if (next_pos.state == OCCUPIED) {
		//bedzie fight lub ruchanko
	}
	else {

	}
}

void Animal::collision() {

}