#include "Constants.h"

#ifndef FOUR_ROBOTS_LARGE_MAZE_H
#define FOUR_ROBOTS_LARGE_MAZE_H

namespace game
{

    // game specific constants
    // define the number of maze squares
    inline const int NB_OF_MAZE_SQUARES = 196;
    // define total number of coins
    inline const int NB_OF_COINS = 20;
    inline const int MAZE_WIDTH = 14;
    //NOTE : Maze copied from https://youtu.be/QLjniy3HG8o?t=75 (coins to be added)
    inline const char MAZE[NB_OF_MAZE_SQUARES] =
        {
            // column 1
            {constants::DOWN_MASK + constants::RIGHT_MASK},//1
            {constants::UP_MASK + constants::DOWN_MASK},//2
            {constants::UP_MASK + constants::DOWN_MASK},//3
            {constants::UP_MASK + constants::RIGHT_MASK},//4
            {constants::DOWN_MASK + constants::RIGHT_MASK},//5
            {constants::UP_MASK + constants::RIGHT_MASK},//6
            {constants::DOWN_MASK + constants::RIGHT_MASK},//7
            {constants::UP_MASK + constants::RIGHT_MASK},//8
            {constants::DOWN_MASK + constants::RIGHT_MASK},//9
            {constants::UP_MASK + constants::RIGHT_MASK},//10
            {constants::DOWN_MASK + constants::RIGHT_MASK},//11
            {constants::UP_MASK + constants::DOWN_MASK},//12
            {constants::UP_MASK + constants::DOWN_MASK},//13
            {constants::UP_MASK + constants::RIGHT_MASK},//14
            // column 2
            {constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//1
            {constants::UP_MASK + constants::RIGHT_MASK},//2
            {constants::DOWN_MASK + constants::RIGHT_MASK},//3
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//4
            {constants::UP_MASK + constants::LEFT_MASK},//5
            {constants::LEFT_MASK + constants::RIGHT_MASK},//6
            {constants::LEFT_MASK + constants::RIGHT_MASK},//7
            {constants::LEFT_MASK + constants::RIGHT_MASK},//8
            {constants::LEFT_MASK + constants::RIGHT_MASK},//9
            {constants::DOWN_MASK + constants::LEFT_MASK},//10
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//11
            {constants::UP_MASK + constants::RIGHT_MASK},//12
            {constants::DOWN_MASK + constants::RIGHT_MASK},//13
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//14
            // column 3
            {constants::LEFT_MASK + constants::RIGHT_MASK},//1
            {constants::LEFT_MASK + constants::RIGHT_MASK},//2
            {constants::DOWN_MASK + constants::LEFT_MASK},//3
            {constants::UP_MASK + constants::RIGHT_MASK},//4
            {constants::DOWN_MASK + constants::RIGHT_MASK},//5
            {constants::UP_MASK + constants::LEFT_MASK},//6
            {constants::LEFT_MASK + constants::RIGHT_MASK},//7
            {constants::LEFT_MASK + constants::RIGHT_MASK},//8
            {constants::DOWN_MASK + constants::LEFT_MASK},//9
            {constants::UP_MASK + constants::RIGHT_MASK},//10
            {constants::DOWN_MASK + constants::RIGHT_MASK},//11
            {constants::UP_MASK + constants::LEFT_MASK},//12
            {constants::LEFT_MASK + constants::RIGHT_MASK},//13
            {constants::LEFT_MASK + constants::RIGHT_MASK},//14
            // column 4
            {constants::LEFT_MASK + constants::RIGHT_MASK},//1
            {constants::DOWN_MASK + constants::LEFT_MASK},//2
            {constants::UP_MASK + constants::DOWN_MASK},//3
            {constants::UP_MASK + constants::LEFT_MASK},//4
            {constants::LEFT_MASK + constants::RIGHT_MASK},//5
            {constants::DOWN_MASK + constants::RIGHT_MASK},//6
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//7
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//8
            {constants::UP_MASK + constants::RIGHT_MASK},//9
            {constants::LEFT_MASK + constants::RIGHT_MASK},//10
            {constants::DOWN_MASK + constants::LEFT_MASK},//11
            {constants::UP_MASK + constants::DOWN_MASK},//12
            {constants::LEFT_MASK + constants::UP_MASK},//13
            {constants::LEFT_MASK + constants::RIGHT_MASK},//14
            // column 5
            {constants::DOWN_MASK + constants::LEFT_MASK},//1
            {constants::UP_MASK + constants::RIGHT_MASK},//2
            {constants::DOWN_MASK + constants::RIGHT_MASK},//3
            {constants::UP_MASK + constants::DOWN_MASK},//4
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//5
            {constants::UP_MASK + constants::LEFT_MASK},//6
            {constants::DOWN_MASK + constants::RIGHT_MASK},//7
            {constants::UP_MASK + constants::RIGHT_MASK},//8
            {constants::DOWN_MASK + constants::LEFT_MASK},//9
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//10
            {constants::UP_MASK + constants::DOWN_MASK},//11
            {constants::UP_MASK + constants::RIGHT_MASK},//12
            {constants::DOWN_MASK + constants::RIGHT_MASK},//13
            {constants::UP_MASK + constants::LEFT_MASK},//14
            // column 6
            {constants::DOWN_MASK + constants::RIGHT_MASK},//1
            {constants::UP_MASK + constants::LEFT_MASK},//2
            {constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//3
            {constants::UP_MASK},//4
            {constants::DOWN_MASK + constants::LEFT_MASK},//5
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//6
            {constants::UP_MASK + constants::LEFT_MASK},//7
            {constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//8
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//9
            {constants::UP_MASK + constants::LEFT_MASK},//10
            {constants::DOWN_MASK},//11
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//12
            {constants::DOWN_MASK + constants::LEFT_MASK},//13
            {constants::UP_MASK + constants::RIGHT_MASK},//14
            // column 7
            {constants::DOWN_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//1
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//2
            {constants::UP_MASK + constants::LEFT_MASK},//3
            {constants::DOWN_MASK + constants::RIGHT_MASK},//4
            {constants::UP_MASK + constants::DOWN_MASK},//5
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//6
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//7
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//8
            {constants::DOWN_MASK + constants::LEFT_MASK},//9
            {constants::UP_MASK + constants::DOWN_MASK},//10
            {constants::UP_MASK + constants::RIGHT_MASK},//11
            {constants::DOWN_MASK + constants::LEFT_MASK},//12
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//13
            {constants::UP_MASK + constants::LEFT_MASK + constants::RIGHT_MASK},//14
            // column 8
            {constants::DOWN_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//1
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//2
            {constants::UP_MASK + constants::RIGHT_MASK},//3
            {constants::DOWN_MASK + constants::LEFT_MASK},//4
            {constants::UP_MASK + constants::DOWN_MASK},//5
            {constants::UP_MASK + constants::RIGHT_MASK},//6
            {constants::RIGHT_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//7
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//8
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//9
            {constants::UP_MASK + constants::DOWN_MASK},//10
            {constants::UP_MASK + constants::LEFT_MASK},//11
            {constants::DOWN_MASK + constants::RIGHT_MASK},//12
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//13
            {constants::UP_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//14
            // column 9
            {constants::DOWN_MASK + constants::LEFT_MASK},//1
            {constants::UP_MASK + constants::RIGHT_MASK},//2
            {constants::DOWN_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//3
            {constants::UP_MASK},//4
            {constants::DOWN_MASK + constants::RIGHT_MASK},//5
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//6
            {constants::UP_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//7
            {constants::DOWN_MASK + constants::RIGHT_MASK},//8
            {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},//9
            {constants::UP_MASK + constants::RIGHT_MASK},//10
            {constants::DOWN_MASK},//11
            {constants::UP_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//12
            {constants::DOWN_MASK + constants::RIGHT_MASK},//13
            {constants::UP_MASK + constants::LEFT_MASK},//14
            // column 10
            {constants::DOWN_MASK + constants::RIGHT_MASK},//1
            {constants::UP_MASK + constants::LEFT_MASK},//2
            {constants::DOWN_MASK + constants::LEFT_MASK},//3
            {constants::UP_MASK + constants::DOWN_MASK},//4
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//5
            {constants::UP_MASK + constants::RIGHT_MASK},//6
            {constants::DOWN_MASK + constants::LEFT_MASK},//7
            {constants::UP_MASK + constants::LEFT_MASK},//8
            {constants::DOWN_MASK + constants::RIGHT_MASK},//9
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//10
            {constants::UP_MASK + constants::DOWN_MASK},//11
            {constants::UP_MASK + constants::LEFT_MASK},//12
            {constants::DOWN_MASK + constants::LEFT_MASK},//13
            {constants::UP_MASK + constants::RIGHT_MASK},//14
            // column 11
            {constants::RIGHT_MASK + constants::LEFT_MASK},//1
            {constants::DOWN_MASK + constants::RIGHT_MASK},//2
            {constants::UP_MASK + constants::DOWN_MASK},//3
            {constants::UP_MASK + constants::RIGHT_MASK},//4
            {constants::RIGHT_MASK + constants::LEFT_MASK},//5
            {constants::DOWN_MASK + constants::LEFT_MASK},//6
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//7
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//8
            {constants::UP_MASK + constants::LEFT_MASK},//9
            {constants::RIGHT_MASK + constants::LEFT_MASK},//10
            {constants::DOWN_MASK + constants::RIGHT_MASK},//11
            {constants::UP_MASK + constants::DOWN_MASK},//12
            {constants::RIGHT_MASK + constants::UP_MASK},//13
            {constants::RIGHT_MASK + constants::LEFT_MASK},//14
            // column 12
            {constants::RIGHT_MASK + constants::LEFT_MASK},//1
            {constants::RIGHT_MASK + constants::LEFT_MASK},//2
            {constants::DOWN_MASK + constants::RIGHT_MASK},//3
            {constants::UP_MASK + constants::LEFT_MASK},//4
            {constants::DOWN_MASK + constants::LEFT_MASK},//5
            {constants::UP_MASK + constants::RIGHT_MASK},//6
            {constants::RIGHT_MASK + constants::LEFT_MASK},//7
            {constants::RIGHT_MASK + constants::LEFT_MASK},//8
            {constants::DOWN_MASK + constants::RIGHT_MASK},//9
            {constants::UP_MASK + constants::LEFT_MASK},//10
            {constants::DOWN_MASK + constants::LEFT_MASK},//11
            {constants::UP_MASK + constants::RIGHT_MASK},//12
            {constants::RIGHT_MASK + constants::LEFT_MASK},//13
            {constants::RIGHT_MASK + constants::LEFT_MASK},//14
            // column 13
            {constants::DOWN_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//1
            {constants::UP_MASK + constants::LEFT_MASK},//2
            {constants::DOWN_MASK + constants::LEFT_MASK},//3
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//4
            {constants::UP_MASK + constants::RIGHT_MASK},//5
            {constants::RIGHT_MASK + constants::LEFT_MASK},//6
            {constants::RIGHT_MASK + constants::LEFT_MASK},//7
            {constants::RIGHT_MASK + constants::LEFT_MASK},//8
            {constants::RIGHT_MASK + constants::LEFT_MASK},//9
            {constants::DOWN_MASK + constants::RIGHT_MASK},//10
            {constants::UP_MASK + constants::DOWN_MASK + constants::RIGHT_MASK},//11
            {constants::UP_MASK + constants::LEFT_MASK},//12
            {constants::DOWN_MASK + constants::LEFT_MASK},//13
            {constants::UP_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},//14
            // column 14
            {constants::DOWN_MASK + constants::LEFT_MASK},//1
            {constants::UP_MASK + constants::DOWN_MASK},//2
            {constants::UP_MASK + constants::DOWN_MASK},//3
            {constants::UP_MASK + constants::LEFT_MASK},//4
            {constants::DOWN_MASK + constants::LEFT_MASK},//5
            {constants::UP_MASK + constants::LEFT_MASK},//6
            {constants::DOWN_MASK + constants::LEFT_MASK},//7
            {constants::UP_MASK + constants::LEFT_MASK},//8
            {constants::DOWN_MASK + constants::LEFT_MASK},//9
            {constants::UP_MASK + constants::LEFT_MASK},//10
            {constants::DOWN_MASK + constants::LEFT_MASK},//11
            {constants::UP_MASK + constants::DOWN_MASK},//12
            {constants::UP_MASK + constants::DOWN_MASK},//13
            {constants::UP_MASK + constants::LEFT_MASK}//14
    };
    inline const int NB_OF_TEAMS = 2;
    // define the number of robots in the game
    inline const int NB_OF_ROBOTS = 4;
    // define nb of robots per team
    inline const int NB_OF_ROBOTS_PER_TEAM = 2;
    // branching factor is 5 for the moment (2 robot per team)
    inline const int BRANCHING_FACTOR = 5;
    // define G1 default initial location
    inline const int GORANE1_DEFAULT_LOCATION = 195-6;
    // define G2 default initial location
    inline const int GORANE2_DEFAULT_LOCATION = 97;
    // define E1 default initial location
    inline const int ENEMY1_DEFAULT_LOCATION = 6;
    // define E2 default initial location
    inline const int ENEMY2_DEFAULT_LOCATION = 98;
    // define interval at which gas closes
    inline const int GAS_CLOSING_INTERVAL = 20;

}

#endif