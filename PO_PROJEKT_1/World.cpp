#include "World.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	// remove and remove_if
#include "Organisms/Animals/Wolf.h"
#include "Organisms/Animals/Sheep.h"

World::World(int w, int h)
	:worldHeight(h), worldWidth(w) {

	round = 0;
	worldMap = new Organism**[h];

	for (int i = 0; i < worldHeight; i++) {
		worldMap[i] = new Organism*[w];	
	}
	clearMap();

	worldMap[0][0] = new Wolf(*this, 0, 0);
	organismList.push_back(worldMap[0][0]);

	//worldMap[1][1] = new Wolf(*this, 1, 1);
	//organismList.push_back(worldMap[1][1]);

	worldMap[2][2] = new Wolf(*this, 2, 2);
	organismList.push_back(worldMap[2][2]);

	worldMap[2][0] = new Sheep(*this, 0, 2);
	organismList.push_back(worldMap[2][0]);

	/* initialize random seed: */
	srand(time(NULL));
}
World::~World() {

	for (int i = 0; i < worldHeight; i++) {
		delete[] worldMap[i];
	}
	delete[] worldMap;
}
void World::clearMap() {
	for (int i = 0; i < worldHeight; i++) {
		for (int j = 0; j < worldWidth;j++) {
			worldMap[i][j] = nullptr;
		}
	}
}
// Wyrysowanie swiata wraz z obramowaniem
void World::drawWorld() {
	std::cout << "+";
	for (int j = 0; j < worldWidth * 2 + 1;j++)
		std::cout << "-";
	std::cout << '+';
	std::cout << '\n';

	for (int i = 0; i < worldHeight; i++) {
		std::cout << "| ";
		for (int j = 0; j < worldWidth;j++) {
			//std::cout << "\033[32m" << worldMap[i][j] << "\033[0m" << " ";
			if (worldMap[i][j] == nullptr)
				std::cout << "\033[32m"<<" " << "\033[0m";
			else
				worldMap[i][j]->draw();
			std::cout << " ";
		}
		std::cout << '|';
		std::cout << '\n';
	}
	std::cout << "+";
	for (int j = 0; j < worldWidth*2+1;j++)
		std::cout << "-";
	std::cout << '+';
	std::cout << '\n';
}
FIELD_STATE World::getFieldState(Position *position) const {
	if (position->y >= worldHeight || position->y < 0 || position->x < 0 || position->x >= worldWidth) 
		position->state = BORDER;
	else if (worldMap[position->y][position->x] == nullptr)
		position->state = AVAILABLE;
	else
		position->state = OCCUPIED;
	
	return position->state;
	
}
Position World::getNextAvailablePosition(Position current, DIRECTION desired_dir) const {

	Position tmp;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		tmp = current;
		desired_dir = (DIRECTION)((desired_dir + 1) % 4);
		switch (desired_dir)
		{
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
		if (getFieldState(&tmp) == AVAILABLE)
			return tmp;
	}
	return current;
}

Position World::getNextPosition(Position current, DIRECTION desired_dir) const {

	Position tmp;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		tmp = current;
		switch (desired_dir)	{
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
		if (getFieldState(&tmp) != BORDER )
			return tmp;
		desired_dir = (DIRECTION)((desired_dir + 1) % 4);
	}
	current.state = NOTAVAILABLE;
	return current;
}
void World::clearPositionOnMap(Position position) {
	worldMap[position.y][position.x] = nullptr;
}
// przepisanie bornOrganismList do odpowiednich miejsc w organismList
void World::upadateOrganizmList() {
	int insert_at;
	Organism* insert_before;

	for (Organism* bornOrganism : bornOrganismList) {
		insert_before = organismList.front();
		insert_at = 0;
		for (Organism* organism : organismList) {
			if (bornOrganism->getInitiative() > organism->getInitiative())
				break;

			insert_at++;
		}
		organismList.insert(organismList.begin() + insert_at, bornOrganism);
	}
	bornOrganismList.clear();
}
void World::moveOrganismOnMap(Organism* organism, Position position) {
	clearPositionOnMap(organism->getPosition());
	worldMap[position.y][position.x] = organism;
	organism->setPosition(position);
}

Organism* World::getOrganismByPos(Position position) {
	return worldMap[position.y][position.x];
}

void World::deleteOrganism(Organism* organism) {

	worldMap[organism->getPosition().y][organism->getPosition().y] = nullptr;
	organismList.erase(std::remove(organismList.begin(), organismList.end(), organism), organismList.end());
	delete organism;
}

void World::addOrganism(ORGANISMS organismType, Position position) {
	Organism* newOrganism = nullptr;
	switch (organismType)
	{
	case HUMAN:
		break;
	case WOLF:
		newOrganism = new Wolf(*this, position.x, position.y);
		break;
	case SHEEP:
		break;
	case FOX:
		break;
	case TURTLE:
		break;
	case ANTELOPE:
		break;
	case CYBER_SHEEP:
		break;
	case GRASS:
		break;
	case DANDELION:
		break;
	case GUARANA:
		break;
	case WOLF_BERRIES:
		break;
	case PINE_BORSCHT:
		break;
	default:
		break;
	}
	bornOrganismList.push_back(newOrganism);
	/*
	// dodanie do listy organizmow
	Organism* insert_before = organismList.front();
	int insert_at = 0;
	for (Organism* organism : organismList) {
		if (newOrganism->getInitiative() > organism->getInitiative()) 
			break;
		
		insert_at++;
	}
	organismList.insert(organismList.begin() + insert_at, newOrganism);*/
	//dodanie na mape
	worldMap[position.y][position.x] = newOrganism;
}

bool World::areDifferentPos(Position pos1, Position pos2) {
	if (pos1.x != pos2.x)
		return true;
	if (pos1.y != pos2.y)
		return true;
	return false;
}


void World::playRound() {
	for (Organism* organism : organismList) {
		
		
		organism->action();
		
		organism->incrementAge();
		//std::cout << "+ ";
	}
	//std::cout << "\n";
	upadateOrganizmList();

}