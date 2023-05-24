//
// Created by Luciann Valencia on 5/15/23.
//

#ifndef ICEMAN_STUDENTWORLD_H
#define ICEMAN_STUDENTWORLD_H
#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"

//we want create a constant to be able to use 60 and 64 continuously
//we want to create a constant to be able to use 60 and 64 continuously
const int ICE_WIDTH = 64;
const int ICE_HEIGHT = 60;

class Actor;
class Iceman;
class Ice;

class StudentWorld : public GameWorld { //since it's keeping track of
private:
    //private data member variables required to keep track of all Ice + Iceman objecy
    Ice* ice[ICE_HEIGHT][ICE_WIDTH]; // 2d-array of Ice pointers
    Iceman* iceman;
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
};


#endif //ICEMAN_STUDENTWORLD_H

