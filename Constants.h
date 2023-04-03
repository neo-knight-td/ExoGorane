#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>

    //TODO : confirm that "inline" should be used https://www.fluentcpp.com/2019/07/23/how-to-define-a-global-constant-in-cpp/

    //NOTE : this constants needs to be adapted everytime a simulation from another maze size launched !
    extern const int NB_OF_MAZE_SQUARES = 36;//196 or 36

    extern const int MAZE_WIDTH = sqrt(NB_OF_MAZE_SQUARES);
    extern const int BRANCHING_FACTOR = 5;
    extern const int NB_OF_TEAMS = 2;
    extern const int NB_OF_ROBOTS_PER_TEAMS = 2;
    extern const int INT_DUMMY_VALUE = -1;
    extern const char CHAR_DUMMY_VALUE = -1;
    extern const char GORANE_TEAM = true;
    extern const char ENEMY_TEAM = false;
    extern const double MAX_NODE_VALUE = 1.0;
    extern const double MIN_NODE_VALUE = 0.0;
    extern const double DRAW_NODE_VALUE = 0.5;
    extern const char UP_MASK = 1;
    extern const char RIGHT_MASK = 2;
    extern const char DOWN_MASK = 4;
    extern const char LEFT_MASK = 8;
    extern const char COIN_MASK = 16;
    extern const char GAS_MASK = 32;//gas mask... lol, #warzone

    //parameters 4 robots
    extern const char GORANE1_INDEX = 0;
    extern const char GORANE2_INDEX = 1;
    extern const char ENEMY1_INDEX = 0;
    extern const char ENEMY2_INDEX = 1;

#endif