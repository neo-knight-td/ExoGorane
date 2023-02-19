#include "GameState.cpp"
#include <tuple>

#ifndef MINIMAX_H
#define MINIMAX_H

using namespace std;

class Minimax
{   protected :
        //maximum depth level that will be explored in the tree from the current game state.
        int maxDepth;
        //dummy depth is the value assigned to a depth when it should not be taken into account
        int const DUMMY_DEPTH = -1;
    public :
        //getValueOfNextState is a recursive function that will explore the tree of states and return the maximum utility
        //value reachable from the current game state. It will also provide the move required to reach that value, the depth
        //at which that value appears in the tree, the depth at which utility increases & the depth to the death of the robot
        tuple<int, int, int, int, int> getValueOfNextState(GameState gameState, int topOfTreeTeamId);

        void chooseFromSuccessors(GameState gameState, int topOfTreeTeamId, std::function<bool(int,int)> comp1, std::function<bool(int,int)> comp2, int *minimax,
            int *moveToMinimax, int *depthToMinimax, int *depthToFirstUtilGoesUp, int *depthToDeath);

        Minimax(int paramMaxDepth);
};

#endif
