#include "Constants.h"

#ifndef FOUR_ROBOTS_REGULAR_GAME_H
#define FOUR_ROBOTS_REGULAR_GAME_H

namespace game
{
    //  * * * * * *
    //   G     $
    //  *  -   - -*
    //    |   |
    //  *         *
    //          |
    //  *         *
    //          |
    //  *- - -    *
    //       $ $|E
    //  * * * * * *

    // G only way to win is to pursue coin closest to E first ($ in square 19)

    // game specific constants
    // define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 25;
    // define total number of coins
    inline const int NB_OF_COINS = 4;
    inline const int MAZE_WIDTH = 5;
    inline const char MAZE[NB_OF_MAZE_SQUARES] =
        {
            // first column
            {constants::RIGHT_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::RIGHT_MASK + constants::DOWN_MASK},
            {constants::RIGHT_MASK + constants::UP_MASK},
            {constants::RIGHT_MASK},
            // second column
            {constants::RIGHT_MASK + constants::LEFT_MASK},
            {constants::DOWN_MASK + constants::RIGHT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},
            {constants::RIGHT_MASK + constants::LEFT_MASK},
            // third column
            {constants::RIGHT_MASK + constants::LEFT_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK + constants::COIN_MASK},
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},
            {constants::RIGHT_MASK + constants::LEFT_MASK + constants::COIN_MASK},
            // fourth column
            {constants::RIGHT_MASK + constants::LEFT_MASK + constants::COIN_MASK},
            {constants::DOWN_MASK + constants::RIGHT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::LEFT_MASK + constants::COIN_MASK},
            // fith column
            {constants::LEFT_MASK},
            {constants::DOWN_MASK + constants::LEFT_MASK},
            {constants::UP_MASK + constants::DOWN_MASK},
            {constants::UP_MASK + constants::DOWN_MASK},
            {constants::UP_MASK},
    };
    inline const int NB_OF_TEAMS = 2;
    // define the number of robots in the game
    inline const int NB_OF_ROBOTS = 4;
    // define nb of robots per team
    inline const int NB_OF_ROBOTS_PER_TEAM = 2;
    // branching factor is 5 for the moment (2 robot per team)
    inline const int BRANCHING_FACTOR = 5;
    // define G1 default initial location
    inline const int GORANE1_DEFAULT_LOCATION = 0;
    // define G2 default initial location
    inline const int GORANE2_DEFAULT_LOCATION = 4;
    // define E1 default initial location
    inline const int ENEMY1_DEFAULT_LOCATION = 20;
    // define E2 default initial location
    inline const int ENEMY2_DEFAULT_LOCATION = 24;
    // define interval at which gas closes
    inline const int GAS_CLOSING_INTERVAL = 3;

}

#endif