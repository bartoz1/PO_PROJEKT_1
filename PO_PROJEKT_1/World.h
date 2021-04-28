#pragma once
#include "Common.h"
class Organism;

class World {
	Organism*** worldMap;
	int worldWidth;
	int worldHeight;						
	int round;								// obecna tura
public:
	World(int w, int h);
	~World();
	FIELD_STATE getFieldState(Position* position) const;			//todo	
	Position getNextAvailablePosition(Position current, DIRECTION desired_dir) const;
	Position getNextPosition(Position current, DIRECTION desired_dir) const;
	void drawWorld();

protected:
	void clearMap();

};

