#include <iostream>
#include "World.h"
#include "Common.h"
#include "Organisms/Organism.h"

using namespace std;

int main() {
    std::string wejscie;
    World mars(10, 5);
    mars.drawWorld();
    
    while (true) {
        mars.playRound();
        mars.drawWorld();
        cin >> wejscie;
    }
    
}

