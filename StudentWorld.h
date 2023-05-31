//
// Created by Luciann Valencia on 5/15/23.
//

#ifndef ICEMAN_STUDENTWORLD_H
#define ICEMAN_STUDENTWORLD_H
#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <vector>

//we want create a constant to be able to use 60 and 64 continuously
//we want to create a constant to be able to use 60 and 64 continuously
const int ICE_HEIGHT= 64;
const int ICE_WIDTH = 60;

class Actor;
class Iceman;
class Ice;

class StudentWorld : public GameWorld { //since it's keeping track of
private:
    Ice* ice[ICE_HEIGHT][ICE_WIDTH]; // 2d-array of Ice pointers
    Iceman* iceman;
    std::vector<Actor *> objects; //vector of pointers to objects (reg  protestors, gold, barrels, sonar)
public:
    StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    //initialize the data structures used to keep track of game's virtual world
    //construct new oil field
    //allocate and insert a valid Iceman object at the proper location
    virtual int init();
    //
    virtual int move();
    //page 10
    virtual void cleanUp();
    //compares 2 parameters and returns smaller number
    int minCalc(int a, int b);
    //compares 2 parameters and returns lerger number
    int maxCalc(int a, int b);
    //boulder distribution
    int boulderDist();
    //gold nugget distribution
    int goldNuggetDist();
    //barrel distribution
    int barrelDist();
};


#endif //ICEMAN_STUDENTWORLD_H
