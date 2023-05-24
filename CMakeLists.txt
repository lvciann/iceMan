cmake_minimum_required(VERSION 3.25)
project(iceMan)

set(CMAKE_CXX_STANDARD 14)

add_executable(iceMan
        main.cpp StudentWorld.cpp StudentWorld.h Actor.h GraphObject.cpp GraphObject.h GameController.cpp GameController.h GameWorld.cpp GameWorld.h GameConstants.cpp GameConstants.h freeglut.h freeglut_std.h freeglut_ext.h SpriteManager.h SoundFX.h Actor.cpp)
