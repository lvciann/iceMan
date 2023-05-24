#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class StudentWorld;

class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
		GraphObject(imageID, startX, startY, dir, size, depth) {

		setVisible(true);
	}

	~Actor() {}
	virtual void doSomething() {}
	//virtual bool isActive();



};

class People : public Actor {
public:
	People(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
		Actor(imageID, startX, startY, dir, size, depth) {


	}
	virtual ~People() {}

	//virtual void isAnnoyed(){}		//all people can be annoyed: Iceman, Protestors
protected:

	int health;

};


class Iceman : public People {
public:

	Iceman() :
		People(IID_PLAYER, 30, 60, right, 1.0, 0) {

		health = 10;

	}

	void doSomething() {

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
		//...
	}


};

class Ice : public Actor {


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


#endif // ACTOR_H_

