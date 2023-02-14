#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "Minimax.cpp"
#include <cmath>
#include <chrono>
#include <numeric>
#include "LightGameState.cpp"
#include "Constants.h"

int main()
{
    std::cout << "Hello Tester !" << std::endl;

    //First Game State Object
    
    vector<vector <int>> mazeVector
    {
        {3,1},{0,4,2},{1,5},//column 1 of maze
        {6,4,0},{3,7,5,1},{4,8,2},//column 2 of maze
        {7,3},{6,8,4},{7,5}//column 3 of maze
    };
    int mazeHDim = 3;
    //list<int> coinsVector = {0,1,5,6,16,17,18,20,21,22,23,24};
    list<int> coinsVector = {0};
    Robot robotG = Robot(4, 0, true, true);
    Robot robotE = Robot(8, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 11;
    int gasClosingInterval = 6;
    

    /*
    000000 ==> 0 (no move)
    000001 ==> 1 (up)
    000010 ==> 2 (right)
    000100 ==> 4 (down)
    001000 ==> 8 (left)
    010000 ==> 16 (coin)
    100000 ==> 32 (gas)
    */

    const char UP = 1;
    const char RIGHT = 2;
    const char DOWN = 4;
    const char LEFT = 8;
    const char COIN = 16;
    const char GAS = 32;
    
    //second GameState Object
    char simpleMaze[9] =
    {
        {4+2+32},{7},{3},{14},{15},{11},{12},{13},{9}//column 3 of maze
    };

    struct SimpleRobot simpleRobotG = {4, 0, true};
    struct SimpleRobot simpleRobotE = {8, 0, true};
    //list<int> coinsVector = {0};
    SimpleRobot simpleRobots[2] = {simpleRobotE, simpleRobotG};
    //vector<SimpleRobot> simpleRobotVector = {simpleRobotG, simpleRobotE};



    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    int teamId = 0;
    bool bTeamId = true;

    //time at start of the game
    int startTime = 0;

    //current depth
    int depth = 0;
    vector<string> teamNames = {"Goranes", "Enemy"};

    //Minimax minimaxStrategy(maxDepth);
    int counter = 0;
    int counterLimit = 100;

    vector<int> cpuTimes;

    while (counter < counterLimit)
    {
        //init game state
        GameState testGameState = GameState(mazeVector, mazeHDim, coinsVector, robotVector, 0, teamId, false, startTime, gasClosingInterval);
        LightGameState testState = LightGameState(simpleMaze,simpleRobots, bTeamId, gasClosingInterval);
        //std:cout << "Turn to " << teamNames[teamId] << " team." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute
        //testGameState.generateSuccessors(teamId);
        testState.generateSuccessors();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        cpuTimes.push_back(elapsed.count());

        //std::cout << "Robot " << teamNames[teamId] << " should move to "<< moveToMinimax << "." << std::endl;
        //printf("Time measured: %.3f seconds.\n", elapsed.count()* 1e-3);
        counter++;
    }

    //std::cout << "Game Over" << endl;

    //std::cout << cpuTimes[0] << endl;

    int sum_of_elems = std::accumulate(cpuTimes.begin(), cpuTimes.end(), 0);

    std::cout << "Average Computing time equals " << sum_of_elems/cpuTimes.size() << " nanoseconds." << endl;
    
}