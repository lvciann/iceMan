#include "StudentWorld.h"
#include <string>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir),
iceman(nullptr) {
    for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
        for (int j = 0; j < ICE_WIDTH; ++j) { //for columns
            ice[i][j] = nullptr;
        }
    }

}

StudentWorld::~StudentWorld() {
    //if iceman doesn't find ice, delete ice
    if (iceman != nullptr) {
        delete iceman;
    }
    for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
        for (int j = 0; j < ICE_WIDTH; ++j) { //for columns
            if (ice[i][j] != nullptr) {
                delete ice[i][j];
            }
        }
    }
}

//initialize the data structures used to keep track of game's virtual world
//construct new oil field
//allocate and insert a valid Iceman object at the proper location
int StudentWorld::init()
{
    this->iceman = new Iceman(this, 30, 60);

    for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
        for (int j = 0; j < ICE_WIDTH; ++j) { //for columns
            if (j < 30 || j > 34 || (j >= 30 && j <= 34 && i < 4)) {
                ice[i][j] = new Ice(this, i, j);
            }
        }
    }

    return GWSTATUS_CONTINUE_GAME;
}

//
int StudentWorld::move()
{
    //part 1: JUST THE ICEMAN--during each tick, must ask Iceman object to do something;
    if (iceman != nullptr) {   //if iceman is alive
        //ask iceman to do something
        iceman->doSomething();
        return GWSTATUS_CONTINUE_GAME;      // so that the game can continue
    }

    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

    decLives();
    return GWSTATUS_PLAYER_DIED;
}

//page 10
void StudentWorld::cleanUp()
{
    if (iceman != nullptr) {
        delete iceman;
    }

    for (int i = 0; i < ICE_HEIGHT; ++i) { //for rows
        for (int j = 0; j < ICE_WIDTH; ++j) { //for columns
            if (ice[i][j] != nullptr) {
                delete ice[i][j];
            }
        }
    }
}

