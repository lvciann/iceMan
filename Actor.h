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

	~Actor();

	virtual void doSomething();

	virtual bool isActive();

	virtual bool canActorsPassThroughMe() const;

	StudentWorld* getWorld();

	StudentWorld* theWorld;
};

class People : public Actor {
public:
	People(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
	virtual ~People();

	//virtual void isAnnoyed(){}		//all people can be annoyed: Iceman, Protestors

	int health;

};

class Iceman : public People {
public:

	Iceman(StudentWorld* world, int startX, int startY);

	int getHealth();

	void doSomething();

};

class Ice : public Actor {
public:

	Ice(StudentWorld* world, int startX, int startY);

};

class Boulder : public Actor {
public:

	Boulder(StudentWorld* world, int startX, int startY);

	virtual bool canActorsPassThroughMe() const;
};

class Squirt : public Actor {
public:

	Squirt(StudentWorld* world, int startX, int startY, Direction dir);

};

class OilBarrel : public Actor {
public:

	OilBarrel(StudentWorld* world, int startX, int startY);

};

class GoldNugget : public Actor {
public:

	GoldNugget(StudentWorld* world, int startX, int startY);

};

class Sonar : public Actor {
public:

	Sonar(StudentWorld* world, int startX, int startY);

};

class WaterPool : public Actor {
public:

	WaterPool(StudentWorld* world, int startX, int startY);

};

class Protestor : public People {
public:

	Protestor(StudentWorld* world, int startX, int startY, int imageID);
	//both protestors can pick up gold nuggets
};

class HardcoreProtestor : public Protestor {
public:

	HardcoreProtestor(StudentWorld* world, int startX, int startY);

};


#endif //ACTOR_H_
