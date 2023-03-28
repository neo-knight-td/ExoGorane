#ifndef MCTS_NODE_H
#define MCTS_NODE_H

#include "Node.h"

class MCTSNode: public Node {
    public :
        double value = 0;
        int visits = 0;
        MCTSNode *pParentNode = nullptr;
        MCTSNode *pChildNodes[BRANCHING_FACTOR];

    public :
        //constructor for MCTSNode
        MCTSNode(const Node &rhs, MCTSNode* pParamParentNode);
        //TODO : create a destructor !
        //~MCTSNode();
        //returns the best child node from current node based on MCTS algorithm
        tuple<double, char> runMCTS(int iterations, bool topOfTreeTeam);
        //searches the tree using MCTS algorithm
        void search();
        //selects one leaf node from current node based on UCB and return pointer to it (with UCB value)
        tuple<MCTSNode*, double> selectFromLeaves(bool topOfTreeTeam);
        //expands node from the current node, simulate a child and return values obtained
        void generateChild(char childIndex);
        //simulate a game until bottom of the tree and record outcome
        double simulate();
        //update values & visits in node
        void update(double paramValue);
        //backpropagate update towards parent
        void backpropagate(double paramValue);
        //checks if node is a leaf node
        bool isLeafNode();
        //get UCB
        double getUCB(bool topOfTreeTeam);
};

#endif