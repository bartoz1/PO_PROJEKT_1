#include "World.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <algorithm>	// remove and remove_if
#include "Organisms/Animals/Wolf.h"

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

	worldMap[1][1] = new Wolf(*this, 1, 1);
	organismList.push_back(worldMap[1][1]);

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
Position World::getNextAvailablePosition(Position current, DIRECTION desired_dir) const{

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

void World::playRound() {
	for (auto& organism : organismList) {
		organism->action();
	}
}