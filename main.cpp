#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "Minimax.cpp"

int main()
{
    std::cout << "Hello Gorane !" << std::endl;

    vector<vector <int>> mazeVector = {{1,3},{0,2},{1,5},{0,4},{3,5},{2,4}};
    list<int> coinsVector = {2};
    Robot robotG = Robot(0, 0, true, true);
    Robot robotE = Robot(5, 0, true, false);
    vector<Robot> robotVector = {robotG, robotE};
    vector<string> teamNames = {"Goranes", "Enemy"};
    int teamId = 0;

    // Following simplified maze (3 x 2) is setup with 2 robots:

    // *****
    // *G  *
    // *   *
    // * | *
    // *   *
    // *$ E*
    // *****

    //  G is the Gorane robot
    //  E is the Enemy
    //  $ is a coin

    //  G is only 1 square away from $ whereas E is 2 squares away from $
    //  G should win by moving to square index 3 and capturing coin $

    GameState simpleGameState = GameState(mazeVector, coinsVector, robotVector, 0, teamId);
    Minimax minimaxStrategy;

    int valueOfMinimax;
    int moveToMinimax;

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