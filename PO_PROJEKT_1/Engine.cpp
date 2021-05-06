#include "Engine.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>

Engine::Engine() {
	human = nullptr;
	world = nullptr;
}
void Engine::drawMainMenu() {
	std::string odp;
	system("CLS");
	std::cout << "Symulator swiata \n";
	std::cout << "Bartosz Zylwis 184477 gr4\n";
	std::cout << "poruszanie sie - strzalki | umiejetnosc - s\n";
	std::cout << "=========================\n";
	std::cout << "1. Rozpocznij nowa gre\n";
	std::cout << "2. wczytaj gre z pliku\n";
	std::cout << "3. oznaczenia zwierzat i roslin\n";
	std::cout << "4. wylacz\n";
	std::cin >> odp;

	if (odp == "1") {
		this->createWorld();
		return;
	}
	else if (odp == "2") {
		drawSaveMenu();
		return;

	}
	else if (odp == "3") {
		drawInfo();
		drawMainMenu();
		return;
	}
	else if (odp == "4") {
		delete human;
		delete world;
		exit(0);
	}
	else {
		drawMainMenu();
	}
}

void Engine::drawSaveMenu() {
	std::string odp;
	system("CLS");
	std::cout << "Symulator swiata \n";
	std::cout << "Bartosz Zylwis 184477 gr4\n";
	std::cout << "=========================\n";
	std::cout << "0. Powrot\n";
	std::cout << "1. Nowa gra\n";
	std::cout << "2. Wczytaj stan gry\n";
	if(world != nullptr )
		std::cout << "3. Zapisz obecny stan gry\n";
	std::cin >> odp;
	if (odp == "1") {
		this->deleteWorld();
		this->createWorld();
	}
	else if (odp == "2") {
		this->loadWorld();
		return;
	}
	else if (odp == "3" && world != nullptr && human != nullptr) {
		world->convertIntoFile();
		return;
	}
	else if (odp == "0") {
		return;
	}
	else {
		drawSaveMenu();
	}
}

void Engine::createWorld() {
	int w, h;
	system("CLS");
	std::cout << "Symulator swiata \n";
	std::cout << "Bartosz Zylwis 184477 gr4\n";
	std::cout << "=========================\n";
	std::cout << "Podaj szerokosc mapy: ";
	std::cin >> w;
	std::cout << "Podaj wysokosc mapy: ";
	std::cin >> h;
	this->deleteWorld();
	
	world = new World(w, h);
	human = (Human*)(Animal*)world->addHuman();
}

void Engine::deleteWorld() {
	if (world != nullptr) {
		delete world;
		world = nullptr;
		human = nullptr;
	}
}

void Engine::drawInfo() const{
	system("CLS");
	std::cout << "Symulator swiata \n";
	std::cout << "Bartosz Zylwis 184477 gr4\n";
	std::cout << "==============================\n";
	std::cout << "OZNACZENIA ROSLIN I ZWIERZAT\n";
	std::cout << "\033[95m" << (char)02 << "\033[0m" << " - czlowiek\n";
	std::cout << "\033[32m" << (char)05 << "\033[0m" << " - trawa\n";
	std::cout << "\033[33m" << (char)15 << "\033[0m" << " - mlecz\n";
	std::cout << "\033[31m" << "g" << "\033[0m" << " - guarana\n";
	std::cout << "\033[34m" << "J" << "\033[0m" << " - wilcze jagody\n";
	std::cout << "\033[31m" << "B" << "\033[0m" << " - barszcz sosnowskiego\n";
	std::cout <<  "W" << " - wilk\n";
	std::cout << "\033[97m" << "O" << "\033[0m" << " - owca\n";
	std::cout <<  "L" << " - lis\n";
	std::cout <<  "Z" << " - zolw\n";
	std::cout <<  "A" << " - antylopa\n";
	std::cout << "==============================\n";
	std::cout << "kliknij przycisk by powrocic\n";
	_getch();

}

void Engine::startGame() {
	int c = 0;
	//system("CLS");
	world->drawWorld();
	while (c != KEY_ESC) {
		c = _getch();
		if (human->isAlive()) {
			if (c == LETTER_S || c == LETTER_s)	
				human->activateSpecialAbitity();
			if (c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP) {
				human->getNextMove(c);
				world->playRound();
				world->drawWorld();
			}
		}
		else if (c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP) {											// kontynuowanie symulacji po smierci czlowieka
			world->playRound();
			world->drawWorld();
		}
	}
	//system("CLS");
	drawSaveMenu();
	startGame();
}

Engine::~Engine() {
	this->deleteWorld();
}

void Engine::loadWorld() {
	ifstream saveFile;
	saveFile.open("save.txt");
	std::string line;
	if (!saveFile.good()) {
		std::cout << "nie posiadasz zapisu gry!\n";
		std::cout << "kliknij dowolny przycisk by zakonczyc\n";
		_getch();
		exit(0);
		return;
	}
	getline(saveFile, line);
	vector <string> tokens;			// wektor z wartosciami swiata / organizmu
	stringstream check1(line);

	string inter;
	int width, height, round;
	while (getline(check1, inter, ' ')) {
		tokens.push_back(inter);
	}
	width = stoi(tokens[0]);
	height = stoi(tokens[1]);
	round = stoi(tokens[2]);
	
	world = new World(width, height, round);
	tokens.clear();

	ORGANISMS type;
	Position pos;
	int age, initiative, strenght, cooldown, uses;
	bool SSactiv;
	while (getline(saveFile, line)) {
		std::cout << line<<endl;
		stringstream check2(line);

		while (getline(check2, inter, ' ')) {			// rozdzielenie elementow w jednej linii
			tokens.push_back(inter);
		}
		type = (ORGANISMS)stoi(tokens[0]);
		age = stoi(tokens[1]);
		initiative = stoi(tokens[2]);
		strenght = stoi(tokens[3]);
		pos.x = stoi(tokens[4]);
		pos.y = stoi(tokens[5]);
		
		world->addOrganism(type, pos);
		Organism* newOrganism = world->getOrganismByPos(pos);
		newOrganism->setStrenght(strenght);
		newOrganism->setAge(age);
		newOrganism->setInitiative(initiative);
		if (type == HUMAN) {
			// specjalne wartosci wystepujace u czlowieka
			SSactiv = (bool)stoi(tokens[6]);
			cooldown = stoi(tokens[7]);
			uses = stoi(tokens[8]);
			human = (Human*)(Animal*)newOrganism;
			human->setSpecialSkillActivated(SSactiv);
			human->setCooldown(cooldown);
			human->setRemainingAbilityUses(uses);
		}
		tokens.clear();
	}
	world->upadateOrganizmList();
}
