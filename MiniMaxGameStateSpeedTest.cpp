#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include <cmath>
#include <chrono>
#include <numeric>
#include "Minimax.cpp"
#include "Constants.h"

int main()
{
    std::cout << "Hello Tester !" << std::endl;

    //Game State Object
    
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
    
    int maxDepth = 10;
    int gasClosingInterval = constants::GAS_CLOSING_INTERVAL;

    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    int teamId = 0;

    //time at start of the game
    int startTime = 0;

    //current depth
    int depth = 0;
    vector<string> teamNames = {"Goranes", "Enemy"};

    //Minimax minimaxStrategy(maxDepth);
    int counter = 0;
    int counterLimit = 100;

    vector<int> cpuTimes;

    //init game state
    GameState testGameState = GameState(mazeVector, mazeHDim, coinsVector, robotVector, 0, teamId, false, startTime, gasClosingInterval);
    Minimax minimaxStrategy(maxDepth);

    while (counter < counterLimit)
    {
        auto begin = std::chrono::high_resolution_clock::now();

        //compute
        std::tie(valueOfMinimax, moveToMinimax, std::ignore, std::ignore, std::ignore) = minimaxStrategy.getValueOfNextState(testGameState, teamId);

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        cpuTimes.push_back(elapsed.count());
        counter++;
    }

    testGameState.printGameState();

    int sum_of_elems = std::accumulate(cpuTimes.begin(), cpuTimes.end(), 0);

    std::cout << "Average Computing time equals " << sum_of_elems/cpuTimes.size() << " milliseconds." << endl;
    
}