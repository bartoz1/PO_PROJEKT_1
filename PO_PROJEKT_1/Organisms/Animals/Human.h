#pragma once
#include "Animal.h"
class Human : public Animal {
	DIRECTION nextMoveDir;
	bool specialSkillActivated;
	int remainingAbilityUses;		
	int cooldown;							// cooldown specjalnej umiejestnosci
public:
	Human(World& world, int pos_x, int pos_y);
	void draw() override;
	void action() override;
	void activateSpecialAbitity();			// aktywowanie(lub nie) umiejetnosci specjalnej
	Position getNextPosition(DIRECTION desired_dir) override;
	void getNextMove(int c);
	void setNextMove(DIRECTION next);
	void setSpecialSkillActivated(bool activ);
	void setRemainingAbilityUses(int uses);
	void setCooldown(int cooldown);
	std::string toString();					// zapisanie wystkich wartosci obiektu do stringa i zwrocenie go
private:
	void updateUsesAndCooldown();			// aktualizaja cooldownu i licz. mozliwych uzyc umiejetnosci specjalnej

};

