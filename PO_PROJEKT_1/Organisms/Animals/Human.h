#pragma once
#include "Animal.h"
class Human : public Animal {
	Human(World& world, int pos_x, int pos_y);
	void draw() override;

};

