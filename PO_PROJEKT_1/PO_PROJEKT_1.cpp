#include <iostream>
//#include "World.h"
//#include "Common.h"
//#include "Organisms/Organism.h"
//#include "Organisms/Animals/Human.h"
//#include "Organisms/Animals/Animal.h"
#include "Engine.h"
//#include <conio.h>


using namespace std;

int main() {
    
    Engine engine;
    engine.drawMainMenu();
    engine.startGame();

    /*std::string wejscie;
    World mars(10, 10);
    Human* marek = (Human*)(Animal*)mars.addHuman();
    int c = 0;
    mars.drawWorld();
    while (wejscie != "x") {
        c = _getch();

        marek->getNextMove(c);
        
        mars.playRound();
        mars.drawWorld();
        
    }*/

    /*for (int i = 0; i < 20; i++) {
        mars.playRound();
        mars.drawWorld();
    }*/
    
}

