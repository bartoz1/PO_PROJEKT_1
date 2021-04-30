#include <iostream>
#include "World.h"
#include "Common.h"
#include "Organisms/Organism.h"

using namespace std;

int main() {
    std::string wejscie;
    World mars(10, 10);
    mars.drawWorld();
    
    while (wejscie != "x") {
        mars.playRound();
        mars.drawWorld();
        cin >> wejscie;
    }

    /*for (int i = 0; i < 20; i++) {
        mars.playRound();
        mars.drawWorld();
    }*/
    
}

