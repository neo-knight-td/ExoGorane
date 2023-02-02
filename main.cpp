#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "Minimax.cpp"
#include <cmath>
#include <chrono>

int main()
{
    std::cout << "Hello Gorane !" << std::endl;

    //  Example 1 : simplified maze (3 x 2) with 2 robots and 1 coin:

    //  *****
    //  *G  *
    //  *   *
    //  * | *
    //  *   *
    //  *$ E*
    //  *****

    //  G is the Gorane robot
    //  E is the Enemy
    //  $ is a coin

    //  G is only 1 square away from $ whereas E is 2 squares away from $
    //  G should win by moving to square index 3 and capturing coin $

    //  Corresponding code :
    /*
    vector<vector <int>> mazeVector = {{1,3},{0,2},{1,5},{0,4},{3,5},{2,4}};
    int mazeHDim = 2;
    list<int> coinsVector = {2};
    Robot robotG = Robot(0, 0, true, true);
    Robot robotE = Robot(5, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 11;
    */

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

    //  ***********
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

    //Example 5 : 5 x 5 maze with

    vector<vector <int>> mazeVector
    {
        {5,1},{0,2},{1,7,3},{2,8},{9},//column 1 of maze
        {10,0,6},{11,7},{6,12,8,2},{7,13,3},{14,4},//column 2 of maze
        {15,11,5},{10,12,6},{11,17,13,7},{12,18,8},{19,9},//column 3 of maze
        {20,10},{21,17},{16,18,12},{19,17,13},{18,14},//column 4 of maze
        {15},{22,16},{21,23},{22,24},{23}//column 5 of maze
    };
    int mazeHDim = 5;
    list<int> coinsVector = {4,9,12,20,15};
    Robot robotG = Robot(0, 0, true, true);
    Robot robotE = Robot(24, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    int maxDepth = 11;
    int gasClosingInterval = 2;
    
    int valueOfMinimax;
    int moveToMinimax;

    //id of team playing first
    int teamId = 0;

    //time at start of the game
    int startTime = 0;
    vector<string> teamNames = {"Goranes", "Enemy"};

    GameState simpleGameState = GameState(mazeVector, mazeHDim, coinsVector, robotVector, 0, teamId, false, startTime, gasClosingInterval);
    Minimax minimaxStrategy(maxDepth);

    simpleGameState.printGameState();

    while (!simpleGameState.isTerminalState())
    {
        std:cout << "Turn to " << teamNames[teamId] << " team." << endl;
        auto begin = std::chrono::high_resolution_clock::now();

        //compute minimax value & move to minimax
        std::tie(valueOfMinimax, moveToMinimax, std::ignore, std::ignore) = minimaxStrategy.getValueOfNextState(simpleGameState, teamId);

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

        std::cout << "Robot " << teamNames[teamId] << " should move to "<< moveToMinimax << "." << std::endl;
        printf("Time measured: %.3f microseconds.\n", elapsed.count()* 1e-3);

        //update game state
        // > robot location
        simpleGameState.robots[teamId].location = moveToMinimax;
        // > coins
        simpleGameState.updateCoins(&simpleGameState.coinsOnGround, &simpleGameState.robots[teamId]);
        // > depth
        simpleGameState.depthOfState++;
        // > time
        simpleGameState.updateTime(&simpleGameState.depthOfState,&simpleGameState.timeSinceStartOfGame);
        // > maze
        simpleGameState.updateMaze(&simpleGameState.mazeSquares, simpleGameState.timeSinceStartOfGame);
        // > robot life
        simpleGameState.updateRobotsLife(&simpleGameState.mazeSquares, &simpleGameState.robots);
        // > team id (only if robot is alive in team taking next turn)
        if (simpleGameState.robots[(teamId+1)%2].isAlive)
            teamId = (teamId+1)%2;
        simpleGameState.teamId = teamId;

        //print game state
        simpleGameState.printGameState();
    }

    std::cout << "Game Over" << endl;
}