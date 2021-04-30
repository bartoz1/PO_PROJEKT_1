#pragma once
#include "Plant.h"
class Guarana :	public Plant {
public:
	Guarana(World& world, int pos_x, int pos_y);
	void draw() override;
	void collision(Organism* otherOrganism) override;

};

