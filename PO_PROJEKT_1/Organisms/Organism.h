#pragma once
#include "../Common.h"
#include "../World.h"
#include <string>

class Organism abstract{
	int strenght;
	int initiative;
	int age;
	Position position;
	std::string name;
	ORGANISMS type;
public:
	//Organism(World& world);
	Organism(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type);
	virtual void action() = 0;
	virtual void collision(Organism* otherOrganism) = 0;
	virtual void draw() = 0;	
	virtual bool willSurviveAttack(Organism& enemy);

	int getStrenght() const;
	int getInitiative() const;
	int getAge() const;
	ORGANISMS getOrganismType() const;
	std::string getName() const;
	Position getPosition() const;
	//World& getWorld() const;

	void setStrenght(int strenght);
	void setInitiative(int initiative);
	void setAge(int age);
	void setName(std::string name);
	void setPosition(Position position);

	void incrementAge();
	void move(int dx, int dy);
protected:
	World& world;
	
private:

	//~Organism();
};

