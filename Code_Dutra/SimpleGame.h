#include "Constants.h"

#ifndef SIMPLE_GAME_H
#define SIMPLE_GAME_H

namespace game
{

    //game specific constants
    //define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 9;
    //define total number of coins 
    inline const int NB_OF_COINS = 1;
    inline const int MAZE_WIDTH = 3;
    inline const char MAZE[NB_OF_MAZE_SQUARES] =
    {
        {constants::COIN_MASK +  constants::RIGHT_MASK + constants::DOWN_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK + constants::DOWN_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK},
        {constants::RIGHT_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},
        {constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::LEFT_MASK}
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
    inline const int GAS_CLOSING_INTERVAL = 1000;

}

#endif