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
	std::cout << "=========================\n";
	std::cout << "1. Rozpocznij nowa gre\n";
	std::cout << "2. wczytaj gre z pliku\n";
	std::cout << "3. wylacz\n";
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
	std::cout << "1. Wczytaj stan gry\n";
	if(world != nullptr )
		std::cout << "2. Zapisz obecny stan gry\n";
	std::cin >> odp;
	if (odp == "1") {
		this->loadWorld();
		return;
	}
	else if (odp == "2" && world != nullptr && human != nullptr) {
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
	std::cout << "Podaj szerokosc mapy: ";
	std::cin >> w;
	std::cout << "Podaj wysokosc mapy: ";
	std::cin >> h;
	if (world != nullptr) {
		delete world;
	}
	if (human != nullptr) {
		delete human;
	}
	
	world = new World(w, h);
	human = (Human*)(Animal*)world->addHuman();
}

void Engine::deleteWorld() {
	if (world != nullptr) {
		delete world;
	}
	if (human != nullptr) {
		delete human;
	}
}

void Engine::startGame() {
	int c = 0;
	system("CLS");
	world->drawWorld();
	while (c != KEY_ESC) {
		c = _getch();
		if (c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT || c == KEY_UP) {
			human->getNextMove(c);
			world->playRound();
			world->drawWorld();
		}

	}
	system("CLS");
	drawSaveMenu();
	//c = _getch();
	startGame();
}

void Engine::saveWorld() {
	
}

void Engine::loadWorld() {
	ifstream saveFile;
	saveFile.open("save.txt");
	std::string line;
	if (!saveFile.good()) {
		std::cout << "wystapil problem z wczytanie zapisu\n";
		std::cin >> line;
		return;
	}
	getline(saveFile, line);
	vector <string> tokens;
	stringstream check1(line);

	string inter;
	int width, height, round;

	while (getline(check1, inter, ' ')) {
		tokens.push_back(inter);
	}
	width = stoi(tokens[0]);
	height = stoi(tokens[1]);
	round = stoi(tokens[0]);
	
	world = new World(width, height, round);
	tokens.clear();

	ORGANISMS type;
	
	Position pos;
	int age, initiative, strenght;
	while (getline(saveFile, line)) {
		std::cout << line<<endl;
		stringstream check2(line);


		while (getline(check2, inter, ' ')) {
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
			//pobranie coldowny specjalnej umiejetnosci
			human = (Human*)(Animal*)newOrganism;
		}


		tokens.clear();
	}
	world->upadateOrganizmList();

}
