#include <iostream>
#include <algorithm>
#include <experimental/random>
#include "MCTSNode.h"
#include "Node.h"
#include "Node.cpp"

//constructor for MCTSNode
MCTSNode::MCTSNode(const Node &rhs, MCTSNode* pParamParentNode) : Node(rhs){
    //init all pointers to null
    for (int i=0; i < sizeof(pChildNodes)/sizeof(*pChildNodes); i++)
        this->pChildNodes[i] = nullptr;
    //init parent pointer to parent
    this->pParentNode = pParamParentNode;
}

/*
//destructor for MCTS
MCTSNode::~MCTSNode(){
    //call destructor of child nodes
    char childIndex = -1;
    for (int i = 0; i < this->getDescendanceSize(); i++){
        //update childIndex to next valid child Index
        setToNextLegalChildIndex(&childIndex);
        delete this->pChildNodes[childIndex];
    }
}
*/

//returns the best child node from current node based on MCTS algorithm
tuple<double, char> MCTSNode::runMCTS(int iterations, bool topOfTreeTeam){

    char childIndex = -1;

    //perform for a number of iterations
    for (int i = 0; i < iterations; i++){
        //select
        MCTSNode *pSelectedLeafNode;

        //if first iteration, select root node
        if (i == 0)
            pSelectedLeafNode = this;
        else
        //otherwise select among leaves
            std:tie(pSelectedLeafNode, std::ignore) = selectFromLeaves(topOfTreeTeam);
        
        childIndex = -1;
        for (int j = 0; j < pSelectedLeafNode->getDescendanceSize(); j++){
            pSelectedLeafNode->setToNextLegalChildIndex(&childIndex);

            //expand (generate child)
            pSelectedLeafNode->generateChild(childIndex);
            //simulate (access child you just generated, simulate and return outcome)
            double result = pSelectedLeafNode->pChildNodes[childIndex]->simulate();
            //backpropagate towards parents
            pSelectedLeafNode->pChildNodes[childIndex]->backpropagate(result);
        }
    }


    //TODO : selectFromChildren --> select one child out of children (the one with max ucb)
    int selectedChildIndex = -1;
    double maxUCB = -1;
    int maxVisits = -1;

    childIndex = -1;
    for (int i = 0; i < getDescendanceSize(); i++){
        //update child index
        setToNextLegalChildIndex(&childIndex);
        //record UCB in child node
        //double UCB = this->pChildNodes[childIndex]->getUCB(topOfTreeTeam);
        //record number of visits in child node
        int visits = this->pChildNodes[childIndex]->visits;
        
        //delete the node
        delete this->pChildNodes[childIndex];
        this->pChildNodes[childIndex] = nullptr;

        //if UCB is bigger, save it
        if (visits > maxVisits){
            maxVisits = visits;
            selectedChildIndex = childIndex;
        }
    }

    //should delete the tree before returning
    this->visits = 0;
    this->value = 0;
    //TODO : return nb of visits
    return {maxUCB,selectedChildIndex};
}

//searches the tree using MCTS algorithm
void MCTSNode::search(){

}


//selects one leaf node from current node based on UCB and return pointer to it (with UCB value)
tuple<MCTSNode*, double> MCTSNode::selectFromLeaves(bool topOfTreeTeam){
    /*
        Legacy code for selectFromLeaves
    
        //if node is leaf
        if(isLeafNode()){
            return {this,this->getUCB(topOfTreeTeam)};
        }
        else{//if it's not a leaf node, look in child nodes
            char childIndex = -1;
            double maxUCB = -1;
            MCTSNode *pSelectedLeafNode = nullptr;

            for (int i=0; i < getDescendanceSize(); i++){
                double UCB;
                MCTSNode *pLeafNode;

                //update childIndex to next valid child Index
                setToNextLegalChildIndex(&childIndex);
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
    */

    char childIndex = -1;
    double maxUCB = -1;
    MCTSNode *pSelectedChildNode = nullptr;

    //loop over children to find the one with max UCB
    for (int i=0; i < getDescendanceSize(); i++){

        //update childIndex to next valid child Index
        setToNextLegalChildIndex(&childIndex);
        //recover child node address
        MCTSNode *pChildNode = this->pChildNodes[childIndex];
        //get UCB of child node
        double UCB = pChildNode->getUCB(topOfTreeTeam);
        //if better UCB is found
        if (UCB > maxUCB){
            //select the child node
            pSelectedChildNode = pChildNode;
            maxUCB = UCB;
        }
    }

    //if the best child is a leaf node, we can end selection here & return address of child found
    if(pSelectedChildNode->isLeafNode()){
        return {pSelectedChildNode, pSelectedChildNode->getUCB(topOfTreeTeam)};
    }
    //otherwise call this function again from the selected child node
    else{
        return pSelectedChildNode->selectFromLeaves(topOfTreeTeam);
    }
}

//expands child at specified index
void MCTSNode::generateChild(char childIndex){
    //create a new node
    this->pChildNodes[childIndex] = new MCTSNode(*this, this);
    //configure it
    this->pChildNodes[childIndex]->configureChild(childIndex);
    this->pChildNodes[childIndex]->pParentNode = this;
}

//simulate a game until bottom of the tree and return outcome
double MCTSNode::simulate(){
    //copy current node into simulation node
    MCTSNode simulationNode(*this, nullptr);
    while (!simulationNode.isTerminal()){

        //select random child index (if fight ongoing, only 2 children are possible)
        //TODO : insert constants values as paramters
        char randomChildIndex;
        if (simulationNode.isCombatOngoing)
            randomChildIndex = std::experimental::randint(-1, 0);
        else
            randomChildIndex = std::experimental::randint(-1, game::BRANCHING_FACTOR - 2);

        //need to see if we are in a tunnel to update cannot turn back
        //TODO : investigate to change this
        simulationNode.getDescendanceSize();

        //set random child index to next valid child index (default policy)
        //TODO : improve default policy to apply A Star
        simulationNode.setToNextLegalChildIndex(&randomChildIndex);
        
        //configure simulation node directly
        simulationNode.configureChild(randomChildIndex);

        //NOTE : debug purpose only
        //simulationNode.printNode();
    }

    return simulationNode.getNodeValue();
}

//update values & visits in node
void MCTSNode::update(double paramValue){
    this->value += paramValue;
    this->visits++;
}

//backpropagate value towards parents
void MCTSNode::backpropagate(double paramValue){
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
    if (this->pParentNode->teamTakingItsTurn == constants::GORANE_TEAM)
        return (double) this->value / this->visits + sqrt(2 * log(this->pParentNode->visits) / this->visits);
    else
        return (double) (this->visits - this->value) / this->visits + sqrt(2 * log(this->pParentNode->visits) / this->visits);
}