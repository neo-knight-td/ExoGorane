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
        tuple<double, char, int, int> runMinimax();
        void selectFromChildren(std::function<bool(double,double)> comp1, std::function<bool(int,int)> comp2, double *minimax, char *indexToMinimax, int *pDepthLastEvalUp, int *pDepthLastEvalDown);
        MinimaxNode generateChild(char childIndex);
        double getDepthRegressionFactor(int paramDepth);
};

#endif