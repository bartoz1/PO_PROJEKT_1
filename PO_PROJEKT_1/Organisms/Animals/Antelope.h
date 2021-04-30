#pragma once
#include "Animal.h"
class Antelope : public Animal {
public:
	Antelope(World& world, int pos_x, int pos_y);
	void collision(Organism* otherOrganism);
	void draw();
	Position getNextPosition(DIRECTION desired_dir) override;
};

