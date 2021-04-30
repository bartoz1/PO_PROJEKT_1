#include <iostream>
#include "World.h"
#include "Common.h"
#include "Organisms/Organism.h"
#include "Organisms/Animals/Human.h"
#include "Organisms/Animals/Animal.h"
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

int main() {
    std::string wejscie;
    World mars(10, 10);
    Human* marek = (Human*)(Animal*)mars.addHuman();
    //mars.moveOrganismOnMap(marek, { 7,7 });
    mars.drawWorld();
    int c;
    while (wejscie != "x") {
        c = 0;

        switch ((c = _getch())) {
        case KEY_UP:
            marek->setNextMove(TOP);
            break;
        case KEY_DOWN:
            marek->setNextMove(BOTTOM);
            break;
        case KEY_LEFT:
            marek->setNextMove(LEFT);
            break;
        case KEY_RIGHT:
            marek->setNextMove(RIGHT);
            break;
        default:
            
            break;
        }
        mars.playRound();
        mars.drawWorld();
        
    }

    /*for (int i = 0; i < 20; i++) {
        mars.playRound();
        mars.drawWorld();
    }*/
    
}

