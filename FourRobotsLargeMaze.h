#ifndef FOUR_ROBOTS_LARGE_MAZE_H
#define FOUR_ROBOTS_LARGE_MAZE_H

#include "Constants.h"

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
            {DOWN_MASK + RIGHT_MASK},//1
            {UP_MASK + DOWN_MASK},//2
            {UP_MASK + DOWN_MASK},//3
            {UP_MASK + RIGHT_MASK},//4
            {DOWN_MASK + RIGHT_MASK},//5
            {UP_MASK + RIGHT_MASK},//6
            {DOWN_MASK + RIGHT_MASK},//7
            {UP_MASK + RIGHT_MASK},//8
            {DOWN_MASK + RIGHT_MASK},//9
            {UP_MASK + RIGHT_MASK},//10
            {DOWN_MASK + RIGHT_MASK},//11
            {UP_MASK + DOWN_MASK},//12
            {UP_MASK + DOWN_MASK},//13
            {UP_MASK + RIGHT_MASK},//14
            // column 2
            {DOWN_MASK + LEFT_MASK + RIGHT_MASK},//1
            {UP_MASK + RIGHT_MASK},//2
            {DOWN_MASK + RIGHT_MASK},//3
            {UP_MASK + DOWN_MASK + LEFT_MASK},//4
            {UP_MASK + LEFT_MASK},//5
            {LEFT_MASK + RIGHT_MASK},//6
            {LEFT_MASK + RIGHT_MASK},//7
            {LEFT_MASK + RIGHT_MASK},//8
            {LEFT_MASK + RIGHT_MASK},//9
            {DOWN_MASK + LEFT_MASK},//10
            {UP_MASK + DOWN_MASK + LEFT_MASK},//11
            {UP_MASK + RIGHT_MASK},//12
            {DOWN_MASK + RIGHT_MASK},//13
            {UP_MASK + LEFT_MASK + RIGHT_MASK},//14
            // column 3
            {LEFT_MASK + RIGHT_MASK},//1
            {LEFT_MASK + RIGHT_MASK},//2
            {DOWN_MASK + LEFT_MASK},//3
            {UP_MASK + RIGHT_MASK},//4
            {DOWN_MASK + RIGHT_MASK},//5
            {UP_MASK + LEFT_MASK},//6
            {LEFT_MASK + RIGHT_MASK},//7
            {LEFT_MASK + RIGHT_MASK},//8
            {DOWN_MASK + LEFT_MASK},//9
            {UP_MASK + RIGHT_MASK},//10
            {DOWN_MASK + RIGHT_MASK},//11
            {UP_MASK + LEFT_MASK},//12
            {LEFT_MASK + RIGHT_MASK},//13
            {LEFT_MASK + RIGHT_MASK},//14
            // column 4
            {LEFT_MASK + RIGHT_MASK},//1
            {DOWN_MASK + LEFT_MASK},//2
            {UP_MASK + DOWN_MASK},//3
            {UP_MASK + LEFT_MASK},//4
            {LEFT_MASK + RIGHT_MASK},//5
            {DOWN_MASK + RIGHT_MASK},//6
            {UP_MASK + DOWN_MASK + LEFT_MASK},//7
            {UP_MASK + DOWN_MASK + LEFT_MASK},//8
            {UP_MASK + RIGHT_MASK},//9
            {LEFT_MASK + RIGHT_MASK},//10
            {DOWN_MASK + LEFT_MASK},//11
            {UP_MASK + DOWN_MASK},//12
            {LEFT_MASK + UP_MASK},//13
            {LEFT_MASK + RIGHT_MASK},//14
            // column 5
            {DOWN_MASK + LEFT_MASK},//1
            {UP_MASK + RIGHT_MASK},//2
            {DOWN_MASK + RIGHT_MASK},//3
            {UP_MASK + DOWN_MASK},//4
            {UP_MASK + DOWN_MASK + LEFT_MASK + RIGHT_MASK},//5
            {UP_MASK + LEFT_MASK},//6
            {DOWN_MASK + RIGHT_MASK},//7
            {UP_MASK + RIGHT_MASK},//8
            {DOWN_MASK + LEFT_MASK},//9
            {UP_MASK + DOWN_MASK + LEFT_MASK + RIGHT_MASK},//10
            {UP_MASK + DOWN_MASK},//11
            {UP_MASK + RIGHT_MASK},//12
            {DOWN_MASK + RIGHT_MASK},//13
            {UP_MASK + LEFT_MASK},//14
            // column 6
            {DOWN_MASK + RIGHT_MASK},//1
            {UP_MASK + LEFT_MASK},//2
            {DOWN_MASK + LEFT_MASK + RIGHT_MASK},//3
            {UP_MASK},//4
            {DOWN_MASK + LEFT_MASK},//5
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//6
            {UP_MASK + LEFT_MASK},//7
            {DOWN_MASK + LEFT_MASK + RIGHT_MASK},//8
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//9
            {UP_MASK + LEFT_MASK},//10
            {DOWN_MASK},//11
            {UP_MASK + LEFT_MASK + RIGHT_MASK},//12
            {DOWN_MASK + LEFT_MASK},//13
            {UP_MASK + RIGHT_MASK},//14
            // column 7
            {DOWN_MASK + LEFT_MASK + RIGHT_MASK},//1
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//2
            {UP_MASK + LEFT_MASK},//3
            {DOWN_MASK + RIGHT_MASK},//4
            {UP_MASK + DOWN_MASK},//5
            {UP_MASK + DOWN_MASK + LEFT_MASK},//6
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//7
            {UP_MASK + LEFT_MASK + RIGHT_MASK},//8
            {DOWN_MASK + LEFT_MASK},//9
            {UP_MASK + DOWN_MASK},//10
            {UP_MASK + RIGHT_MASK},//11
            {DOWN_MASK + LEFT_MASK},//12
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//13
            {UP_MASK + LEFT_MASK + RIGHT_MASK},//14
            // column 8
            {DOWN_MASK + RIGHT_MASK + LEFT_MASK},//1
            {UP_MASK + DOWN_MASK + LEFT_MASK},//2
            {UP_MASK + RIGHT_MASK},//3
            {DOWN_MASK + LEFT_MASK},//4
            {UP_MASK + DOWN_MASK},//5
            {UP_MASK + RIGHT_MASK},//6
            {RIGHT_MASK + DOWN_MASK + LEFT_MASK},//7
            {UP_MASK + DOWN_MASK + LEFT_MASK},//8
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//9
            {UP_MASK + DOWN_MASK},//10
            {UP_MASK + LEFT_MASK},//11
            {DOWN_MASK + RIGHT_MASK},//12
            {UP_MASK + DOWN_MASK + LEFT_MASK},//13
            {UP_MASK + RIGHT_MASK + LEFT_MASK},//14
            // column 9
            {DOWN_MASK + LEFT_MASK},//1
            {UP_MASK + RIGHT_MASK},//2
            {DOWN_MASK + RIGHT_MASK + LEFT_MASK},//3
            {UP_MASK},//4
            {DOWN_MASK + RIGHT_MASK},//5
            {UP_MASK + DOWN_MASK + LEFT_MASK},//6
            {UP_MASK + RIGHT_MASK + LEFT_MASK},//7
            {DOWN_MASK + RIGHT_MASK},//8
            {UP_MASK + DOWN_MASK + LEFT_MASK},//9
            {UP_MASK + RIGHT_MASK},//10
            {DOWN_MASK},//11
            {UP_MASK + RIGHT_MASK + LEFT_MASK},//12
            {DOWN_MASK + RIGHT_MASK},//13
            {UP_MASK + LEFT_MASK},//14
            // column 10
            {DOWN_MASK + RIGHT_MASK},//1
            {UP_MASK + LEFT_MASK},//2
            {DOWN_MASK + LEFT_MASK},//3
            {UP_MASK + DOWN_MASK},//4
            {UP_MASK + DOWN_MASK + RIGHT_MASK + LEFT_MASK},//5
            {UP_MASK + RIGHT_MASK},//6
            {DOWN_MASK + LEFT_MASK},//7
            {UP_MASK + LEFT_MASK},//8
            {DOWN_MASK + RIGHT_MASK},//9
            {UP_MASK + DOWN_MASK + RIGHT_MASK + LEFT_MASK},//10
            {UP_MASK + DOWN_MASK},//11
            {UP_MASK + LEFT_MASK},//12
            {DOWN_MASK + LEFT_MASK},//13
            {UP_MASK + RIGHT_MASK},//14
            // column 11
            {RIGHT_MASK + LEFT_MASK},//1
            {DOWN_MASK + RIGHT_MASK},//2
            {UP_MASK + DOWN_MASK},//3
            {UP_MASK + RIGHT_MASK},//4
            {RIGHT_MASK + LEFT_MASK},//5
            {DOWN_MASK + LEFT_MASK},//6
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//7
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//8
            {UP_MASK + LEFT_MASK},//9
            {RIGHT_MASK + LEFT_MASK},//10
            {DOWN_MASK + RIGHT_MASK},//11
            {UP_MASK + DOWN_MASK},//12
            {RIGHT_MASK + UP_MASK},//13
            {RIGHT_MASK + LEFT_MASK},//14
            // column 12
            {RIGHT_MASK + LEFT_MASK},//1
            {RIGHT_MASK + LEFT_MASK},//2
            {DOWN_MASK + RIGHT_MASK},//3
            {UP_MASK + LEFT_MASK},//4
            {DOWN_MASK + LEFT_MASK},//5
            {UP_MASK + RIGHT_MASK},//6
            {RIGHT_MASK + LEFT_MASK},//7
            {RIGHT_MASK + LEFT_MASK},//8
            {DOWN_MASK + RIGHT_MASK},//9
            {UP_MASK + LEFT_MASK},//10
            {DOWN_MASK + LEFT_MASK},//11
            {UP_MASK + RIGHT_MASK},//12
            {RIGHT_MASK + LEFT_MASK},//13
            {RIGHT_MASK + LEFT_MASK},//14
            // column 13
            {DOWN_MASK + RIGHT_MASK + LEFT_MASK},//1
            {UP_MASK + LEFT_MASK},//2
            {DOWN_MASK + LEFT_MASK},//3
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//4
            {UP_MASK + RIGHT_MASK},//5
            {RIGHT_MASK + LEFT_MASK},//6
            {RIGHT_MASK + LEFT_MASK},//7
            {RIGHT_MASK + LEFT_MASK},//8
            {RIGHT_MASK + LEFT_MASK},//9
            {DOWN_MASK + RIGHT_MASK},//10
            {UP_MASK + DOWN_MASK + RIGHT_MASK},//11
            {UP_MASK + LEFT_MASK},//12
            {DOWN_MASK + LEFT_MASK},//13
            {UP_MASK + RIGHT_MASK + LEFT_MASK},//14
            // column 14
            {DOWN_MASK + LEFT_MASK},//1
            {UP_MASK + DOWN_MASK},//2
            {UP_MASK + DOWN_MASK},//3
            {UP_MASK + LEFT_MASK},//4
            {DOWN_MASK + LEFT_MASK},//5
            {UP_MASK + LEFT_MASK},//6
            {DOWN_MASK + LEFT_MASK},//7
            {UP_MASK + LEFT_MASK},//8
            {DOWN_MASK + LEFT_MASK},//9
            {UP_MASK + LEFT_MASK},//10
            {DOWN_MASK + LEFT_MASK},//11
            {UP_MASK + DOWN_MASK},//12
            {UP_MASK + DOWN_MASK},//13
            {UP_MASK + LEFT_MASK}//14
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