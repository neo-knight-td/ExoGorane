#include <iostream>
#include <algorithm>
#include <experimental/random>
#include "MCTSNode.h"
#include "Node.h"
#include "Node.cpp"

//constructor for MCTSNode
MCTSNode::MCTSNode(char *paramMaze, Robot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing) : Node(paramMaze, paramRobots, paramTeamTakingItsTurn, paramTimeUntilGasClosing){
    this->value = 0;
    this->visits = 0;
    //init all pointers to null
    for (int i=0; i < sizeof(pChildNodes)/sizeof(*pChildNodes); i++)
        this->pChildNodes[i] = nullptr;
}

//destructor for MCTS
MCTSNode::~MCTSNode(){
    //call destructor of child nodes
    char childIndex = 0;
    for (int i = 0; i < this->getDescendanceSize(); i++){
        //update childIndex to next valid child Index
        getLocationIncrement(&childIndex);
        delete this->pChildNodes[childIndex];
    }
}

//returns the best child node from current node based on MCTS algorithm
tuple<double, int> MCTSNode::runMCTS(int iterations){

}
//searches the tree using MCTS algorithm
void MCTSNode::search(){

}
//selects one child node from current node based on UCB & search in child with best UCB
void MCTSNode::selectFromChildren(){
    double maxUCB1 = -1;
    MCTSNode *pSelectedChild = nullptr;
    char childIndex = 0;
    for (int i=0; i < this->getDescendanceSize(); i++){
        //update childIndex to next valid child Index
        getLocationIncrement(&childIndex);
        MCTSNode *pChildNode = this->pChildNodes[childIndex];
        //TODO : check/tune formula
        double UCB1 = (double) pChildNode->value / pChildNode->visits + sqrt(2 * log(visits) / pChildNode->visits);

        if (UCB1 > maxUCB1){
            pSelectedChild = pChildNode;
            maxUCB1 = UCB1;
        }
    }

    pSelectedChild->search();
    
}
//expands nodes from the current node
void MCTSNode::generateDescendance(){

    char childIndex = 0;
    char numberOfChildren = getDescendanceSize();
    for (char i = 0; i < numberOfChildren; i++){
        
        int locationIncrement = getLocationIncrement(&childIndex);
        //create a new node !
        this->pChildNodes[childIndex] = new MCTSNode(this->maze, this->robots, this->teamTakingItsTurn, this->timeUntilGasClosing);
        //configure it
        this->pChildNodes[childIndex]->configureChild(locationIncrement);
    }

}
//simulate a game until bottom of the tree and record outcome
bool MCTSNode::simulate(){
    //copy current node into simulation node
    MCTSNode simulationNode(this->maze, this->robots, this->teamTakingItsTurn, this->timeUntilGasClosing);
    while (!simulationNode.isTerminal()){

        //select random child index
        //TODO : insert constants values as paramters
        char randomChildIndex = std::experimental::randint(1, constants::BRANCHING_FACTOR - 1);
        int locationIncrement = simulationNode.getLocationIncrement(&randomChildIndex);
        
        //configure simulation node
        simulationNode.configureChild(locationIncrement);

        //NOTE : debug purpose only
        //simulationNode.printNode();
    }

    return simulationNode.getNodeValue();
}