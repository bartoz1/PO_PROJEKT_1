#pragma once
#include "../Common.h"
#include "../World.h"
#include <string>

class Organism abstract{
	bool alive;							// pole mowiace czy organizm jest zywy
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
	virtual bool willSurviveAttack(Organism& enemy);		// sprawdzenie czy organizm przetrwa atak innego organizmy
	virtual Position getNextAvailablePosition(Position current, DIRECTION desired_dir);

	bool isAlive() const;
	int getStrenght() const;
	int getInitiative() const;
	int getAge() const;
	ORGANISMS getOrganismType() const;
	std::string getName() const;
	Position getPosition() const;

	void setStrenght(int strenght);
	void setInitiative(int initiative);
	void setAge(int age);
	void setName(std::string name);
	void setPosition(Position position);
	void setDeath();										// zmiana statusu organizmu na niezywy

	void incrementAge();
	virtual std::string toString();							// zapisanie wystkich wartosci obiektu do stringa i zwrocenie go
protected:
	World& world;
	
};

