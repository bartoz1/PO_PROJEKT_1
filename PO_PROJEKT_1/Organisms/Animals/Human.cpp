#include "Human.h"
#include <iostream>
#include <conio.h>
Human::Human(World& world, int pos_x, int pos_y)
	:Animal(world, pos_x, pos_y, 4, 5, "czlowiek", HUMAN) {
	nextMoveDir = NONE;
}
void Human::draw() {
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

		std::cout << "move: (" << next_pos.x << ", " << next_pos.y << ") \n";
		world.moveOrganismOnMap(this, next_pos);
		this->setPosition(next_pos);
		break;
	default:
		std::cout << this->getName() << " pozostal na swojej pozycji\n";
		break;
	}
	nextMoveDir = NONE;
}

Position Human::getNextPosition(DIRECTION desired_dir) {

	Position tmp;
	tmp = this->getPosition();
	switch (desired_dir) {
	case LEFT:
		tmp.x--;
		break;
	case RIGHT:
		tmp.x++;
		break;
	case TOP:
		tmp.y--;
		break;
	case BOTTOM:
		tmp.y++;
		break;
	}
	tmp.state = world.getFieldState(&tmp);
	if (tmp.state != BORDER) {
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
