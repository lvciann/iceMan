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
    //for ice:
    for (int i = 0; i < ICE_WIDTH; ++i) { //for rows
        for (int j = 0; j < ICE_HEIGHT; ++j) { //for columns
            ice[i][j] = nullptr;
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
        
        //distributing game objects
        boulderDist();
        goldDist();
        
        
    }

    return GWSTATUS_CONTINUE_GAME;
}

//
int StudentWorld::move()
{
    //update game status line:
    stats();
    
    ///////////////////////////////////////////continue game////////////////////////////////////////////////////////
    //give each actor a chance to do something
    if(iceman->isActive() == true){ //if iceman is alive
        //ask iceman to do something
        iceman->doSomething();
        return GWSTATUS_CONTINUE_GAME;      // so that the game can continue
    }
    
    ///////////////////////////////////////////next level////////////////////////////////////////////////////////
    if(barrelAmnt() == 0){
        playSound(GWSTATUS_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    if(goldNuggetAmnt() == 0){
        
    }
    
    // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    ///////////////////////////////////////////player deaths////////////////////////////////////////////////////////
    if(iceman->getHealth() == 0){
        playSound(SOUND_PLAYER_GIVE_UP); //dont forget to play sound is void; this is int!!
        return GWSTATUS_PLAYER_DIED;
    }
    decLives();
    return GWSTATUS_PLAYER_DIED;
    
    //todo:
    //if iceman has collected all of the barrels, next level
    
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


//------------------------------------area for actors in oil field------------------------------------
int StudentWorld::boulderRandomX(){
        int rX;
        rX = (rand() % 56) + 4;
        return rX;
}
int StudentWorld::boulderRandomY(){
    int rY;
    rY = rand() % 60;
    return rY;
}
int StudentWorld::goldRandomX(){
    int rX;
    rX = (rand() % 56) + 4;
    return rX;
}
int StudentWorld::goldRandomY(){
    int rY;
    rY = rand() % 60;
    return rY;
}
int StudentWorld::barrelRandomX(){
    int rX;
    rX = (rand() % 56) + 4;
    return rX;
}
int StudentWorld::barrelRandomY(){
    int rY;
    rY = rand() % 60;
    return rY;
}
int StudentWorld::boulderAmnt(){
    int A = min(int (getLevel()/2) + 2, 9);
    return A;
}
int StudentWorld::goldNuggetAmnt(){
//    int G = max(5-((int)getLevel()/2), 2);
    int G = 5;
    return G;
}
int StudentWorld::barrelAmnt(){
    int L = min(2 + (int) (getLevel()), 21);
    return L;
}
void StudentWorld::boulderDist(){
    for(int i = 0; i < boulderAmnt(); i++){
        actors.push_back(new Boulder(this, boulderRandomX(), boulderRandomY()));
    }
}
void StudentWorld::goldDist(){
    for(int i = 0; i < 1; i++){
        actors.push_back(new GoldNugget(this, goldRandomX(), goldRandomY()));
    }
}
//------------------------------------area for actors in oil field------------------------------------

void StudentWorld::clearIce(int x, int y){
    //if iceman's location == the location of ice, delete ice
    //took the x(+- 1) and y(+- 3) position of iceman then made a for loop from the current position to calculated position to delete\\
    
//    for(int i = x; i < (x + 1); i++){ //for row
//        for(int j = y; j < (y + 3); j++){ //for column
//            if(iceman = ice[x][y]){
//                delete ice[i][j];
//            }
//        }
//
//    }

        delete ice[x][y];
    
}
