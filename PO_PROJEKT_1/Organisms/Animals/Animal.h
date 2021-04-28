#pragma once
#include "../Organism.h"

class Animal abstract: public Organism {
	Animal(World& world, Position& position, int initiative, int strenght);
	void action() override;
	void collision() override;
};

