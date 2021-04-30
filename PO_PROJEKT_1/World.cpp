#include "World.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	// remove and remove_if
#include "Organisms/Animals/Wolf.h"
#include "Organisms/Animals/Sheep.h"
#include "Organisms/Animals/Fox.h"
#include "Organisms/Animals/Turtle.h"
#include "Organisms/Animals/Antelope.h"
#include "Organisms/Animals/Human.h"
#include "Organisms/Plants/Grass.h"

World::World(int w, int h)
	:worldHeight(h), worldWidth(w) {

	round = 0;
	worldMap = new Organism**[h];

	for (int i = 0; i < worldHeight; i++) {
		worldMap[i] = new Organism*[w];	
	}
	clearMap();
	srand(time(NULL));
	Position pozycja;
	// dodawanie zwierzat w losowe miejsca
	for (int i = (int)WOLF;i < (int)CYBER_SHEEP; i += 1) {
		for (int j = 0; j < 2;j++) {
			pozycja = getRandomAvailablePosition();
			if (pozycja.state == NOTAVAILABLE)
				break;
			this->addOrganism((ORGANISMS)i, pozycja);
		}

	}
}
World::~World() {

	for (int i = 0; i < worldHeight; i++) {
		//delete[] worldMap[i];
	}
	//delete[] worldMap;
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
	//std::cout << "+";
	std::cout << (char)201;
	for (int j = 0; j < worldWidth * 2 + 1;j++)
		std::cout << (char)205;
		//std::cout << "-";
	std::cout << (char)187;
	//std::cout << '+';
	std::cout << '\n';

	for (int i = 0; i < worldHeight; i++) {
		//std::cout << "| ";
		std::cout << (char)186<<" ";
		for (int j = 0; j < worldWidth;j++) {
			//std::cout << "\033[32m" << worldMap[i][j] << "\033[0m" << " ";
			if (worldMap[i][j] == nullptr)
				std::cout <<"-";
			else
				worldMap[i][j]->draw();
			std::cout << " ";
		}
		//std::cout << '|';
		std::cout << (char)186;
		std::cout << '\n';
	}
	//std::cout << "+";
	std::cout << (char)200;
	for (int j = 0; j < worldWidth*2+1;j++)
		std::cout << (char)205;
		//std::cout << "-";
	//std::cout << '+';
	std::cout << (char)188;
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
	if(worldMap[organism->getPosition().y][organism->getPosition().x] == organism)
		worldMap[organism->getPosition().y][organism->getPosition().x] = nullptr;
	organismList.erase(std::remove(organismList.begin(), organismList.end(), organism), organismList.end());
	bornOrganismList.erase(std::remove(bornOrganismList.begin(), bornOrganismList.end(), organism), bornOrganismList.end());
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
		newOrganism = new Sheep(*this, position.x, position.y);
		break;
	case FOX:
		newOrganism = new Fox(*this, position.x, position.y);
		break;
	case TURTLE:
		newOrganism = new Turtle(*this, position.x, position.y);
		break;
	case ANTELOPE:
		newOrganism = new Antelope(*this, position.x, position.y);
		break;
	case CYBER_SHEEP:
		break;
	case GRASS:
		newOrganism = new Grass(*this, position.x, position.y);
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

bool World::drawTruth(int percent) {
	if (rand() % 101 < percent) {
		return true;
	}
	return false;
}

Organism* World::addHuman() {

	//Human* marek = new Human(*this, 7, 7);
	//this.moveOrganismOnMap(marek, { 7,7 });
	worldMap[7][7] = new Human(*this, 7, 7);
	organismList.push_back(worldMap[7][7]);

	return worldMap[7][7];
}


void World::playRound() {
	debugInfo();
	int licznik=0;
	/*for (Organism* organism : organismList) {
		if (organism != nullptr) {
			organism->action();
			organism->incrementAge();

		}
		
	}*/
	for (int i = 0; i < organismList.size(); i++) {
		if (organismList[i] != nullptr) {
			organismList[i]->incrementAge();
			organismList[i]->action();
		}
		licznik++;

	}
	upadateOrganizmList();

}

void World::debugInfo() {
	std::cout << "====DEBUG INFO====\n";
	for (Organism* organism : organismList) {
		std::cout << organism->getName() << "( " << organism->getPosition().x << ", " << organism->getPosition().y << " )\n";
	}
	std::cout << "narodzone:\n";
	for (Organism* organism : bornOrganismList) {
		std::cout << organism->getName() << "( " << organism->getPosition().x << ", " << organism->getPosition().y << " )\n";
	}
	std::cout << "====DEBUG INFO====\n";
}

Position World::getRandomAvailablePosition() {
	Position tmp;
	for (int i = 0; i < 150; i++) {
		tmp.x = rand() % worldWidth;
		tmp.y = rand() % worldHeight;
		if (getFieldState(&tmp) == AVAILABLE)
			return tmp;
	}

	return Position({ 0,0,NOTAVAILABLE });
}
