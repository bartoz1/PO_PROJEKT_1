#pragma once
#include "Animal.h"
class Sheep : public Animal {
public:
	Sheep(World& world, int pos_x, int pos_y);
	void draw() override;
	

};

