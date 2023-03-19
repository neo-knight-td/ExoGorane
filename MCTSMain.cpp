//--------------------------------------------------------------------------------------------
//NOTE : make sure to include the correct constants ! It will define all the game parameters
#include "FourRobotsRegularMaze.h"
//--------------------------------------------------------------------------------------------
#include "Constants.h"
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
    vector<string> teamNames = {"E","R","G","H"};

    char simpleMaze[game::NB_OF_MAZE_SQUARES];
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++){
        simpleMaze[i] = game::MAZE[i];

        //add a coin on all squares except those on which a robot lies
        if (i != game::ENEMY1_DEFAULT_LOCATION && i != game::ENEMY2_DEFAULT_LOCATION && i != game::GORANE1_DEFAULT_LOCATION && i != game::GORANE2_DEFAULT_LOCATION)
             simpleMaze[i] += constants::COIN_MASK;
    }
    int timeUntilGasClosing = game::GAS_CLOSING_INTERVAL;

    struct Robot G1 = {game::GORANE1_DEFAULT_LOCATION, 0, true};
    struct Robot G2 = {game::GORANE2_DEFAULT_LOCATION, 0, true};
    struct Robot E1 = {game::ENEMY1_DEFAULT_LOCATION, 0, true};
    struct Robot E2 = {game::ENEMY2_DEFAULT_LOCATION, 0, true};

    Robot goraneRobots[game::NB_OF_ROBOTS_PER_TEAM];
    Robot enemyRobots[game::NB_OF_ROBOTS_PER_TEAM];

    goraneRobots[constants::GORANE1_INDEX] = G1;
    goraneRobots[constants::GORANE2_INDEX] = G2;
    enemyRobots[constants::ENEMY1_INDEX] = E1;
    enemyRobots[constants::ENEMY2_INDEX] = E2;

    Team goraneTeam(goraneRobots);
    Team enemyTeam(enemyRobots);

    Team teams[game::NB_OF_TEAMS];

    teams[constants::GORANE_TEAM] = goraneTeam;
    teams[constants::ENEMY_TEAM] = enemyTeam;

    double valueOfMCTS;
    char selectedChildIndex;

    //id of team playing first
    bool bTeamId = constants::ENEMY_TEAM;

    //init node
    Node myNode = Node(simpleMaze, teams, bTeamId, timeUntilGasClosing);

    //init MCTS Node
    int iteration = 10000;
    //init game state
    MCTSNode mctsNode = MCTSNode(myNode, nullptr);
    
    mctsNode.printNode();

    while (!mctsNode.isTerminal())
    {
        if (mctsNode.isCombatOngoing){
            //random kill one of the robots in combat
            selectedChildIndex = std::experimental::randint(0, 1);
        }

        else {
            std:cout << "Turn to " << teamNames[(int) mctsNode.teamTakingItsTurn*2 + (int) mctsNode.teams[mctsNode.teamTakingItsTurn].robotTakingItsTurn] << " robot." << endl;
            auto begin = std::chrono::high_resolution_clock::now();

            //compute
            std::tie(valueOfMCTS, selectedChildIndex) = mctsNode.runMCTS(iteration, mctsNode.teamTakingItsTurn);
            
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            std::cout << "Robot " << teamNames[mctsNode.teamTakingItsTurn] << " should move to "<< mctsNode.getLocationIncrement(selectedChildIndex) << "." << std::endl;
            std::cout << "Computing time was " << elapsed.count() << " microseconds" << endl;
        }
        //update node
        mctsNode.configureChild(selectedChildIndex);

        //print new node
        mctsNode.printNode();
    }

    std::cout << "Game Over" << endl;
    std::cout << "Result is " << mctsNode.getNodeValue() << endl;

}