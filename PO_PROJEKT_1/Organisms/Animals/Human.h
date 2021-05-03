#pragma once
#include "Animal.h"
class Human : public Animal {
	DIRECTION nextMoveDir;
	bool specialSkillActivated;
	int remainingAbilityUses;
	int cooldown;
public:
	Human(World& world, int pos_x, int pos_y);
	void draw() override;
	void action() override;
	void activateSpecialAbitity();
	void updateUsesAndCooldown();
	Position getNextPosition(DIRECTION desired_dir) override;
	void setNextMove(DIRECTION next);
	void getNextMove(int c);
	//bool specialSkillIsActiv();
	//int getCooldown();
	//int getRemainingAbilityUses();
	void setSpecialSkillActivated(bool activ);
	void setRemainingAbilityUses(int uses);
	void setCooldown(int cooldown);
	std::string toString();
	//Position getNextPosition(DIRECTION desired_dir) override;
	//void collision(Organism* otherOrganism) override;

};

