#pragma once
#include "Plant.h"
class PineBorscht :	public Plant {
public:
	PineBorscht(World& world, int pos_x, int pos_y);
	void draw()const override;
	void collision(Organism* otherOrganism) override;
	void action() override;
private:
	void killNearAnimals();
};

