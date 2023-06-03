#include "Actor.h"
#include <algorithm>

///////////////////////////////////// Actor Base Class /////////////////////////////////////

Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	GraphObject(imageID, startX, startY, dir, size, depth) {
	
	health = 0;
	theWorld = world;
	setVisible(true);	//// change this for objects who start out invisible
}

Actor::~Actor() {}

void Actor::doSomething() {}

bool Actor::isActive() { return false; }

void Actor::setDead() {}

bool Actor::canActorsPassThroughMe() const { return false; }


StudentWorld* Actor::getWorld() {
	return theWorld;
}

///////////////////////////////////// People Class /////////////////////////////////////

People::People(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(world, imageID, startX, startY, dir, size, depth) {

	health = 0;
}

People::~People() {}

void People::setGold(int i) {

	gold = i;
}

void People::setDead(){}

bool People::isActive() {
	
	if (health > 0) {
		return true;
	}

	return false;
}


///////////////////////////////////// Iceman Class /////////////////////////////////////

Iceman::Iceman(StudentWorld* world, int startX, int startY) :
	People(world, IID_PLAYER, 30, 60, right, 1.0, 0) {

	health = 10;
	ammo = 5;
	gold = 0;
	charge = 1;
}

bool Iceman::isActive() {

	if (getHealth() > 0) {
		return true;
	}

	return false;
}

int Iceman::getHealth() {

	return health;
}

int Iceman::getAmmo() {

	return ammo;
}

int Iceman::getGold() {

	return gold;
}

int Iceman::getBarrel() {

	return barrels;
}

void Iceman::setDead() {

	health = 0;
}

void Iceman::setAmmo() {
	ammo++;
}

void Iceman::setGold() {
	gold++;
}

void Iceman::setBarrel() {
	barrels++;
}

void Iceman::doSomething() {

	if (!isActive()) {
		return;
	}

	int ch;
	if (getWorld()->getKey(ch) == true)
	{
		// user hit a key this tick! 
		switch (ch)
		{
		case KEY_PRESS_LEFT:

			if (getDirection() == left && getX() > 0) {
				moveTo(getX() - 1, getY());
			}

			setDirection(left);

			break;
		case KEY_PRESS_RIGHT:

			if (getDirection() == right && getX() < 56) {		//why 56?
				moveTo(getX() + 1, getY());
			}

			setDirection(right);

			break;
		case KEY_PRESS_UP:

			if (getDirection() == up && getY() < 60) {
				moveTo(getX(), getY() + 1);
			}

			setDirection(up);

			break;
		case KEY_PRESS_DOWN:

			if (getDirection() == down && getY() > 0) {
				moveTo(getX(), getY() - 1);
			}

			setDirection(down);

			break;

		case KEY_PRESS_SPACE:
			
			if (getDirection() == left) {

				Squirt* sq = new Squirt(getWorld(), getX() - 1, getY(), left);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				delete sq;

			}

			else if (getDirection() == right) {

				Squirt* sq = new Squirt(getWorld(), getX() + 1, getY(), right);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				delete sq;
			}

			else if (getDirection() == up) {

				Squirt* sq = new Squirt(getWorld(), getX(), getY() + 1, up);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				delete sq;
			}

			else if (getDirection() == down) {

				Squirt* sq = new Squirt(getWorld(), getX(), getY() - 1, down);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				delete sq;
			}
			break;

		case KEY_PRESS_TAB:

			gold--;
			GoldNugget* nug = new GoldNugget(getWorld(), getX(), getY());

			break;

		case KEY_PRESS_ESCAPE:

			setDead();

			break;

		case 'z':

			charge--; //have to somehow make visible using setVisible., what if create new objects w depth 0?

			break;

		case 'Z':

			charge--;

			break;

		}
	}

}

bool Iceman::hasCompletedLevel(int i) {

	if (barrels == i) {
		return true;
	}

	return false;
}

///////////////////////////////////// Protestor Class /////////////////////////////////////

Protestor::Protestor(StudentWorld* world, int startX, int startY, int imageID) :
	People(world, imageID, startX, startY, left, 1.0, 0) {

	health = 5;
	numSquaresToMoveInCurrentDirection = (rand() % 56) + 4;

}

bool Protestor::isActive() {

	if (health > 0) {
		return true;
	}

	return false;

}

void Protestor::doSomething() {}

///////////////////////////////////// Hardcore Protestor Class /////////////////////////////////////

HardcoreProtestor::HardcoreProtestor(StudentWorld* world, int startX, int startY) :
	Protestor(world, startX, startY, IID_HARD_CORE_PROTESTER) {

	health = 20;
}

bool HardcoreProtestor::isActive() {

	if (health > 0) {
		return true;
	}

	return false;

}

void HardcoreProtestor::doSomething() {}

///////////////////////////////////// Ice Class /////////////////////////////////////

Ice::Ice(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_ICE, startX, startY, right, 0.25, 3) {

}

bool Ice::isActive() { 

	return true;
}

void Ice::doSomething(){}

///////////////////////////////////// Boulder Class /////////////////////////////////////

Boulder::Boulder(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_BOULDER, startX, startY, down, 1.0, 1) {

	lifespan = 30;
}

void Boulder::doSomething() {

	if (waiting) {

		if (lifespan > 0) {
			lifespan--;
		}

		else {
			getWorld()->playSound(SOUND_FALLING_ROCK);
			moveTo(getX(), getY() - 1);
		}
	}

}

void Boulder::isWaiting(bool amIWaiting) {

	waiting = amIWaiting;
}

bool Boulder::isActive() {

	if (state) {
		return true;
	}

	return false;
}

void Boulder::setDead() {

	state = false;
}
bool Boulder::canActorsPassThroughMe() const {
	return false;
}

///////////////////////////////////// Squirt Class /////////////////////////////////////

Squirt::Squirt(StudentWorld* world, int startX, int startY, Direction dir) :
	Actor(world, IID_WATER_SPURT, startX, startY, dir, 1.0, 1) {

}

void Squirt::doSomething() {}

bool Squirt::isActive() {

	return true;

}

///////////////////////////////////// Oil Barrel Class /////////////////////////////////////

OilBarrel::OilBarrel(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_BARREL, startX, startY, right, 1.0, 2) {

	//setVisible(false);
}

bool OilBarrel::isActive() {
	return true;
}

void OilBarrel::doSomething(){}

///////////////////////////////////// Gold Nugget Class /////////////////////////////////////

GoldNugget::GoldNugget(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_GOLD, startX, startY, right, 1.0, 2) {

}

bool GoldNugget::isActive() {

	return true;
}

void GoldNugget::doSomething() {}

///////////////////////////////////// Sonar Class /////////////////////////////////////

Sonar::Sonar(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_SONAR, startX, startY, right, 1.0, 2) {


}

bool Sonar::isActive(){
	return true;

}

void Sonar::doSomething() {}

///////////////////////////////////// Water Pool Class /////////////////////////////////////

WaterPool::WaterPool(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_WATER_POOL, startX, startY, right, 1.0, 2) {

}

bool WaterPool::isActive() {

	return true;

}

void WaterPool::doSomething() {}


///////////////////////////////////// Other Functions /////////////////////////////////////
