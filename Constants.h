#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace constants
{
    //TODO : confirm that "inline" should be used https://www.fluentcpp.com/2019/07/23/how-to-define-a-global-constant-in-cpp/

    inline const int INT_DUMMY_VALUE = -1;
    inline const char CHAR_DUMMY_VALUE = -1;
    inline const bool GORANE_TEAM = true;
    inline const bool ENEMY_TEAM = false;
    inline const double MAX_NODE_VALUE = 1.0;
    inline const double MIN_NODE_VALUE = 0.0;
    //branching factor is 5 for the moment (1 robot per team)
    inline const int BRANCHING_FACTOR = 5;
    //define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 9;
    inline const int MAZE_WIDTH = 3;
    //define the number of robots in the game
    inline const int NB_OF_ROBOTS = 2;
    //define interval at which gas closes
    inline const int GAS_CLOSING_INTERVAL = 30;
    //define total number of coints 
    inline const int NB_OF_COINS = 1;

    //define masks (value(s) held by each square in the maze array)
    inline const char UP_MASK = 1;
    inline const char RIGHT_MASK = 2;
    inline const char DOWN_MASK = 4;
    inline const char LEFT_MASK = 8;
    inline const char COIN_MASK = 16;
    inline const char GAS_MASK = 32;//gas mask... lol, #warzone

    //parameters for Minimax :
    //inline const int MAX_DEPTH = 10;

}

#endif