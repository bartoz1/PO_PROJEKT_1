#include "World.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	// remove and remove_if
#include <stdlib.h>
#include <fstream>
#include "Organisms/Animals/Wolf.h"
#include "Organisms/Animals/Sheep.h"
#include "Organisms/Animals/Fox.h"
#include "Organisms/Animals/Turtle.h"
#include "Organisms/Animals/Antelope.h"
#include "Organisms/Animals/Human.h"
#include "Organisms/Plants/Grass.h"
#include "Organisms/Plants/Dandelion.h"
#include "Organisms/Plants/Guarana.h"
#include "Organisms/Plants/PineBorscht.h"
#include "Organisms/Plants/WolfBerries.h"

World::World(int w, int h)
	:worldHeight(h), worldWidth(w) {

	round = 0;

	// tworzenie mapy 2D (tablica 2D)
	worldMap = new Organism**[h];
	for (int i = 0; i < worldHeight; i++) {
		worldMap[i] = new Organism*[w];	
	}
	
	clearMap();
	srand(time(NULL));
	Position pozycja;
	int liczbaOrg = 0;
	// dodawanie zwierzat i roslin w losowe miejsca
	for (int i = (int)WOLF;i < (int)CYBER_SHEEP; i += 1) {
		liczbaOrg = 2;
		int g = ((w * h) / 10) / 5;
		if (i != PINE_BORSCHT)			
			liczbaOrg = 2 + rand() % (1+ ((w*h)/10)/5);				// urozmaicenie liczcby wystapien zwierzat danego gatunku
		
		for (int j = 0; j < liczbaOrg;j++) {
			pozycja = getRandomAvailablePosition();
			if (pozycja.state == NOTAVAILABLE)
				break;
			this->addOrganism((ORGANISMS)i, pozycja);
		}
	}
	this->upadateOrganizmList();
}
//konstruktor uzywany podczas wczytywania swiata z pliku
World::World(int w, int h, int r)	
	:worldHeight(h), worldWidth(w), round(r) {

	// tworzenie mapy 2D (tablicy 2D)
	worldMap = new Organism **[h];
	for (int i = 0; i < worldHeight; i++) {
		worldMap[i] = new Organism * [w];
	}
	clearMap();
	srand(time(NULL));
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
// usuniecie niezywych i dodanie nowo narodzonych organizmow do odpowiednich miejsc w organismList
void World::upadateOrganizmList() {
	this->removeDeadOrganisms();
	int insert_at;
	Organism* insert_before;

	for (Organism* bornOrganism : bornOrganismList) {
		if (organismList.size() == 0) {
			organismList.push_back(bornOrganism);
		}
		else {
			if (bornOrganism->isAlive()) {
				insert_before = organismList.front();
				insert_at = 0;
				for (Organism* organism : organismList) {
					if (bornOrganism->getInitiative() > organism->getInitiative())
						break;

					insert_at++;
				}
				organismList.insert(organismList.begin() + insert_at, bornOrganism);
			}
		}
	}
	bornOrganismList.clear();
}
void World::moveOrganismOnMap(Organism* organism, Position position) {
	clearPositionOnMap(organism->getPosition());
	worldMap[position.y][position.x] = organism;
	organism->setPosition(position);
}

Organism* World::getOrganismByPos(Position position) const{
	return worldMap[position.y][position.x];
}

void World::killOrganism(Organism* organism) {
	if(worldMap[organism->getPosition().y][organism->getPosition().x] == organism)
		worldMap[organism->getPosition().y][organism->getPosition().x] = nullptr;
	organism->setDeath();
}

void World::addOrganism(ORGANISMS organismType, Position position) {
	Organism* newOrganism = nullptr;
	switch (organismType)
	{
	case HUMAN:
		newOrganism = new Human(*this, position.x, position.y);
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
		newOrganism = new Dandelion(*this, position.x, position.y);
		break;
	case GUARANA:
		newOrganism = new Guarana(*this, position.x, position.y);
		break;
	case WOLF_BERRIES:
		newOrganism = new WolfBerries(*this, position.x, position.y);
		break;
	case PINE_BORSCHT:
		newOrganism = new PineBorscht(*this, position.x, position.y);
		break;
	default:
		break;
	}
	bornOrganismList.push_back(newOrganism);
	//return newOrganism;
	
	//dodanie na mape
	worldMap[position.y][position.x] = newOrganism;
}

bool World::areDifferentPos(Position pos1, Position pos2) const {
	if (pos1.x != pos2.x)
		return true;
	if (pos1.y != pos2.y)
		return true;
	return false;
}

bool World::drawTruth(int percent)const {
	if (rand() % 101 < percent) {
		return true;
	}
	return false;
}

Organism* World::addHuman() {
	Position pos = this->getRandomAvailablePosition();
	worldMap[pos.y][pos.x] = new Human(*this, pos.x, pos.y);
	bornOrganismList.push_back(worldMap[pos.y][pos.x]);
	this->upadateOrganizmList();

	return worldMap[pos.y][pos.x];
}

void World::playRound() {
	//debugInfo();
	std::cout << "Runda: " << this->round + 1 << "\n";

	for (int i = 0; i < organismList.size(); i++) {
		if (organismList[i]->isAlive()) {
			organismList[i]->incrementAge();
			organismList[i]->action();
		}

	}
	upadateOrganizmList();
	this->round++;
}

void World::debugInfo() const {
	std::cout << "====DEBUG INFO====\n";
	for (Organism* organism : organismList) {
		std::cout << organism->getName() << "( " << organism->getPosition().x << ", " << organism->getPosition().y << " )\n";
	}
	std::cout << "====DEBUG INFO====\n";
}
// calkowite usuniecie niezywych organizmow z gry
void World::removeDeadOrganisms() {
	vector<Organism*> organismsToBeRemoved;
	for (Organism* curOrganism : organismList) {
		// jezeli gdy obecny organizm jest niezywy
		if (!curOrganism->isAlive())
			organismsToBeRemoved.push_back(curOrganism);
	}
	if (organismsToBeRemoved.size() > 0) {
		for (Organism* delOrganism : organismsToBeRemoved) {
			organismList.erase(std::remove(organismList.begin(), organismList.end(), delOrganism), organismList.end());
			bornOrganismList.erase(std::remove(bornOrganismList.begin(), bornOrganismList.end(), delOrganism), bornOrganismList.end());
			delete delOrganism;
		}
	}
}
// returns random available position on map or position (0,0) with status NOTAVAILABLE
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

void World::convertIntoFile() {
	ofstream saveFile;
	saveFile.open("save.txt");
	saveFile << std::to_string(worldWidth) << " " << std::to_string(worldHeight) << " " << std::to_string(round) << endl;
	for (Organism* cOrganism : organismList) {
		saveFile << cOrganism->toString() << endl;
	}
	saveFile.close();
}
World::~World() {
	this->upadateOrganizmList();
	for (int i = 0; i < worldHeight; i++) {
		for (int j = 0; j < worldWidth;j++) {
			if (worldMap[i][j] != nullptr)
				delete worldMap[i][j];
		}
		delete[] worldMap[i];
	}
	delete[] worldMap;
	worldMap = nullptr;
}