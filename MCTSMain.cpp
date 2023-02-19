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
    int maxDepth = 10;
    
    double valueOfMCTS;
    int locationIncrement;

    //id of team playing first
    bool bTeamId = constants::GORANE_TEAM;

    //time at start of the game
    int startTime = 0;

    vector<string> teamNames = {"Enemy", "Goranes"};

    //init game state
    MCTSNode mctsNode = MCTSNode(simpleMaze,simpleRobots,bTeamId,timeUntilGasClosing);
    
    bool result = mctsNode.simulate();
    mctsNode.generateChildren();

    /*

    while (!mctsNode.isTerminal())
    {
        std:cout << "Turn to " << teamNames[minimaxNode.teamTakingItsTurn] << " team." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute minimax value & move to minimax
        std::tie(valueOfMCTS, moveToMinimax, std::ignore) = minimaxNode.runMinimax();
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        std::cout << "Robot " << teamNames[minimaxNode.teamTakingItsTurn] << " should move to "<< moveToMinimax << "." << std::endl;
        std::cout << "Computing time was " << elapsed.count() << " milliseconds" << endl;

        //update node
        minimaxNode.configureRobotsLocationInChildNode(minimaxNode.robots, moveToMinimax);
        minimaxNode.configureCoinsInChildNode(minimaxNode.maze, minimaxNode.robots);
        minimaxNode.configureGasInChildNode(minimaxNode.maze, &timeUntilGasClosing);
        minimaxNode.configureRobotsLivesInChildNode(minimaxNode.maze, minimaxNode.robots);
        minimaxNode.configureTeamInChildNode(minimaxNode.robots, &minimaxNode.teamTakingItsTurn);

        //print new node
        minimaxNode.printNode();
    }
    */

    std::cout << "Game Over" << endl;
    std::cout << "Result is " << result << std::endl;
}