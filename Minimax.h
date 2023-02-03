#include "GameState.cpp"
#include <tuple>

#ifndef MINIMAX_H
#define MINIMAX_H

using namespace std;

class Minimax
{   protected :
        //maximum depth level that will be explored in the tree from the current game state.
        int maxDepth;
    public :
        //getValueOfNextState is a recursive function that will explore the tree of states and return the maximum utility
        //value reachable from the current game state. It will also provide the move required to reach that value, the depth
        //at which that value appears in the tree & the depth to the nearest state in which utility increases
        tuple<int, int, int, int> getValueOfNextState(GameState gameState, int topOfTreeTeamId);

        Minimax(int paramMaxDepth);
};

#endif
