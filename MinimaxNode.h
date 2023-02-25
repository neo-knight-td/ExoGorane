#include "Node.h"

#ifndef MINIMAX_NODE_H
#define MINIMAX_NODE_H

class MinimaxNode: public Node {
    public :
        int depth;
        int maxDepth;
        //int depthLastEvalFuncChange;
        int depthLastEvalUp;
        int depthLastEvalDown;
        //MinimaxNode *pChildNodes[constants::BRANCHING_FACTOR];

    public :
        MinimaxNode(char *paramMaze, Team *paramTeams, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing, int paramDepth, int paramMaxDepth);
        tuple<double, int, int, int> runMinimax();
        void selectFromChildren(std::function<bool(double,double)> comp1, std::function<bool(int,int)> comp2, double *minimax, int *moveToMinimax, int *pDepthLastEvalUp, int *pDepthLastEvalDown);
        MinimaxNode generateMinimaxNode(int locationIncrement);
        double getDepthRegressionFactor(int paramDepth);
};

#endif