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

class Iceman : public People {
public:

	Iceman(StudentWorld* world, int startX, int startY);

	virtual bool isActive();

	int getHealth();

	int getAmmo();

	int getGold();

	int getBarrel();

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

};

class Ice : public Actor {
public:

	Ice(StudentWorld* world, int startX, int startY);

	void doSomething();

	virtual bool isActive();

};

class Boulder : public Actor {
public:

	Boulder(StudentWorld* world, int startX, int startY);

	void doSomething();

	void isWaiting(bool amIWaiting);

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

	void doSomething();

	virtual bool isActive();

};

class OilBarrel : public Actor {
public:

	OilBarrel(StudentWorld* world, int startX, int startY);

	void doSomething();

	virtual bool isActive();

};

class GoldNugget : public Actor {
public:

	GoldNugget(StudentWorld* world, int startX, int startY);

	void doSomething();

	virtual bool isActive();

};

class Sonar : public Actor {
public:

	Sonar(StudentWorld* world, int startX, int startY);

	void doSomething();

	virtual bool isActive();

};

class WaterPool : public Actor {
public:

	WaterPool(StudentWorld* world, int startX, int startY);

	void doSomething();

	virtual bool isActive();

};

class Protestor : public People {
public:

	Protestor(StudentWorld* world, int startX, int startY, int imageID);

	void doSomething();

	
	//both protestors can pick up gold nuggets

	virtual bool isActive();
};

class HardcoreProtestor : public Protestor {
public:

	HardcoreProtestor(StudentWorld* world, int startX, int startY);

	void doSomething();

	virtual bool isActive();

};


#endif //ACTOR_H_

