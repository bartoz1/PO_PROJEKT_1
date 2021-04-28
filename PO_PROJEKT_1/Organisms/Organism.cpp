#include "Organism.h"
//Organism::Organism(World& world) {
//	initiative = 0;
//	strenght = 0;
//	age = 0;
//	world = nullptr;
//}
Organism::Organism(World& world, Position &position, int initiative, int strenght)
	: world(world), position(position), initiative(initiative), strenght(strenght) {
	this->age = 0;
}

int Organism::getStrenght() const{
	return this->strenght;
}
int Organism::getInitiative() const{
	return this->initiative;
}
int Organism::getAge() const{
	return this->age;
}
Position Organism::getPosition() const{
	return this->position;
}
/*
World& Organism::getWorld() const{
	return this->world;
}*/

void Organism::setStrenght(int strenght){
	this->strenght = strenght;
}

void Organism::setInitiative(int initiative){
	this->initiative = initiative;
}

void Organism::setAge(int age){
	this->age = age;
}

void Organism::setPosition(Position position){
	this->position = position;
}

void Organism::incrementAge() {
	this->age++;
}

void Organism::move(int dx, int dy) {
	this->position.x += dx;
	this->position.y += dy;
}
