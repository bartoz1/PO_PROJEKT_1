#pragma once
#include "../Organism.h"

class Animal abstract: public Organism {
public:
	Animal(World& world, int pos_x, int pos_y, int initiative, int strenght);
	void action() override;
	void collision() override;
};

