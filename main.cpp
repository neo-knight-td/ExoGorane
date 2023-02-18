#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "MinimaxNode.h"
#include "MinimaxNode.cpp"
#include "Constants.h"
#include <cmath>
#include <chrono>

int main()
{
    std::cout << "Hello Gorane !" << std::endl;

    //  Example 1 : simplified maze (3 x 3) with 2 robots and 1 coin:


    //  G is the Gorane robot
    //  E is the Enemy
    //  $ is a coin


    // New Implementation code :
    char simpleMaze[9] =
    {
        {constants::COIN_MASK +  constants::RIGHT_MASK + constants::DOWN_MASK},
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
    int maxDepth = 10;
    int timeUntilGasClosing = constants::GAS_CLOSING_INTERVAL;

    //  Example 2 : long maze (5x2) with 2 robots and 1 coin


    //  G should go down
    //  Corresponding code :
    /*
    vector<vector <int>> mazeVector
    {
        {1},{0,2},{1,3},{2,4},{3},//column 1 of maze
        {6},{5,7},{6,8},{7,9},{8},//column 2 of maze
    };
    int mazeHDim = 2;
    //list<int> coinsVector = {20,4,19};
    list<int> coinsVector = {4};
    Robot robotG = Robot(1, 0, true, true);
    Robot robotE = Robot(7, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 11;
    */

    //  Example 3 : bigger maze (5 x 5) with 2 robots and 3 coins:

    //  ***********timeUntilGasClosing
    //  *G     $  *
    //  *  -   - -*
    //  * |   |   *
    //  *         *
    //  *       | *
    //  *         *
    //  *       | *
    //  *- - -    *
    //  *    $ $|E*
    //  ***********

    // G only way to win is to pursue coin closest to E first ($ in square 19)
    
    // Corresponding code :
    /*
    vector<vector <int>> mazeVector
    {
        {5,1},{0,2},{1,7,3},{2,8},{9},//column 1 of maze
        {10,0},{11,7},{6,12,8,2},{7,13,3},{14,4},//column 2 of maze
        {15,11,5},{10,12,6},{11,17,13,7},{12,18,8},{19,9},//column 3 of maze
        {20,10},{21,17},{16,18,12},{19,17,13},{18,14},//column 4 of maze
        {15},{22,16},{21,23},{22,24},{23}//column 5 of maze
    };
    int mazeHDim = 5;
    list<int> coinsVector = {15,14,19};
    Robot robotG = Robot(0, 0, true, true);
    Robot robotE = Robot(24, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 11;
    */

    // Example 4 : simple maze (3 x 2) with 2 robots and 2 coins:

    //  *****
    //  *$ E*
    //  *   *
    //  *G| *
    //  *   *
    //  *$  *
    //  *****

    // If utility function only counts the number of coins in possession of G
    // and max depth equal 3, then G has no preference going up or down (Minimax is equal to 1 either way).
    // For G to chose to go up, max depth should be increased to 5. This would require additionnal computing time
    // but going up would be rewarded by 2 whereas going down by 1 only.

    // A utility function that counts coins of G minus coins of E allows chosing to move up without an
    // increase of depth. Indeed, if G moves up then he prevents E from eating the dot and would be rewarded by 1.
    // However, if G choses to go down he would be rewarded 0 because both G and E did eat a dot (1-1 = 0)
    
    // Corresponding code :
    /*
    vector<vector <int>> mazeVector = {{1,3},{2,0},{1,5},{0,4},{3,5},{2,4}};
    int mazeHDim = 2;
    list<int> coinsVector = {0,2};
    Robot robotG = Robot(1, 0, true, true);
    Robot robotE = Robot(3, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 3;
    */

    //Example simpleGameState5 : 5 x 5 maze with 5 coins, 2 robots and the gas closing after 4 moves

    //  ***********
    //  *G     $  *
    //  *  -   - -*
    //  * |   |   *
    //  *         *
    //  *    $  | *
    //  *         *
    //  *       | *
    //  *- - -    *
    //  *$ $    |E*
    //  ***********

    //G has two options once reaching square 10. Either pursue the 2 coins on
    //the right or grab the coin in the middle of the maze (both options lead to minimax of 1) Getting down is the best option to chose as it allows
    //staying alive longer (and maybe see coins that were further away than the max depth when in square 10).

    // Corresponding code :

    /*
    vector<vector <int>> mazeVector
    {
        {5,1},{0,2},{1,7,3},{2,8},{9},//column 1 of maze
        {0,10},{11,7},{6,12,8,2},{7,13,3},{14,4},//column 2 of maze
        {15,11,5},{10,12,6},{11,17,13,7},{12,18,8},{19,9},//column 3 of maze
        {20,10},{21,17},{16,18,12},{19,17,13},{18,14},//column 4 of maze
        {15},{22,16},{21,23},{22,24},{23}//column 5 of maze
    };
    int mazeHDim = 5;
    list<int> coinsVector = {4,9,20,15,12};
    Robot robotG = Robot(0, 0, true, true);
    Robot robotE = Robot(24, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 11;
    int gasClosingInterval = 4;
    */
    
    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    bool bTeamId = constants::GORANE_TEAM;

    //time at start of the game
    int startTime = 0;

    //current depth
    int depth = 0;
    vector<string> teamNames = {"Enemy", "Goranes"};

    //init game state
    MinimaxNode minimaxNode = MinimaxNode(simpleMaze, simpleRobots, bTeamId, timeUntilGasClosing, depth, maxDepth);

    minimaxNode.printNode();

    while (!minimaxNode.isTerminal())
    {
        std:cout << "Turn to " << teamNames[minimaxNode.teamTakingItsTurn] << " team." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute minimax value & move to minimax
        std::tie(valueOfMinimax, moveToMinimax, std::ignore) = minimaxNode.getMinimax();
        
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

    std::cout << "Game Over" << endl;
}