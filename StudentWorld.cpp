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
//    int xAxis = 0;
//    int yAxis = 0;
    this->iceman = new Iceman(this, 30, 60); //position of iceman
    std::vector<Actor *> actors; 

    for (int i = 0; i < ICE_WIDTH; ++i) { //for columns
        for (int j = 0; j < ICE_HEIGHT; ++j) { //for rows
            if (i < 30 || i > 33 || (i >= 30 && i <= 34 && j < 4)) {
                ice[i][j] = new Ice(this, i, j);
            }

        }
    }
    //distributing game objects randomly
    for(int i = 0; i < boulderAmnt(); i++){
        int x = boulderRandomX();
        int y = boulderRandomY();
        
        actors.push_back(new Boulder(this, x, y));
                   
    }

    for(int i = 0; i < goldNuggetAmnt(); i++){
        actors.push_back(new GoldNugget(this, goldRandomX(), goldRandomY()));
    
    }
    for(int i = 0; i < barrelAmnt(); i++){
        if(i < (ICE_WIDTH - 30 ) || i > (ICE_WIDTH - 27) || (i >= (ICE_WIDTH - 30) && i <= (ICE_WIDTH - 26) && (ICE_HEIGHT < 4))){
            actors.push_back(new OilBarrel(this, barrelRandomX(), barrelRandomY()));
        }
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
        if(iceman->hasCompletedLevel(min((2 + (int) getLevel()), 21))){
            playSound(GWSTATUS_FINISHED_LEVEL);
            return GWSTATUS_FINISHED_LEVEL;
        }
        return GWSTATUS_CONTINUE_GAME;      // so that the game can continue
    }

    ///////////////////////////////////////////next level////////////////////////////////////////////////////////

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
                          "HEALTH: " + to_string(iceman->getHealth() * 10) + "%" + "  " +
                          "WATER: " + to_string(iceman->getAmmo()) + "  "
                          + "GOLD: " + to_string(iceman->getGold()) + "  "
//                        + "OIL LEFT: " + to_string() + "
                            //   " barrel dist - amount collected
//                          "SONAR: " + to_string() + "  "
                          + "SCORE: " + to_string(getScore()) + "  ";
    
    setGameStatText(iceMan_stats);
}


//------------------------------------area for actors in oil field------------------------------------
int StudentWorld::boulderRandomX(){
    int rX = 0;
    if(ICE_WIDTH >= 0 || ICE_WIDTH > 37 || ICE_WIDTH < 26 || ICE_WIDTH <= 60){
        rX = (rand() % 56) + 4;
    }
    return rX;
}
int StudentWorld::boulderRandomY(){
    int rY = 0;
    if(ICE_HEIGHT <= 50 || ICE_HEIGHT >= 20){
        rY = rand() % 60;
    }
    return rY;
}
int StudentWorld::goldRandomX(){
    int rX;
    if(ICE_WIDTH >= 0 || ICE_WIDTH <60){
        rX = (rand() % 56) + 4;
    }
        return rX;
}
int StudentWorld::goldRandomY(){
    int rY;
    if(ICE_HEIGHT >= 0 || ICE_HEIGHT <= 56){
        rY = rand() % 60;
    }
        return rY;
}
int StudentWorld::barrelRandomX(){
    int rX;
    if(ICE_WIDTH >= 0 || ICE_WIDTH <60){
        rX = (rand() % 56) + 4;
    }
        return rX;
    
}
int StudentWorld::barrelRandomY(){
    int rY;
    if(ICE_HEIGHT >= 0 || ICE_HEIGHT <= 56){
        rY = rand() % 60;
    }
    return rY;
}

int StudentWorld::boulderAmnt(){
    int A = min(int (getLevel()/2) + 2, 9);
    return A;
}
int StudentWorld::goldNuggetAmnt(){
    int G = max(5-((int)getLevel()/2), 2);
    return G;
}
int StudentWorld::barrelAmnt(){
    int L = min(2 + (int) (getLevel()), 21);
    return L;
}

//------------------------------------area for actors in oil field------------------------------------

void StudentWorld::clearIce(int x, int y){
    //if iceman's location == the location of ice, delete ice
    //took the x(+- 1) and y(+- 3) position of iceman then made a for loop from the current position to calculated position to delete\\
    

        delete ice[x][y];
}
//no dirt behind object
//bool StudentWorld::noIceBehindObject(int x, int y) {
//    bool status = false;
//    for(int i = x; i < x + 4; i++){
//        for (int j = y; j < y + 4; j++){
//            if(isIce(x, y)){ //if there is ice, return status as true, delete ice
//                status = true;
//                Ice *tempIce = ice[i][j];
//                delete tempIce;
//            }
//        }
//    }
//    return status;
//}
//checking if there is ice here
bool StudentWorld::isIce(int x, int y){
    if(ice[x][y] != 0){
        return true;
    }
    return false;
}
