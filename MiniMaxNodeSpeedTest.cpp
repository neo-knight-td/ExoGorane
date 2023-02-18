//--------------------------------------------------------------------------------------------
//NOTE : make sure to include the correct constants ! It will define all the game parameters.
#include "SimpleMazeConstants.h"
//--------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include <cmath>
#include <chrono>
#include <numeric>
#include "MinimaxNode.h"
#include "MinimaxNode.cpp"

int main()
{
    std::cout << "Hello Tester !" << std::endl;

    //retrieve all game parameters from constant file
    char simpleMaze[constants::NB_OF_MAZE_SQUARES];
    for (int i = 0; i < constants::NB_OF_MAZE_SQUARES; i++)
        simpleMaze[i] = constants::MAZE[i];
    struct Robot simpleRobotG = {constants::GORANE_DEFAULT_LOCATION, 0, true};
    struct Robot simpleRobotE = {constants::ENEMY_DEFAULT_LOCATION, 0, true};
    Robot simpleRobots[constants::NB_OF_ROBOTS];
    simpleRobots[constants::GORANE_TEAM] = simpleRobotG;
    simpleRobots[constants::ENEMY_TEAM] = simpleRobotE;
    int timeUntilGasClosing = constants::GAS_CLOSING_INTERVAL;
    int maxDepth = 10;
    
    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    bool bTeamId = constants::GORANE_TEAM;

    //time at start of the game
    int startTime = 0;

    //current depth
    int depth = 0;

    int counter = 0;
    int counterLimit = 1;
    vector<int> cpuTimes;

    //init game state
    MinimaxNode testMinimaxNode = MinimaxNode(simpleMaze, simpleRobots, bTeamId, timeUntilGasClosing, depth, maxDepth);

    while (counter < counterLimit)
    {
        auto begin = std::chrono::high_resolution_clock::now();

        //compute Minimax
        std::tie(valueOfMinimax, moveToMinimax, std::ignore) = testMinimaxNode.getMinimax();

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        cpuTimes.push_back(elapsed.count());

        counter++;
    }

    testMinimaxNode.printNode();

    int sum_of_elems = std::accumulate(cpuTimes.begin(), cpuTimes.end(), 0);

    //average computing time is 8 ms on Thomas Desktop
    std::cout << "Average Computing time equals " << sum_of_elems/cpuTimes.size() << " milliseconds." << endl;
    
}