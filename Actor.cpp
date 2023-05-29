#include "Actor.h"


///////////////////////////////////// Actor Base Class /////////////////////////////////////

Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	GraphObject(imageID, startX, startY, dir, size, depth) {

	theWorld = world;
	setVisible(true);
}

Actor::~Actor() {}

void Actor::doSomething() {}

bool Actor::isActive() { return false; }

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


///////////////////////////////////// Iceman Class /////////////////////////////////////

Iceman::Iceman(StudentWorld* world, int startX, int startY) :
	People(world, IID_PLAYER, 30, 60, right, 1.0, 0) {

	health = 10;

}

int Iceman::getHealth() {

	return health;
}

void Iceman::doSomething() {

	int ch;
	if (getWorld()->getKey(ch) == true)
	{
		// user hit a key this tick! 
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			moveTo(getX() - 1, getY());
			//... move player to the left ...;
			break;
		case KEY_PRESS_RIGHT:
			moveTo(getX() + 1, getY());
			//... move player to the right ...;
			break;
		case KEY_PRESS_UP:
			moveTo(getX(), getY() + 1);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() - 1);
			break;

		case KEY_PRESS_SPACE:
			//... add a Squirt in front of the player...;
			break;
			// etc…
		}
	}

}

///////////////////////////////////// Protestor Class /////////////////////////////////////

Protestor::Protestor(StudentWorld* world, int startX, int startY, int imageID) :
	People(world, imageID, startX, startY, left, 1.0, 0) {


}

///////////////////////////////////// Hardcore Protestor Class /////////////////////////////////////

HardcoreProtestor::HardcoreProtestor(StudentWorld* world, int startX, int startY) :
	Protestor(world, startX, startY, IID_HARD_CORE_PROTESTER) {

}

///////////////////////////////////// Ice Class /////////////////////////////////////

Ice::Ice(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_ICE, startX, startY, right, 0.25, 3) {

}

///////////////////////////////////// Boulder Class /////////////////////////////////////

Boulder::Boulder(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_BOULDER, startX, startY, down, 1.0, 1) {

}

bool Boulder::canActorsPassThroughMe() const {
	return false;
}


///////////////////////////////////// Squirt Class /////////////////////////////////////

Squirt::Squirt(StudentWorld* world, int startX, int startY, Direction dir) :
	Actor(world, IID_WATER_SPURT, startX, startY, dir, 1.0, 1) {

}

///////////////////////////////////// Oil Barrel Class /////////////////////////////////////

OilBarrel::OilBarrel(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_BARREL, startX, startY, right, 1.0, 2) {

	//setVisible(false);
}

///////////////////////////////////// Gold Nugget Class /////////////////////////////////////

GoldNugget::GoldNugget(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_GOLD, startX, startY, right, 1.0, 2) {

}

///////////////////////////////////// Sonar Class /////////////////////////////////////

Sonar::Sonar(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_SONAR, startX, startY, right, 1.0, 2) {


}

///////////////////////////////////// Water Pool Class /////////////////////////////////////

WaterPool::WaterPool(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_WATER_POOL, startX, startY, right, 1.0, 2) {

}
