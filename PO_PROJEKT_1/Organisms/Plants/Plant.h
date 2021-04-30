#pragma once
#include "../Organism.h"
class Plant : public Organism {
public:
	Plant(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type);
	virtual void action() override;
	virtual void collision(Organism* otherOrganism) override;
};

