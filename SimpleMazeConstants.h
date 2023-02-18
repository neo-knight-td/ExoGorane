#ifndef SIMPLE_MAZE_CONSTANTS_H
#define SIMPLE_MAZE_CONSTANTS_H
namespace constants
{
    //TODO : confirm that "inline" should be used https://www.fluentcpp.com/2019/07/23/how-to-define-a-global-constant-in-cpp/

    inline const int INT_DUMMY_VALUE = -1;
    inline const char CHAR_DUMMY_VALUE = -1;
    inline const bool GORANE_TEAM = true;
    inline const bool ENEMY_TEAM = false;
    inline const double MAX_NODE_VALUE = 1.0;
    inline const double MIN_NODE_VALUE = 0.0;
    inline const char UP_MASK = 1;
    inline const char RIGHT_MASK = 2;
    inline const char DOWN_MASK = 4;
    inline const char LEFT_MASK = 8;
    inline const char COIN_MASK = 16;
    inline const char GAS_MASK = 32;//gas mask... lol, #warzone

    //game specific constants
    //define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 9;
    //define total number of coins 
    inline const int NB_OF_COINS = 1;
    inline const int MAZE_WIDTH = 3;
    inline const char MAZE[NB_OF_MAZE_SQUARES] =
    {
        {COIN_MASK +  RIGHT_MASK + DOWN_MASK},
        {UP_MASK + RIGHT_MASK + DOWN_MASK},
        {UP_MASK + RIGHT_MASK},
        {RIGHT_MASK + DOWN_MASK + LEFT_MASK},
        {UP_MASK + RIGHT_MASK + DOWN_MASK + LEFT_MASK},
        {UP_MASK + RIGHT_MASK + LEFT_MASK},
        {DOWN_MASK + LEFT_MASK},
        {UP_MASK + DOWN_MASK + LEFT_MASK},
        {UP_MASK + LEFT_MASK}
    };
    //define the number of robots in the game
    inline const int NB_OF_ROBOTS = 2;
    //branching factor is 5 for the moment (1 robot per team)
    inline const int BRANCHING_FACTOR = 5;
    //define G default initial location
    inline const int GORANE_DEFAULT_LOCATION = 4;
    //define E default initial location
    inline const int ENEMY_DEFAULT_LOCATION = 8;
    //define interval at which gas closes
    inline const int GAS_CLOSING_INTERVAL = 30;

}

#endif