//
// Created by Luciann Valencia on 5/15/23.
//

#ifndef ICEMAN_STUDENTWORLD_H
#define ICEMAN_STUDENTWORLD_H
#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"

class StudentWorld : public GameWorld { //since it's keeping track of
private:
    //private data member variables required to keep track of all Ice + Iceman objecy
    Ice ice;
    Iceman iceman;
public:
    StudentWorld(std::string assetDir) : GameWorld(assetDir),
    iceman(IID_PLAYER, 30, 60, GraphObject::right, 1.0, 0),
    ice(IID_ICE, 0, 0, GraphObject::right, 0.25, 3){
    }

    virtual ~StudentWorld(){

    }

    virtual int init()
    {
        return GWSTATUS_CONTINUE_GAME;
    }

    virtual int move()
    {
        // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
        // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }

    virtual void cleanUp()
    {
    }
};



#endif //ICEMAN_STUDENTWORLD_H
