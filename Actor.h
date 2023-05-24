#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);

	~Actor();
	virtual void doSomething();
	//virtual bool isActive() = 0;

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

class Boulders : public Actor {

};

class Squirt : public Actor {

};

class OilBarrel : public Actor {

};

class GoldNugget : public Actor {

};

class Sonar : public Actor {


};

class WaterPool : public Actor {


};

class Protestor : public People {

	//both protestors can pick up gold nuggets
};

class HardcoreProtestor : public Protestor {


};


#endif //ACTOR_H_

