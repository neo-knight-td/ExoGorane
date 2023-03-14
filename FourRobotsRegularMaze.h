#include "Constants.h"

#ifndef FOUR_ROBOTS_REGULAR_MAZE_H
#define FOUR_ROBOTS_REGULAR_MAZE_H

namespace game
{
    // G only way to win is to pursue coin closest to E first ($ in square 19)

    // game specific constants
    // define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 36;
    // define total number of coins
    inline const int NB_OF_COINS = 20;//32;
    inline const int MAZE_WIDTH = 6;
    inline const char MAZE[NB_OF_MAZE_SQUARES] =
        {
            // first column
            {constants::RIGHT_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::RIGHT_MASK},
            {constants::DOWN_MASK},
            {constants::RIGHT_MASK + constants::UP_MASK + constants::DOWN_MASK},
            {constants::RIGHT_MASK + constants::UP_MASK},
            // second column
            {constants::RIGHT_MASK + constants::LEFT_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::RIGHT_MASK},
            {constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},
            {constants::UP_MASK + constants::LEFT_MASK},
            {constants::RIGHT_MASK + constants::LEFT_MASK},
            // third column
            {constants::LEFT_MASK},
            {constants::RIGHT_MASK + constants::LEFT_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},
            {constants::RIGHT_MASK + constants::DOWN_MASK},
            {constants::LEFT_MASK + constants::UP_MASK},
            // fourth column
            {constants::RIGHT_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::LEFT_MASK},
            {constants::RIGHT_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},
            {constants::RIGHT_MASK},
            // fith column
            {constants::LEFT_MASK + constants::RIGHT_MASK},
            {constants::DOWN_MASK + constants::RIGHT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::RIGHT_MASK},
            {constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::RIGHT_MASK + constants::LEFT_MASK + constants::UP_MASK},
            // sixth column
            {constants::LEFT_MASK + constants::DOWN_MASK},
            {constants::DOWN_MASK + constants::LEFT_MASK + constants::UP_MASK},
            {constants::UP_MASK},
            {constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::DOWN_MASK + constants::UP_MASK},
            {constants::LEFT_MASK + constants::UP_MASK},
    };
    inline const int NB_OF_TEAMS = 2;
    // define the number of robots in the game
    inline const int NB_OF_ROBOTS = 4;
    // define nb of robots per team
    inline const int NB_OF_ROBOTS_PER_TEAM = 2;
    // branching factor is 5 for the moment (2 robot per team)
    inline const int BRANCHING_FACTOR = 5;
    // define G1 default initial location
    inline const int GORANE1_DEFAULT_LOCATION = 33;
    // define G2 default initial location
    inline const int GORANE2_DEFAULT_LOCATION = 17;
    // define E1 default initial location
    inline const int ENEMY1_DEFAULT_LOCATION = 2;
    // define E2 default initial location
    inline const int ENEMY2_DEFAULT_LOCATION = 18;
    // define interval at which gas closes
    inline const int GAS_CLOSING_INTERVAL = 2;

}

#endif