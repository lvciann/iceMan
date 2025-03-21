#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

//forward declare StudentWorld class
class StudentWorld;

//Actor class
class Actor : public GraphObject {
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);

	virtual ~Actor();

	virtual void doSomething();

	virtual bool isActive();

	virtual void setDead();

	virtual bool canActorsPassThroughMe() const;

	StudentWorld* getWorld();

	int health;

	bool state;

	StudentWorld* theWorld;
};

class People : public Actor {
public:
	People(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);

	virtual ~People();

	virtual void setGold(int i);

	virtual void setDead();

	virtual bool isActive();

	//virtual void isAnnoyed(){}		//all people can be annoyed: Iceman, Protestors

	int gold;

};

class Squirt;

class Iceman : public People {
public:

	Iceman(StudentWorld* world, int startX, int startY);

	virtual bool isActive();

	int getHealth();

	int getAmmo();

	int getCharge();

	int getGold();

	int getBarrel();

	Squirt* getSquirt();

	virtual void setDead();

	void setAmmo();

	void setGold();

	void setBarrel();

	void doSomething();

	bool hasCompletedLevel(int i);

private:

	int barrels;
	int ammo;
	int charge;
	Squirt* sq;

};

class Ice : public Actor {
public:

	Ice(StudentWorld* world, int startX, int startY);

	virtual void doSomething();

	virtual bool isActive();

};

class Boulder : public Actor {
public:

	Boulder(StudentWorld* world, int startX, int startY);

	virtual void doSomething();

	virtual bool canActorsPassThroughMe() const;

	virtual bool isActive();

	virtual void setDead();

private:

	int lifespan;
	bool waiting;
	bool state;
};

class Squirt : public Actor {
public:

	Squirt(StudentWorld* world, int startX, int startY, Direction dir);

	virtual void doSomething();

	virtual bool isActive();

};

class OilBarrel : public Actor {
public:

	OilBarrel(StudentWorld* world, int startX, int startY);

	virtual void doSomething();

	virtual bool isActive();

};

class GoldNugget : public Actor {
public:

	GoldNugget(StudentWorld* world, int startX, int startY);

	virtual void doSomething();

	virtual bool isActive();

};

class Sonar : public Actor {
public:

	Sonar(StudentWorld* world);

	virtual void doSomething();

	virtual bool isActive();

};

class WaterPool : public Actor {
public:

	WaterPool(StudentWorld* world, int startX, int startY);

	virtual void doSomething();

	virtual bool isActive();

};

class Protestor : public People {
public:

	Protestor(StudentWorld* world, int startX, int startY, int imageID);

	virtual void doSomething();


	//both protestors can pick up gold nuggets

	virtual bool isActive();

	int numSquaresToMoveInCurrentDirection;
	int ticksToWaitBetweenMoves;
};

class HardcoreProtestor : public Protestor {
public:

	HardcoreProtestor(StudentWorld* world, int startX, int startY);

	virtual void doSomething();

	virtual bool isActive();

};


bool basicPath(StudentWorld* world, Protestor* pro, int nRows, int nCols, int sr, int sc, int er, int ec);

#endif //ACTOR_H_


