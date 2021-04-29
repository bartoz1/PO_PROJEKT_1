#include <iostream>
#include "World.h"
#include "Common.h"
#include "Organisms/Organism.h"

using namespace std;

int main() {
    std::string wejscie;
    World mars(5, 3);
    mars.drawWorld();
    
    while (true) {
        mars.playRound();
        mars.drawWorld();
        cin >> wejscie;
    }
    
}

