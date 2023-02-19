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
}
//returns the best child node from current node based on MCTS algorithm
tuple<double, int> MCTSNode::runMCTS(int iterations){

}
//searches the tree using MCTS algorithm
void MCTSNode::searchTree(){

}
//selects one child node from current node based on UCB
void MCTSNode::selectFromChildren(){

}
//expands nodes from the current node
void MCTSNode::generateChildren(){

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