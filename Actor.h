#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class Actor : public GraphObject {
public:
	Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
		GraphObject(imageID, startX, startY, right, 1.0, 0){
	
		setVisible(true);
	}

	virtual ~Actor(){
		
	}

	virtual void doSomething() = 0;


};

class People : public Actor {


};


class Iceman : public Actor {
public:

	Iceman(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :
		Actor(IID_PLAYER, 30, 60, right, 1.0, 0) {

		health = 10;

	}

private:

	int health;

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


};

class HardcoreProtestor : public Protestor {


};


#endif // ACTOR_H_
