#ifndef CONSTANTS_H
#define CONSTANTS_H
namespace constants
{
    //TODO : confirm that "inline" should be used https://www.fluentcpp.com/2019/07/23/how-to-define-a-global-constant-in-cpp/

    inline const int INT_DUMMY_VALUE = -1;
    inline const char CHAR_DUMMY_VALUE = -1;
    inline const char GORANE_TEAM = true;
    inline const char ENEMY_TEAM = false;
    inline const double MAX_NODE_VALUE = 1.0;
    inline const double MIN_NODE_VALUE = 0.0;
    inline const double DRAW_NODE_VALUE = 0.5;
    inline const char UP_MASK = 1;
    inline const char RIGHT_MASK = 2;
    inline const char DOWN_MASK = 4;
    inline const char LEFT_MASK = 8;
    inline const char COIN_MASK = 16;
    inline const char GAS_MASK = 32;//gas mask... lol, #warzone

    //parameters 4 robots
    inline const char GORANE1_INDEX = 0;
    inline const char GORANE2_INDEX = 1;
    inline const char ENEMY1_INDEX = 0;
    inline const char ENEMY2_INDEX = 1;

}

#endif