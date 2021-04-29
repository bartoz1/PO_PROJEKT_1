#pragma once
#include "../Organism.h"
#include <string>

class Animal abstract: public Organism {
public:
	Animal(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name);
	void action() override;
	void collision(Organism* otherOrganism) override;
private:
	bool isSameAnimalType(Organism* animal1, Organism* animal2);
	virtual void giveBirth(Organism* parent2) = 0;
};

