#include "Organism.h"
//Organism::Organism(World& world) {
//	initiative = 0;
//	strenght = 0;
//	age = 0;
//	world = nullptr;
//}
Organism::Organism(World& world, int pos_x, int pos_y, int initiative, int strenght, std::string name, ORGANISMS type)
	: world(world), initiative(initiative), strenght(strenght), name(name), type(type) {
	this->age = 0;
	this->position.x = pos_x;
	this->position.y = pos_y;
	this->alive = true;
}

bool Organism::willSurviveAttack(Organism& enemy) {
	if (enemy.getStrenght() >= this->getStrenght())
		return false;
	return true;
}

Position Organism::getNextAvailablePosition(Position current, DIRECTION desired_dir) {
	Position tmp;
	for (int i = 0; i < 4; i++) {		// petla przechodz¹ca po wszystkich 
		tmp = current;
		desired_dir = (DIRECTION)((desired_dir + 1) % 4);
		switch (desired_dir)
		{
		case LEFT:
			tmp.x--;
			break;
		case RIGHT:
			tmp.x++;
			break;
		case TOP:
			tmp.y--;
			break;
		case BOTTOM:
			tmp.y++;
			break;
		}
		if (world.getFieldState(&tmp) == AVAILABLE)
			return tmp;
	}
	return current;
}

bool Organism::isAlive() const
{
	return this->alive;
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
ORGANISMS Organism::getOrganismType() const {
	return this->type;
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
	this->position.x = position.x;
	this->position.y = position.y;
}

void Organism::setDeath() {
	this->alive = false;
}

void Organism::incrementAge() {
	this->age++;
}

void Organism::move(int dx, int dy) {
	this->position.x += dx;
	this->position.y += dy;
}

std::string Organism::toString() {
	std::string	text = "";
	text += std::to_string((int)(this->getOrganismType()));
	text += " ";
	text += std::to_string(this->getAge());
	text += " ";
	text += std::to_string(this->getInitiative());
	text += " ";
	text += std::to_string(this->getStrenght());
	text += " ";
	text += std::to_string(this->getPosition().x);
	text += " ";
	text += std::to_string(this->getPosition().y);
	

	return text;
}
