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
#include "Constants.h"

int main()
{
    std::cout << "Hello Tester !" << std::endl;

    int maxDepth = 10;
    int gasClosingInterval = constants::GAS_CLOSING_INTERVAL;

    //Node Object
    
    char simpleMaze[9] =
    {
        {constants::COIN_MASK + constants::RIGHT_MASK + constants::DOWN_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK + constants::DOWN_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK},
        {constants::RIGHT_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::RIGHT_MASK + constants::LEFT_MASK},
        {constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::DOWN_MASK + constants::LEFT_MASK},
        {constants::UP_MASK + constants::LEFT_MASK}
    };

    struct Robot simpleRobotG = {4, 0, true};
    struct Robot simpleRobotE = {8, 0, true};
    Robot simpleRobots[2] = {simpleRobotE, simpleRobotG};
    

    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    bool bTeamId = constants::GORANE_TEAM;

    //time at start of the game
    int startTime = 0;

    //current depth
    int depth = 0;
    vector<string> teamNames = {"Goranes", "Enemy"};

    int counter = 0;
    int counterLimit = 100;
    vector<int> cpuTimes;

    //init game state
    MinimaxNode testMinimaxNode = MinimaxNode(simpleMaze, simpleRobots, bTeamId, gasClosingInterval, depth, maxDepth);

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

    std::cout << "Average Computing time equals " << sum_of_elems/cpuTimes.size() << " milliseconds." << endl;
    
}