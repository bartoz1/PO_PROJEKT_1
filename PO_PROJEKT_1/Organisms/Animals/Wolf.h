#pragma once
#include "Animal.h"
class Wolf : public Animal {
public:
	Wolf(World& world, int pos_x, int pos_y);
	void draw() override;
	//void giveBirth(Organism* parent2) override;

};

