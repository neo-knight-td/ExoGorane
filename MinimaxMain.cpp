//--------------------------------------------------------------------------------------------
//NOTE : make sure to include the correct constants ! It will define all the game parameters
#include "FourRobotsLargeMaze.h"
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

int main()
{
    std::cout << "Hello Gorane !" << std::endl;

    char simpleMaze[game::NB_OF_MAZE_SQUARES];
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++)
        simpleMaze[i] = game::MAZE[i];
    int timeUntilGasClosing = game::GAS_CLOSING_INTERVAL;
    int maxDepth = 11;

    /*
    //with 1 robot per team
    struct Robot simpleRobotG = {game::GORANE_DEFAULT_LOCATION, 0, true};
    struct Robot simpleRobotE = {game::ENEMY_DEFAULT_LOCATION, 0, true};
    Robot simpleRobots[game::NB_OF_ROBOTS];
    simpleRobots[constants::GORANE_TEAM] = simpleRobotG;
    simpleRobots[constants::ENEMY_TEAM] = simpleRobotE;
    */

    //with 2 robots per team
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

    //teams[constants::ENEMY_TEAM] = enemyTeam;
    //teams[constants::GORANE_TEAM] = goraneTeam;
    
    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    bool bTeamId = constants::ENEMY_TEAM;

    //time at start of the game
    int startTime = 0;

    //current depth
    int depth = 0;
    vector<string> teamNames = {"Enemy", "Goranes"};

    //init game state
    MinimaxNode minimaxNode = MinimaxNode(simpleMaze, teams, bTeamId, timeUntilGasClosing, depth, maxDepth);

    minimaxNode.printNode();

    while (!minimaxNode.isTerminal())
    {
        std:cout << "Turn to " << teamNames[minimaxNode.teamTakingItsTurn] << " team." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute minimax value & move to minimax
        std::tie(valueOfMinimax, moveToMinimax, std::ignore, std::ignore) = minimaxNode.runMinimax();
        
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        std::cout << "Robot " << teamNames[minimaxNode.teamTakingItsTurn] << " should move to "<< moveToMinimax << "." << std::endl;
        std::cout << "Computing time was " << elapsed.count() << " microseconds" << endl;

        //update node
        minimaxNode.configureChild(moveToMinimax);

        //print new node
        minimaxNode.printNode();
    }

    std::cout << "Game Over" << endl;
    
}