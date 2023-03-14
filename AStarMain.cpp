//--------------------------------------------------------------------------------------------
//NOTE : make sure to include the correct constants ! It will define all the game parameters
#include "FourRobotsRegularMaze.h"
//--------------------------------------------------------------------------------------------
#include "Constants.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "AStarNode.h"
#include "AStarNode.cpp"
#include <cmath>
#include <chrono>

int main()
{
    std::cout << "Hello Gorane !" << std::endl;
    vector<string> teamNames = {"E","R","G","H"};

    int posH = 17;

    char simpleMaze[game::NB_OF_MAZE_SQUARES];
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++){
        simpleMaze[i] = game::MAZE[i];

        //add a coin on all squares except those on which a robot lies
        if (abs(posH%game::MAZE_WIDTH - i%game::MAZE_WIDTH) + abs(posH/game::MAZE_WIDTH - i/game::MAZE_WIDTH) <= 4 && abs(posH%game::MAZE_WIDTH - i%game::MAZE_WIDTH) + abs(posH/game::MAZE_WIDTH - i/game::MAZE_WIDTH) > 0)
             simpleMaze[i] += constants::COIN_MASK;
    }
        
    int timeUntilGasClosing = game::GAS_CLOSING_INTERVAL;

    struct Robot E1 = {0, 0, false};
    struct Robot E2 = {6, 0, false};
    struct Robot G1 = {12, 0, false};
    struct Robot G2 = {posH, 0, true};

    Robot enemyRobots[game::NB_OF_ROBOTS_PER_TEAM];
    Robot goraneRobots[game::NB_OF_ROBOTS_PER_TEAM];


    enemyRobots[constants::ENEMY1_INDEX] = E1;
    enemyRobots[constants::ENEMY2_INDEX] = E2;
    goraneRobots[constants::GORANE1_INDEX] = G1;
    goraneRobots[constants::GORANE2_INDEX] = G2;

    Team enemyTeam(enemyRobots);
    Team goraneTeam(goraneRobots);

    Team teams[game::NB_OF_TEAMS];

    teams[constants::GORANE_TEAM] = goraneTeam;
    teams[constants::ENEMY_TEAM] = enemyTeam;

    //id of team playing first
    bool bTeamId = constants::GORANE_TEAM;

    //init node
    Node myNode = Node(simpleMaze, teams, bTeamId, timeUntilGasClosing);

    //give turn to H
    myNode.teams[1].robotTakingItsTurn = true;
    
    char indexToAStar;
    int costToAStar;
    AStarNode aStarNode = AStarNode(myNode, nullptr, 0, true);
    /*
    AStarNode aStarNode = AStarNode(myNode, nullptr, 0, false);

    
    aStarNode.modifyToMazeWithOneCoin();
    int costToLonelyCoin;
    int indexToLonelyCoin;

    std::tie(costToLonelyCoin, indexToLonelyCoin) = aStarNode.runAStar();
    */

    aStarNode.printNode();

    //aStarNode.getDistanceBetweenAllCoinClusters();

    while (!aStarNode.Node::isTerminal())
    {   

        std:cout << "Turn to " << teamNames[(int) aStarNode.teamTakingItsTurn*2 + (int) aStarNode.teams[aStarNode.teamTakingItsTurn].robotTakingItsTurn] << " robot." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute minimax value & index to minimax
        std::tie(costToAStar, indexToAStar) = aStarNode.runAStar();
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        std::cout << "Robot " << teamNames[aStarNode.teamTakingItsTurn] << " should move to "<< aStarNode.getLocationIncrement(indexToAStar) << "." << std::endl;
        std::cout << "Computing time was " << elapsed.count() << " microseconds" << endl;

        //update node
        aStarNode.configureChild(indexToAStar);

        //print new node
        aStarNode.printNode();
    }

    std::cout << "Game Over" << endl;
    //std::cout << aStarNode.getNodeValue() << endl;

}
