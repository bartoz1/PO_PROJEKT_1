#pragma once
#include "Plant.h"
class Dandelion : public Plant {
public:
	Dandelion(World& world, int pos_x, int pos_y);
	void draw() override;
	void action() override;
};

