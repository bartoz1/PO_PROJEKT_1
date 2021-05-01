#pragma once
#include "Animal.h"
class Human : public Animal {
public:
	DIRECTION nextMoveDir;
	Human(World& world, int pos_x, int pos_y);
	void draw() override;
	void action() override;
	Position getNextPosition(DIRECTION desired_dir) override;
	void setNextMove(DIRECTION next);
	void getNextMove(int c);
	//Position getNextPosition(DIRECTION desired_dir) override;
	//void collision(Organism* otherOrganism) override;

};

