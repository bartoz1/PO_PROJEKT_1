#pragma once
#include "../Common.h"
#include "../World.h"

class Organism abstract{
	int strenght;
	int initiative;
	int age;
	Position position;

public:
	//Organism(World& world);
	Organism(World& world, int pos_x, int pos_y, int initiative, int strenght);
	virtual void action() = 0;
	virtual void collision() = 0;
	virtual void draw() = 0;
	virtual bool willSurviveAttack(Organism& enemy);

	int getStrenght() const;
	int getInitiative() const;
	int getAge() const;
	Position getPosition() const;
	//World& getWorld() const;

	void setStrenght(int strenght);
	void setInitiative(int initiative);
	void setAge(int age);
	void setPosition(Position position);

	void incrementAge();
	void move(int dx, int dy);
protected:
	World& world;
private:

	//~Organism();
};

