//
// Created by Luciann Valencia on 5/15/23.
//

#ifndef ICEMAN_STUDENTWORLD_H
#define ICEMAN_STUDENTWORLD_H

#include "GameWorld.h"


//keeps track of the whole game world
class StudentWorld : public GameWorld{
private:
    //private data member variables required to keep track of all the ice in the
    //oil field as well as the Iceman object
public:
    //constructor that initializes all member variables required for gameplay
//    StudentWorld(){
//
//    }

    //destructor for Iceman and all remaining Ice
    ~StudentWorld() {}

    //must create Iceman object and insert it to oil field at right location,
    //must create all the oil field's Ice objects and inserts them into data structure that tracks active Ice
    virtual int init(){}

    //at each tick, must ask Iceman object to do something
    //will not need to check if Iceman died--assume it cannot die here
    //only deals with Iceman
    virtual int move(){}

    //frees any dynamically allocated data that was allocated during calls to init() or move()
    //likely does the same thing as dtor
    virtual void cleanup(){}

};

class Actor{};

StudentWorld* getWorld();


#endif //ICEMAN_STUDENTWORLD_H
