#pragma once
#include "Common.h"
#include <vector>
class Organism;

using namespace std;

class World {
	Organism*** worldMap;
	vector<Organism*> organismList;
	int worldWidth;
	int worldHeight;						
	int round;								// obecna tura
public:
	World(int w, int h);
	~World();
	void playRound();
	FIELD_STATE getFieldState(Position* position) const;
	Position getNextAvailablePosition(Position current, DIRECTION desired_dir) const;		// zwrocenie wolnej pozycji obok current
	Position getNextPosition(Position current, DIRECTION desired_dir) const;				// zwrocenie losowej pozycji obok current
	void drawWorld();
	void moveOrganismOnMap(Organism* organism, Position position);
	Organism* getOrganismByPos(Position position);											// zwrocenie organizmu z danej pozycji na mapie
	void deleteOrganism(Organism* organism);
private:
	void clearMap();
	void clearPositionOnMap(Position position);
};

