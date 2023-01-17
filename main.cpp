#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "Minimax.cpp"
#include <cmath>

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
    
        vector<vector <int>> mazeVector = {{1,3},{0,2},{1,5},{0,4},{3,5},{2,4}};
        int mazeHDim = 2;
        list<int> coinsVector = {2};
        Robot robotG = Robot(0, 0, true, true);
        Robot robotE = Robot(5, 0, true, false);
        vector<Robot> robotVector = {robotG, robotE};
    
    //  Example 2 : bigger maze (5 x 5) with 2 robots and 3 coins:

    //  ***********
    //  *      G  *
    //  *  -   - -*
    //  * |   |E  *
    //  *         *
    //  *       | *
    //  *         *
    //  *       | *
    //  *- - -    *
    //  *$     $| *
    //  ***********

    // G only way to win is to pursue coin closest to E first ($ in square 19)
    
    // Corresponding code :
    /*
    vector<vector <int>> mazeVector
    {
        {5,1},{0,2},{1,7,3},{2,8},{9},//column 1 of maze
        {10,0},{11,7},{6,12,8,2},{7,13,3},{4,14},//column 2 of maze
        {15,11,5},{10,12,6},{11,17,13,7},{12,18,8},{9,19},//column 3 of maze
        {20,10},{21,17},{16,18,12},{17,19,13},{18,14},//column 4 of maze
        {15},{22,16},{21,23},{22,24},{23}//column 5 of maze
    };
    int mazeHDim = 5;
    list<int> coinsVector = {20,4,19};
    Robot robotG = Robot(0, 0, true, true);
    Robot robotE = Robot(24, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    */
    
    int valueOfMinimax;
    int moveToMinimax;
    int teamId = 0;
    vector<string> teamNames = {"Goranes", "Enemy"};

    GameState simpleGameState = GameState(mazeVector, mazeHDim, coinsVector, robotVector, 0, teamId);
    Minimax minimaxStrategy;

    simpleGameState.printGameState();

    while (!simpleGameState.isTerminalState())
    {
        std:cout << "Turn to " << teamNames[teamId] << " team." << endl;

        //compute minimax & move to minimax
        std::tie(valueOfMinimax, moveToMinimax) = minimaxStrategy.getValueOfNextState(simpleGameState, teamId);

        std::cout << "Robot " << teamNames[teamId] << " should move to "<< moveToMinimax << std::endl; 

        //update game state
        // > robot location
        simpleGameState.robots[teamId].location = moveToMinimax;
        // > coins
        simpleGameState.updateCoins(&simpleGameState.coinsOnGround, &simpleGameState.robots[teamId]);
        // > team id
        teamId = (teamId+1)%2;
        simpleGameState.teamId = teamId;

        //print game state
        simpleGameState.printGameState();
    }

    std::cout << "Game Over" << endl;
}