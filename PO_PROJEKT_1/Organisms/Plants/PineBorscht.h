#pragma once
#include "Plant.h"
class PineBorscht :	public Plant {
public:
	PineBorscht(World& world, int pos_x, int pos_y);
	void draw() override;
	void action() override;
	void collision(Organism* otherOrganism) override;
private:
	void killNearAnimals();			// zabicie zwierzat na sasiednich polach
};

