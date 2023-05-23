//
// Created by Luciann Valencia on 5/15/23.
//

#ifndef ICEMAN_STUDENTWORLD_H
#define ICEMAN_STUDENTWORLD_H
#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"

//we want create a constant to be able to use 60 and 64 continuously
const int ICE_WIDTH = 64;
const int ICE_HEIGHT = 60;

class StudentWorld : public GameWorld { //since it's keeping track of
private:
    //private data member variables required to keep track of all Ice + Iceman objecy
    Ice* ice[ICE_HEIGHT][ICE_WIDTH]; // 2d-array of Ice pointers
    Iceman* iceman;
public:
    StudentWorld(std::string assetDir) : GameWorld(assetDir),
    iceman(nullptr){
        for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
            for (int j = 0; j < ICE_WIDTH; ++j){ //for columns
                ice[i][j] = nullptr;
            }
        }

    }

    virtual ~StudentWorld(){
        //if iceman doesn't find ice, delete ice
        if(iceman != nullptr){
            delete iceman;
        }
        for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
            for (int j = 0; j < ICE_WIDTH; ++j){ //for columns
                if(ice[i][j] != nullptr) {
                    delete ice[i][j];
                }
            }
        }
    }

    //initialize the data structures used to keep track of game's virtual world
    //construct new oil field
    //allocate and insert a valid Iceman object at the proper location
    virtual int init()
    {
        this->iceman = new Iceman(IID_PLAYER, 30, 60, GraphObject::right, 1.0, 0);

        for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
            for (int j = 0; j < ICE_WIDTH; ++j){ //for columns
                if (j < 30 || j > 34 || (j >= 30 && j <= 34 && i < 4)){
                        ice[i][j] = new Ice(IID_ICE, i, j, GraphObject::right, 0.25, 3);
                }
            }
        }

        return GWSTATUS_CONTINUE_GAME;
    }

    //
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
