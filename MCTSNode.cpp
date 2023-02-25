#include <iostream>
#include <algorithm>
#include <experimental/random>
#include "MCTSNode.h"
#include "Node.h"
#include "Node.cpp"

//constructor for MCTSNode
MCTSNode::MCTSNode(char *paramMaze,  Team *paramTeams, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing, MCTSNode* pParamParentNode) : Node(paramMaze, paramTeams, paramTeamTakingItsTurn, paramTimeUntilGasClosing){
    //init all pointers to null
    for (int i=0; i < sizeof(pChildNodes)/sizeof(*pChildNodes); i++)
        this->pChildNodes[i] = nullptr;
    //init parent pointer to parent
    this->pParentNode = pParamParentNode;
}

//destructor for MCTS
MCTSNode::~MCTSNode(){
    //call destructor of child nodes
    char childIndex = -1;
    for (int i = 0; i < this->getDescendanceSize(); i++){
        //update childIndex to next valid child Index
        getLocationIncrement(&childIndex);
        delete this->pChildNodes[childIndex];
    }
}

//returns the best child node from current node based on MCTS algorithm
tuple<double, int> MCTSNode::runMCTS(int iterations, bool topOfTreeTeam){

    char childIndex = -1;

    //perform for a number of iterations
    for (int i = 0; i < iterations; i++){
        //select
        MCTSNode *pSelectedLeafNode;

        //if first iteration, select root node. Otherwise select among leaves.
        if (i == 0)
            pSelectedLeafNode = this;
        else
            std:tie(pSelectedLeafNode, std::ignore) = selectFromLeaves(topOfTreeTeam);
        
        
        childIndex = -1;
        for (int j = 0; j < pSelectedLeafNode->getDescendanceSize(); j++){
            //expand (generate child)
            pSelectedLeafNode->generateChild(&childIndex);
            //simulate (access child you just generated, simulate and return outcome)
            int result = pSelectedLeafNode->pChildNodes[childIndex]->simulate();
            //backpropagate towards parents
            pSelectedLeafNode->pChildNodes[childIndex]->backpropagate(result);
        }
    }


    //TODO : selectFromChildren --> select one child out of children (the one with max ucb)
    int selectedLocationIncrement = -1;
    double maxUCB = -1;

    childIndex = -1;
    for (int i = 0; i < getDescendanceSize(); i++){
        //update child index & record location increment
        int locationIncrement = getLocationIncrement(&childIndex);
        //record UCB in child node
        double UCB = this->pChildNodes[childIndex]->getUCB(topOfTreeTeam);
        //if UCB is bigger, save it
        if (UCB > maxUCB){
            maxUCB = UCB;
            selectedLocationIncrement = locationIncrement;
        }
    }

    return {maxUCB,selectedLocationIncrement};
}

//searches the tree using MCTS algorithm
void MCTSNode::search(){

}


//selects one leaf node from current node based on UCB and return pointer to it (with UCB value)
tuple<MCTSNode*, double> MCTSNode::selectFromLeaves(bool topOfTreeTeam){

    //if node is leaf
    if(isLeafNode()){
        return {this,this->getUCB(topOfTreeTeam)};
    }
    else{//if it's not a leaf node, look in child nodes
        char childIndex = -1;
        double maxUCB = -1;
        MCTSNode *pSelectedLeafNode = nullptr;

        for (int i=0; i < this->getDescendanceSize(); i++){
            double UCB;
            MCTSNode *pLeafNode;

            //update childIndex to next valid child Index
            getLocationIncrement(&childIndex);
            //recover child node address
            MCTSNode *pChildNode = this->pChildNodes[childIndex];
            //perform selection from child node then return best leaf and associated UCB
            std::tie(pLeafNode, UCB) = pChildNode->selectFromLeaves(topOfTreeTeam);
            //if better UCB is found update the values to maximize
            if (UCB > maxUCB){
                pSelectedLeafNode = pLeafNode;
                maxUCB = UCB;
            }
        }
        return {pSelectedLeafNode, maxUCB};
    }
}

//expands child at specified index
void MCTSNode::generateChild(char *pChildIndex){
    //retrieve location increment but do not update child index
    int locationIncrement = getLocationIncrement(pChildIndex);
    //create a new node
    this->pChildNodes[*pChildIndex] = new MCTSNode(this->maze, this->teams, this->teamTakingItsTurn, this->timeUntilGasClosing, this);
    //configure it
    this->pChildNodes[*pChildIndex]->configureChild(locationIncrement);
    this->pChildNodes[*pChildIndex]->pParentNode = this;
}

//simulate a game until bottom of the tree and return outcome
bool MCTSNode::simulate(){
    //copy current node into simulation node
    MCTSNode simulationNode(this->maze, this->teams, this->teamTakingItsTurn, this->timeUntilGasClosing, nullptr);
    while (!simulationNode.isTerminal()){

        //select random child index
        //TODO : insert constants values as paramters
        char randomChildIndex = std::experimental::randint(1, game::BRANCHING_FACTOR - 1);
        int locationIncrement = simulationNode.getLocationIncrement(&randomChildIndex);
        
        //configure simulation node
        simulationNode.configureChild(locationIncrement);

        //NOTE : debug purpose only
        //simulationNode.printNode();
    }

    return simulationNode.getNodeValue();
}

//update values & visits in node
void MCTSNode::update(int paramValue){
    this->value += paramValue;
    this->visits++;
}

//backpropagate value towards parents
void MCTSNode::backpropagate(int paramValue){
    update(paramValue);
    if(pParentNode != nullptr)
        this->pParentNode->backpropagate(paramValue);
}

//
bool MCTSNode::isLeafNode(){

    for (int i=0; i < game::BRANCHING_FACTOR; i++){
        if (this->pChildNodes[i] != nullptr)
            return false;
    }

    return true;
}

double MCTSNode::getUCB(bool topOfTreeTeam){
    if (topOfTreeTeam == constants::GORANE_TEAM)
        return (double) this->value / this->visits + sqrt(2 * log(this->pParentNode->visits) / this->visits);
    else
        return (double) (this->visits - this->value) / this->visits + sqrt(2 * log(this->pParentNode->visits) / this->visits);
}