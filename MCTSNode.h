#include "Node.h"

#ifndef MCTS_NODE_H
#define MCTS_NODE_H

class MCTSNode: public Node {
    public :
        int value;
        int visits;
        MCTSNode *pChildNodes[constants::BRANCHING_FACTOR];

    public :
        //constructor for MCTSNode
        MCTSNode(char *paramMaze, Robot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing);
        //TODO : create a destructor !
        ~MCTSNode();
        //returns the best child node from current node based on MCTS algorithm
        tuple<double, int> runMCTS(int iterations);
        //searches the tree using MCTS algorithm
        void search();
        //selects one child node from current node based on UCB
        void selectFromChildren();
        //expands node from the current node
        void generateDescendance();
        //simulate a game until bottom of the tree and record outcome
        bool simulate();
        //generate an MCTS node
        MCTSNode generateMCTSNode(int locationIncrement);
};

#endif