#include "Organism.h"
//Organism::Organism(World& world) {
//	initiative = 0;
//	strenght = 0;
//	age = 0;
//	world = nullptr;
//}
Organism::Organism(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name)
	: world(world), initiative(initiative), strenght(strenght), name(name) {
	this->age = 0;
	this->position.x = pos_x;
	this->position.y = pos_y;
}

bool Organism::willSurviveAttack(Organism& enemy) {
	if (enemy.getStrenght() >= this->getStrenght())
		return false;
	return true;
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
std::string Organism::getName() const {
	return this->name;
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

void Organism::setName(std::string name) {
	this->name = name;
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
