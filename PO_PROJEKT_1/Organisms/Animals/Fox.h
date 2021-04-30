#pragma once
#include "Animal.h"
class Fox :	public Animal {
public:
	Fox(World& world, int pos_x, int pos_y);
	void draw() override;
	Position getNextPosition(DIRECTION desired_dir) override;
};

