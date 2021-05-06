#pragma once
#include "Common.h"
#include <vector>
class Organism;
class Human;
using namespace std;

class World {
	Organism*** worldMap;						// mapa swiata jako tablica organizmow* 2D
	vector<Organism*> organismList;				// wektor z organizmami ulozonymi wdlg kolejnosci ruchu
	vector<Organism*> bornOrganismList;			// wektor z organizmami narodzonymi obecnej rundy
	int worldWidth;
	int worldHeight;						
	int round;									// numer obecnej tury
public:
	World(int w, int h);
	World(int w, int h, int r);
	void playRound();														// rozegnamie ruchow wszystkich organizmow
	void drawWorld();														// wyrysowanie calego swiata
	void moveOrganismOnMap(Organism* organism, Position position);			// zmiana polozenia organizmu
	void killOrganism(Organism* organism);									// ustawienie statusu organizmy na niezywy i usuniecie z mapy
	void clearPositionOnMap(Position position);								// wyczyszczenie pozycji na mapie - nadpisanie nulem
	void convertIntoFile();													// zapisanie swiata do pliku
	void upadateOrganizmList();												// dopisanie nowo narodzonych organizmow w odpowiednie miejsca wektora
	
	bool drawTruth(int percent) const;										// funckja losuj¹ca (prawda lub falsz) z prawdopo procent %
	bool areDifferentPos(Position pos1, Position pos2) const;				// sprawdzenie czy podane pozycje sa rozne
	FIELD_STATE getFieldState(Position* position) const;					// zwrocenie statusu wskazywanego pola
	Organism* getOrganismByPos(Position position) const;					// zwrocenie organizmu z danej pozycji na mapie
	
	void addOrganism(ORGANISMS organismType, Position position);
	Organism* addHuman();													// dodanie czlowieka w losowym miejscu na mapie
	
	~World();
private:
	void clearMap();														// nadpisanie calej mapy nullami
	void debugInfo() const;
	void removeDeadOrganisms();												// usuniecie niezywych organizmow z wektorow
	Position getRandomAvailablePosition();									// zwraca pusta pozycje na mapie wybrana losowo


};

