#include "Human.h"
#include <iostream>
#include <conio.h>
Human::Human(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 4, 5, "czlowiek", HUMAN) {
	this->nextMoveDir = NONE;
	this->cooldown = 0;
	this->specialSkillActivated = false;
	this->remainingAbilityUses = 0;
}
void Human::draw() {
	// narysowanie rozonewj emoji usmietego czlowieka
	std::cout << "\033[95m" << (char)02 << "\033[0m";
}

void Human::action() {
	if (nextMoveDir == NONE)
		return;
	Position next_pos = this->getNextPosition(nextMoveDir);
	Organism* otherOrganism;

	switch (next_pos.state) {
	case NOTAVAILABLE:		// brak mozliwosci ruchu
		std::cout << this->getName() << "nie moze sie poruszyc\n";
		break;
	case OCCUPIED:			// fight lub rozmnazanie
		std::cout << "PROBA INTERAKCJI\n";
		otherOrganism = world.getOrganismByPos(next_pos);
		//collision(otherOrganism);
		otherOrganism->collision(this);

		break;
	case AVAILABLE:			// wykonanie ruchu

		std::cout << this->getName() << " moved: (" << next_pos.x << ", " << next_pos.y << ") \n";
		world.moveOrganismOnMap(this, next_pos);
		this->setPosition(next_pos);
		break;
	default:
		std::cout << this->getName() << " pozostal na swojej pozycji\n";
		break;
	}
	nextMoveDir = NONE;
	this->updateUsesAndCooldown();
}

Position Human::getNextPosition(DIRECTION desired_dir) {
	int tmpMoveLen = 1;
	if (this->specialSkillActivated) {
		tmpMoveLen = 2;
	}
	if (this->specialSkillActivated && this->remainingAbilityUses <= 2) {
		if (world.drawTruth(50)) {
			tmpMoveLen = 1;
			std::cout << "Mimo aktywowanej spec. umiej, tym razem niezadzialala";
		}
	}
	Position tmp;
	tmp = this->getPosition();
	switch (desired_dir) {
	case LEFT:
		tmp.x -= tmpMoveLen;	break;
	case RIGHT:
		tmp.x += tmpMoveLen;	break;
	case TOP:
		tmp.y -= tmpMoveLen;	break;
	case BOTTOM:
		tmp.y += tmpMoveLen;	break;
	}
	tmp.state = world.getFieldState(&tmp);
	if (tmp.state != BORDER)
		return tmp;

	if (tmpMoveLen == 2) {				// proba przeskoku o 1 podczas aktywnej umiejetnosci specjalnej
		tmp = this->getPosition();
		switch (desired_dir) {
		case LEFT:
			tmp.x -= 1;		break;
		case RIGHT:
			tmp.x += 1;		break;
		case TOP:
			tmp.y -= 1;		break;
		case BOTTOM:
			tmp.y += 1;		break;
		}
		tmp.state = world.getFieldState(&tmp);
		if (tmp.state != BORDER) 
			return tmp;
	}

	tmp = this->getPosition();
	tmp.state = NOTAVAILABLE;
	return tmp;
}

void Human::setNextMove(DIRECTION next) {
	this->nextMoveDir = next;
}

void Human::getNextMove(int c) {
	switch (c) {
	case KEY_UP:
		this->setNextMove(TOP);
		break;
	case KEY_DOWN:
		this->setNextMove(BOTTOM);
		break;
	case KEY_LEFT:
		this->setNextMove(LEFT);
		break;
	case KEY_RIGHT:
		this->setNextMove(RIGHT);
		break;
	default:

		break;
	}
}
/*
bool Human::specialSkillIsActiv() {
	return this->specialSkillActivated;
}

int Human::getCooldown() {
	return this->cooldown;
}

int Human::getRemainingAbilityUses() {
	return this->remainingAbilityUses;
}*/

void Human::activateSpecialAbitity() {
	if (this->cooldown != 0) {
		std::cout << "Specjalna umiejetnosc nie moze zostac aktywowana - cooldown : " << this->cooldown << " tur\n";
	}
	else {
		std::cout << "Specjalna umiejestnosc czlowieka zostala aktywowana\n";
		this->cooldown = 10;
		this->specialSkillActivated = true;
		this->remainingAbilityUses = 5;
	}
}

void Human::updateUsesAndCooldown() {
	if (this->cooldown == 0)
		return;
	if (this->remainingAbilityUses > 0)
		this->remainingAbilityUses--;
	if(this->cooldown > 0)
		this->cooldown--;

	if (this->remainingAbilityUses == 0) 
		this->specialSkillActivated = false;
		
}

void Human::setSpecialSkillActivated(bool activ) {
	this->specialSkillActivated = activ;
}

void Human::setRemainingAbilityUses(int uses) {
	this->remainingAbilityUses = uses;
}

void Human::setCooldown(int cooldown) {
	this->cooldown = cooldown;
}

std::string Human::toString() {
	std::string	text = "";
	text += std::to_string((int)(this->getOrganismType()));
	text += " ";
	text += std::to_string(this->getAge());
	text += " ";
	text += std::to_string(this->getInitiative());
	text += " ";
	text += std::to_string(this->getStrenght());
	text += " ";
	text += std::to_string(this->getPosition().x);
	text += " ";
	text += std::to_string(this->getPosition().y);
	text += " ";
	text += std::to_string((int)this->specialSkillActivated);
	text += " ";
	text += std::to_string(this->cooldown);
	text += " ";
	text += std::to_string(this->remainingAbilityUses);

	return text;
}
