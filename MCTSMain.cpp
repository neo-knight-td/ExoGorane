//--------------------------------------------------------------------------------------------
//NOTE : make sure to include the correct constants ! It will define all the game parameters
#include "SimpleMazeConstants.h"
//--------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "MCTSNode.h"
#include "MCTSNode.cpp"
#include <cmath>
#include <chrono>

int main()
{
    std::cout << "Hello Gorane !" << std::endl;

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
    int iteration = 10;
    
    double valueOfMCTS;
    int locationIncrement;

    //id of team playing first
    bool bTeamId = constants::GORANE_TEAM;

    //time at start of the game
    int startTime = 0;

    vector<string> teamNames = {"Enemy", "Goranes"};

    //init game state
    MCTSNode mctsNode = MCTSNode(simpleMaze,simpleRobots,bTeamId,timeUntilGasClosing, nullptr);

    mctsNode.printNode();

    while (!mctsNode.isTerminal())
    {
        std:cout << "Turn to " << teamNames[mctsNode.teamTakingItsTurn] << " team." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute minimax value & move to minimax
        std::tie(valueOfMCTS, locationIncrement) = mctsNode.runMCTS(iteration);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        std::cout << "Robot " << teamNames[mctsNode.teamTakingItsTurn] << " should move to "<< locationIncrement << "." << std::endl;
        std::cout << "Computing time was " << elapsed.count() << " microseconds" << endl;

        //update node
        mctsNode.configureRobotsLocationInChildNode(mctsNode.robots, locationIncrement);
        mctsNode.configureCoinsInChildNode(mctsNode.maze, mctsNode.robots);
        mctsNode.configureGasInChildNode(mctsNode.maze, &timeUntilGasClosing);
        mctsNode.configureRobotsLivesInChildNode(mctsNode.maze, mctsNode.robots);
        mctsNode.configureTeamInChildNode(mctsNode.robots, &mctsNode.teamTakingItsTurn);

        //print new node
        mctsNode.printNode();
    }

    std::cout << "Game Over" << endl;

}