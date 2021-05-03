#pragma once
#include "Common.h"
#include <vector>
//#include "Organisms/Animals/Human.h"
class Organism;
class Human;
using namespace std;

class World {
	Organism*** worldMap;
	vector<Organism*> organismList;
	vector<Organism*> bornOrganismList;
	int worldWidth;
	int worldHeight;						
	int round;								// obecna tura
public:
	World(int w, int h);
	World(int w, int h, int r);
	~World();
	void playRound();
	FIELD_STATE getFieldState(Position* position) const;
	//Position getNextAvailablePosition(Position current, DIRECTION desired_dir) const;			// zwrocenie wolnej pozycji obok current
	//Position getNextPosition(Position current, DIRECTION desired_dir) const;					// zwrocenie losowej pozycji obok current
	void drawWorld();
	void moveOrganismOnMap(Organism* organism, Position position);
	Organism* getOrganismByPos(Position position);												// zwrocenie organizmu z danej pozycji na mapie
	void killOrganism(Organism* organism);
	void addOrganism(ORGANISMS organismType, Position position);
	bool areDifferentPos(Position pos1, Position pos2);
	bool drawTruth(int percent);																// funckja losuj¹ca (prawda lub falsz) z prawdopo procent %
	Organism* addHuman();
	void convertIntoFile();
	void upadateOrganizmList();
private:
	void clearMap();
	void clearPositionOnMap(Position position);
	void debugInfo();
	void removeDeadOrganisms();
	Position getRandomAvailablePosition();


};

