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
#include "MinimaxNode.h"
#include "MinimaxNode.cpp"
#include <cmath>
#include <chrono>
#include <experimental/random>

int main()
{
    std::cout << "Hello Gorane !" << std::endl;
    vector<string> teamNames = {"E","R","G","H"};

    char simpleMaze[game::NB_OF_MAZE_SQUARES]; // Create tab of size Nb_of_maze defined in game (namespace)
    
    
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++){
        simpleMaze[i] = game::MAZE[i]; //Copy initial maze defined in game

        //add a coin on all squares except those on which a robot lies
        if (i != game::ENEMY1_DEFAULT_LOCATION && i != game::ENEMY2_DEFAULT_LOCATION && i != game::GORANE1_DEFAULT_LOCATION && i != game::GORANE2_DEFAULT_LOCATION)
             simpleMaze[i] += constants::COIN_MASK;
    }
        
    int timeUntilGasClosing = game::GAS_CLOSING_INTERVAL;

    //Initie les Teams
    struct Robot E1 = {game::ENEMY1_DEFAULT_LOCATION, 0, false};
    struct Robot E2 = {game::ENEMY2_DEFAULT_LOCATION, 0, true};
    struct Robot G1 = {game::GORANE1_DEFAULT_LOCATION, 0, false};
    struct Robot G2 = {game::GORANE2_DEFAULT_LOCATION, 0, true};

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

    //Our time to play ? True or False
    bool bTeamId = constants::ENEMY_TEAM;

    //init node
    Node myNode = Node(simpleMaze, teams, bTeamId, timeUntilGasClosing);

    //init minimax node
    int valueOfMinimax;
    char indexToMinimax;
    //current depth
    int depth = 0;
    //max depth
    int maxDepth = 3;
    
    MinimaxNode minimaxNode = MinimaxNode(myNode, depth, maxDepth);

    minimaxNode.printNode();

    while (!minimaxNode.isTerminal())
    {
        if (minimaxNode.isCombatOngoing){
            //random kill one of the robots in combat
            indexToMinimax = std::experimental::randint(0, 1);
        }
        
        else {
            std:cout << "Turn to " << teamNames[(int) minimaxNode.teamTakingItsTurn*2 + (int) minimaxNode.teams[minimaxNode.teamTakingItsTurn].robotTakingItsTurn] << " robot." << endl;
            auto begin = std::chrono::high_resolution_clock::now();

            //compute minimax value & index to minimax
            std::tie(valueOfMinimax, indexToMinimax, std::ignore, std::ignore) = minimaxNode.runMinimax();
            
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

            std::cout << "Robot " << teamNames[minimaxNode.teamTakingItsTurn] << " should move to "<< minimaxNode.getLocationIncrement(indexToMinimax) << "." << std::endl;
            std::cout << "Computing time was " << elapsed.count() << " microseconds" << endl;
        }

        //update node
        minimaxNode.configureChild(indexToMinimax);

        //print new node
        minimaxNode.printNode();
    }

    std::cout << "Game Over" << endl;
    std::cout << minimaxNode.getNodeValue() << endl;
    
}