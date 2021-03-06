#pragma once
#include "Common.h"
#include "World.h"
#include "Organisms/Organism.h"
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
class Engine {
	World* world;
	Human* human;
public:
	Engine();
	void drawMainMenu();
	void startGame();					// rozpoczecie symulacji
	~Engine();
private:
	void drawSaveMenu();
	void loadWorld();					// zaladowanie swiata z pliku
	void createWorld();					// stworzenie nowego swiata zgodnie z podanymi arg
	void deleteWorld();					// usuniecie swiata i wszystkich organizmow
	void drawInfo() const;				// wypisanie oznaczen zwirzat i roslin
};

