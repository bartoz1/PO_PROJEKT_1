#pragma once
#include "Plant.h"
class WolfBerries :	public Plant {
public:
	WolfBerries(World& world, int pos_x, int pos_y);
	void draw() override;
	void collision(Organism* otherOrganism) override;
};

