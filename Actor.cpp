#include "Actor.h"
#include "StudentWorld.h"

Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	GraphObject(imageID, startX, startY, dir, size, depth) {

	theWorld = world;
	setVisible(true);
}

Actor::~Actor() {};
void Actor::doSomething() {};
//virtual bool isActive() = 0;

StudentWorld* Actor::getWorld() {
	return theWorld;
}

People::People(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
	Actor(world, imageID, startX, startY, dir, size, depth) {

	health = 0;
}

People::~People() {}


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
			// etcÖ
		}
	}

}

Ice::Ice(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_ICE, startX, startY, right, 0.25, 3) {

}

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

