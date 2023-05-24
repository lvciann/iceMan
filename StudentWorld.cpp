//
// Created by Luciann Valencia on 5/15/23.
//

#include "StudentWorld.h"
#include <string>
using namespace std;

StudentWorld* theWorld = nullptr;

GameWorld* createStudentWorld(string assetDir)
{
    theWorld = new StudentWorld(assetDir);
    return theWorld;
}

StudentWorld* getWorld() {
    return theWorld;
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
