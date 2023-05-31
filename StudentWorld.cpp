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
    //update game status line:
    stats();
    
    //give each actor a chance to do something
    if(iceman->isActive() == true){ //if iceman is alive
        //ask iceman to do something
        iceman->doSomething();
        return GWSTATUS_CONTINUE_GAME;      // so that the game can continue
    }
//    for(){
//
//        return GWSTATUS_CONTINUE_GAME;
//    }
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.

    decLives();
    return GWSTATUS_PLAYER_DIED;
    
    //todo:
    //if iceman has collected all of the barrels, continue game
    
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

void StudentWorld::stats(){
    //must update the status text on top of the screen
    string iceMan_stats = "LEVEL: " + to_string(getLevel()) + "  " +
                          "LIVES: " + to_string(getLives()) + "  " +
                          "HEALTH: " + to_string(iceman->getHealth()) + "  "
//                          + "WATER: " + to_string() + "  "
                          + "GOLD: " + to_string(iceman->getGold()) + "  "
//                        + "OIL LEFT: " + to_string() + "  " + //barrel dist - amount collected
//                          "SONAR: " + to_string() + "  "
                          + "SCORE: " + to_string(getScore()) + "  ";
    
    setGameStatText(iceMan_stats);
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

void StudentWorld::clearIce(int x, int y){
    //if iceman's location == the location of ice, delete ice
        delete ice[x][y];
    
}
