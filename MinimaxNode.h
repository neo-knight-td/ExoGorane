#include "Constants.h"
#include "Node.h"

#ifndef MINIMAX_NODE_H
#define MINIMAX_NODE_H

class MinimaxNode: public Node {
    public :
        int depth;
        int maxDepth;
        //MinimaxNode *pChildNodes[constants::BRANCHING_FACTOR];

    public :
        MinimaxNode(char *paramMaze, Robot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing, int paramDepth, int paramMaxDepth);
        tuple<double, int, int> getMinimax();
        void selectFromChildren(std::function<bool(int,int)> comp1, std::function<bool(int,int)> comp2, double *minimax, int *moveToMinimax, int *depthToMinimax);
        void generateChildren();
        MinimaxNode generateMinimaxNode(int locationIncrement);
};

#endif