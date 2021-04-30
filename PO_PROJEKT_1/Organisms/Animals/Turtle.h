#pragma once
#include "Animal.h"
class Turtle : public Animal {
public:
	Turtle(World& world, int pos_x, int pos_y);
	void draw() override;
	Position getNextPosition(DIRECTION desired_dir) override;
	void collision(Organism* otherOrganism) override;
};

