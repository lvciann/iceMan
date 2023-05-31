//
// Created by Luciann Valencia on 5/15/23.
//

#include "StudentWorld.h"
#include <string>
#include <algorithm>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

StudentWorld::StudentWorld(std::string assetDir) : GameWorld(assetDir),
iceman(nullptr) {
    for (int i = 0; i < ICE_WIDTH; ++i) { //for rows
        for (int j = 0; j < ICE_HEIGHT; ++j) { //for columns
            ice[i][j] = nullptr;
        }
    }
}

StudentWorld::~StudentWorld() {
    //if iceman doesn't find ice, delete ice
    if (iceman != nullptr) {
        delete iceman;
    }
    for (int i = 0; i < ICE_WIDTH; ++i) { //for rows
        for (int j = 0; j < ICE_HEIGHT; ++j) { //for columns
            if (ice[i][j] != nullptr) {
                delete ice[i][j]; //shows an error
            }
        }
    }
}

//initialize the data structures used to keep track of game's virtual world
//construct new oil field
//allocate and insert a valid Iceman object at the proper location
int StudentWorld::init()
{
    this->iceman = new Iceman(this, 30, 60); //position of iceman

    for (int i = 0; i < ICE_WIDTH; ++i) { //for columns
        for (int j = 0; j < ICE_HEIGHT; ++j) { //for rows
            if (i < 30 || i > 33 || (i >= 30 && i <= 34 && j < 4)) {
                ice[i][j] = new Ice(this, i, j);
            }
            //testing for orientation--delete asap
            if(i == 0 && j == 0){
                delete ice[0][0];
            }
            if(i == 30 && j == 0){
                delete ice[30][0];
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

int StudentWorld::minCalc(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

int StudentWorld::maxCalc(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

//------------------------------------area for object distribution in oil field---------
int StudentWorld::boulderDist(){
    int B = minCalc((GameWorld::getLevel()/2) + 2, 9);
    return B;
}

int StudentWorld::goldNuggetDist(){
    int G = maxCalc((5 - GameWorld::getLevel()), 21);
    return G;
}

int StudentWorld::barrelDist(){
    int L = minCalc((2 + getLevel()), 21);
    return L;
}
//------------------------------------area for object distribution in oil field---------


