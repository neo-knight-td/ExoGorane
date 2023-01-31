#include "GameState.cpp"
#include <tuple>

#ifndef MINIMAX_H
#define MINIMAX_H

using namespace std;

class Minimax
{   protected :
        //maximum depth level that will be explored in the tree from the current game state
        int const MAX_DEPTH = 11;
    public :
        //computes minimax value from current game state. getValueOfNextState also returns
        //the move required to reach Minimax and the depth to next state in which the utility goes up
        tuple<int, int, int, int> getValueOfNextState(GameState gameState, int topOfTreeTeamId);
};

#endif
