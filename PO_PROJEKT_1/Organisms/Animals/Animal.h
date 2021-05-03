#pragma once
#include "../Organism.h"
#include <string>

class Animal abstract: public Organism {
public:
	Animal(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type);
	virtual void action() override;
	virtual void collision(Organism* otherOrganism) override;
	virtual Position getNextPosition(DIRECTION desired_dir);
protected:
	bool isSameAnimalType(Organism* animal2);				// sprawdza czy dany organism jest tego samego typu co obiekt
	void giveBirth(Organism* parent2);						// rozmnazanie organizmow
};

