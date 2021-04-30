#pragma once
#include "../Organism.h"
#include <string>

class Animal abstract: public Organism {
public:
	Animal(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type);
	virtual void action() override;
	virtual void collision(Organism* otherOrganism) override;
protected:
	virtual Position getNextPosition(DIRECTION desired_dir);
	virtual Position getNextAvailablePosition(Position current, DIRECTION desired_dir);
	bool isSameAnimalType(Organism* animal2);
	void giveBirth(Organism* parent2);
private:
};

