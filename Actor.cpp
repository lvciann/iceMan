#include "Actor.h"
#include <algorithm>

///////////////////////////////////// Constants ////////////////////////////////////////////

int ACTOR_HEIGHT = 4;

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

void People::setDead() {}

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
	sq = nullptr;
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

Squirt* Iceman::getSquirt() {

	return sq;
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

		int x = getX();
		int y = getY();

		switch (ch)
		{
		case KEY_PRESS_LEFT:



			if (getDirection() == left && x > 0) {

				for (int i = 0; i < ACTOR_HEIGHT; i++) {

					if (getWorld()->isIce(x - 1, y + i)) {
						getWorld()->clearIce(x - 1, y + i);
						getWorld()->playSound(SOUND_DIG);
					}
				}

				moveTo(x - 1, y);
			}

			else {
				moveTo(x, y);
			}

			setDirection(left);

			break;
		case KEY_PRESS_RIGHT:

			if (getDirection() == right && x < 56) {

				for (int i = 0; i < ACTOR_HEIGHT; i++) {

					for (int j = 0; j < ACTOR_HEIGHT + 1; j++) {

						if (getWorld()->isIce(x + j, y + i)) {
							getWorld()->clearIce(x + j, y + i);
							getWorld()->playSound(SOUND_DIG);
						}
					}
				}

				moveTo(x + 1, y);
			}

			else {
				moveTo(x, y);
			}

			setDirection(right);

			break;
		case KEY_PRESS_UP:

			if (getDirection() == up && y < 56) {

				for (int i = 0; i < ACTOR_HEIGHT; i++) {

					for (int j = 0; j < ACTOR_HEIGHT + 1; j++) {

						if (getWorld()->isIce(x + i, y + j)) {
							getWorld()->clearIce(x + i, y + j);
							getWorld()->playSound(SOUND_DIG);
						}
					}
				}

				moveTo(x, y + 1);
			}

			else {
				moveTo(x, y);
			}

			setDirection(up);

			break;
		case KEY_PRESS_DOWN:

			if (getDirection() == down && y > 0) {

				for (int i = 0; i < ACTOR_HEIGHT; i++) {

					if (getWorld()->isIce(x + i, y - 1)) {
						getWorld()->clearIce(x + i, y - 1);
						getWorld()->playSound(SOUND_DIG);
					}
				}

				moveTo(x, y - 1);
			}

			else {
				moveTo(x, y);
			}

			setDirection(down);


			break;

		case KEY_PRESS_SPACE:

			if (getDirection() == left) {

				sq = new Squirt(getWorld(), x - 1, y, left);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				sq->doSomething();

			}

			else if (getDirection() == right) {

				sq = new Squirt(getWorld(), x + 1, y, right);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				sq->doSomething();
			}

			else if (getDirection() == up) {

				sq = new Squirt(getWorld(), x, y + 1, up);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				sq->doSomething();

			}

			else if (getDirection() == down) {

				sq = new Squirt(getWorld(), x, y - 1, down);
				getWorld()->playSound(SOUND_PLAYER_SQUIRT);
				sq->doSomething();


			}

			break;

		case KEY_PRESS_TAB:

			if (gold > 0) {
				gold--;

				GoldNugget* nug = new GoldNugget(getWorld(), getX(), getY());

			}

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

	int t = 3 - getWorld()->getLevel() / 4;
	ticksToWaitBetweenMoves = std::max(0, t);

}

bool Protestor::isActive() {

	if (health > 0) {
		return true;
	}

	return false;

}

void Protestor::doSomething() {

	if (ticksToWaitBetweenMoves != 0) {

		ticksToWaitBetweenMoves--;
	}

	else {

		if (isActive()) {



		}

		int t = 3 - getWorld()->getLevel() / 4;
		ticksToWaitBetweenMoves = std::max(0, t);
	}



}

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

	if (getWorld()->isIce(getX(), getY())) {
		return true;
	}

	return false;
}

void Ice::doSomething() {}

///////////////////////////////////// Boulder Class /////////////////////////////////////

Boulder::Boulder(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_BOULDER, startX, startY, down, 1.0, 1) {

	lifespan = 10;

	if (getWorld()->isIce(startX, startY)) {

		for (int i = 0; i < ACTOR_HEIGHT; i++) {

			for (int j = 0; j < ACTOR_HEIGHT; j++) {

				getWorld()->clearIce(startX + i, startY + j);
			}
		}
	}

}

void Boulder::doSomething() {

	int x = getX();
	int y = getY();

	if (!(getWorld()->isIce(x, y - 1))) {
		if (!(getWorld()->isIce(x + 1, y - 1))) {
			if (!(getWorld()->isIce(x + 2, y - 1))) {
				if (!(getWorld()->isIce(x + 3, y - 1))) {

					if (lifespan > 0) {
						lifespan--;
					}

					else {

						//while (!(getWorld()->isIce(getX(), getY() - 1))) {

						getWorld()->playSound(SOUND_FALLING_ROCK);
						moveTo(x, y - 8);
						//}

					}
				}
			}
		}
	}

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

	state = true;
}

void Squirt::doSomething() {

	int x = getX();
	int y = getY();

	if (getDirection() == left && !(getWorld()->isIce(x - 12, y))) {
		moveTo(x - 12, y);
	}

	if (getDirection() == right && !(getWorld()->isIce(x + 12, y))) {
		moveTo(x + 12, y);
	}

	if (getDirection() == up && !(getWorld()->isIce(x, y + 12))) {
		moveTo(x, y + 12);
	}

	if (getDirection() == down && !(getWorld()->isIce(x, y - 12))) {
		moveTo(x, y - 12);
	}

	state = false;
}

bool Squirt::isActive() {

	if (state) {

		return true;
	}

	return false;

}

///////////////////////////////////// Oil Barrel Class /////////////////////////////////////

OilBarrel::OilBarrel(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_BARREL, startX, startY, right, 1.0, 2) {

	//setVisible(false);
}

bool OilBarrel::isActive() {

	if (state) {

		return true;
	}

	return false;
}

void OilBarrel::doSomething() {}

///////////////////////////////////// Gold Nugget Class /////////////////////////////////////

GoldNugget::GoldNugget(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_GOLD, startX, startY, right, 1.0, 2) {

	//setVisible(false);
}

bool GoldNugget::isActive() {

	if (state) {

		return true;
	}

	return false;
}

void GoldNugget::doSomething() {}

///////////////////////////////////// Sonar Class /////////////////////////////////////

Sonar::Sonar(StudentWorld* world) :
	Actor(world, IID_SONAR, 0, 60, right, 1.0, 2) {

	//setVisible(false);
}

bool Sonar::isActive() {

	if (state) {

		return true;
	}

	return false;

}

void Sonar::doSomething() {}

///////////////////////////////////// Water Pool Class /////////////////////////////////////

WaterPool::WaterPool(StudentWorld* world, int startX, int startY) :
	Actor(world, IID_WATER_POOL, startX, startY, right, 1.0, 2) {

	//setVisible(false);
}

bool WaterPool::isActive() {

	if (state) {

		return true;
	}

	return false;

}

void WaterPool::doSomething() {}


///////////////////////////////////// Other Functions /////////////////////////////////////

