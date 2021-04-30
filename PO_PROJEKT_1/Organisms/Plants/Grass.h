#pragma once
#include "Plant.h"
class Grass : public Plant {
public:
	Grass(World& world, int pos_x, int pos_y);
	void draw() override;
};

