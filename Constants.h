#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace constants
{
    //TODO : confirm that "inline" should be used https://www.fluentcpp.com/2019/07/23/how-to-define-a-global-constant-in-cpp/

    //define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 9;
    inline const int MAZE_WIDTH = 3;
    //define the number of robots in the game
    inline const int NB_OF_ROBOTS = 2;
    //define interval at which gas closes
    inline const int GAS_CLOSING_INTERVAL = 6;

    //define masks (value(s) held by each square in the maze array)
    inline const char UP_MASK = 1;
    inline const char RIGHT_MASK = 2;
    inline const char DOWN_MASK = 4;
    inline const char LEFT_MASK = 8;
    inline const char COIN_MASK = 16;
    inline const char GAS_MASK = 32;//gas mask... lol, #warzone
}

#endif