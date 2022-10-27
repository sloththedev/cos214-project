#include "Branch.h"

Branch::Branch(Unit* unit):Unit() {
	this->unit = unit;
}

void Branch::attack(Unit* pl){
	this->unit->attack(pl);
}

void Branch::requestState(){
	this->unit->requestState();
}

void Branch::setUnitState(UnitsState* unitS){
	this->unit->setUnitState(unitS);
}

bool Branch::takeDamage(int damage){
	return this->unit->takeDamage(damage);
}

string Branch::getBranch(){
	return "BRANCH";
}

string Branch::toString(int lineLen){
	return this->unit->toString(lineLen);
}

int * Branch::getAmmo(){
	return this->unit->getAmmo();
}

Branch::~Branch(){
	delete this->unit;
}
