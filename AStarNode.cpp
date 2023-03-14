#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "AStarNode.h"
#include "Node.h"
#include "Node.cpp"

//constructor for AStarNode
AStarNode::AStarNode(const Node &rhs, AStarNode* pParamParentNode, int paramBackwardCost, bool paramComputeResidualCost) : Node(rhs){
    //init all pointers to null
    for (int i=0; i < sizeof(pChildNodes)/sizeof(*pChildNodes); i++)
        this->pChildNodes[i] = nullptr;
    //init parent pointer to parent
    this->pParentNode = pParamParentNode;
    this->backwardCost = paramBackwardCost;
    this->computeResidualCost = paramComputeResidualCost;
}

//TODO : create a destructor !
AStarNode::~AStarNode(){
    //call destructor of child nodes
    char childIndex = -1;
    for (int i = 0; i < this->getDescendanceSize(); i++){
        //update childIndex to next valid child Index
        setToNextLegalChildIndex(&childIndex);
        delete this->pChildNodes[childIndex];
    }
}

//returns the best child node from current node based on A Star algorithm
tuple<int, char> AStarNode::runAStar(){

    char childIndex = -1;
    //start selecting the root
    AStarNode *pSelectedLeafNode = this;

    //run A Star Until we find the path to goal state !
    do{
        int costToSelectedNode;
        childIndex = -1;
        for (int j = 0; j < pSelectedLeafNode->getDescendanceSize(); j++){
            pSelectedLeafNode->setToNextLegalChildIndex(&childIndex);

            //generate child
            pSelectedLeafNode->generateChild(childIndex);
            //update backward cost in child node (+1 wrt parent node)
            //pSelectedLeafNode->pChildNodes[childIndex]->backwardCost++;
            //update forward cost in child node (compute heuristic)
            //pSelectedLeafNode->pChildNodes[childIndex]->setHeuristicValue();
        }

        //select the node from all leaves that minimizes the costs
        std:tie(pSelectedLeafNode, costToSelectedNode) = selectFromLeaves();
        
        //NOTE : debug purpose only
        std::cout << "Following node costs "<< costToSelectedNode << " :" << endl;
        pSelectedLeafNode->printNode();

    }
    while(!pSelectedLeafNode->AStarNode::isTerminal());

    //Backtrack path to A Star
    pSelectedLeafNode->backTrackPathToAStar();

    //ERROR ! > should back track from pSelectedNode to child from this node
    childIndex = -1;
    for (int i = 0; i < getDescendanceSize(); i++){
        
        //update child index
        setToNextLegalChildIndex(&childIndex);

        if (this->pChildNodes[childIndex]->isOnPathToAStar)
            return {pSelectedLeafNode->getCost(),childIndex};

    }

}
//selects one leaf node from current node based g + h cost and return pointer to it
tuple<AStarNode*, int> AStarNode::selectFromLeaves(){
    //if node is leaf
    if(isLeafNode()){
        return {this, this->getCost()};
    }
    else{//if it's not a leaf node, look in child nodes
        char childIndex = -1;
        int minCost = 1000;
        int minNbOfClusters;
        AStarNode *pSelectedLeafNode = nullptr;

        //NOTE : debug only 
        if(this->teams[1].robots[1].location == 16){
            //std::cout<< "I visited 16" << endl;
        }

        for (int i=0; i < getDescendanceSize(); i++){
            int cost;
            AStarNode *pLeafNode;

            //update childIndex to next valid child Index
            setToNextLegalChildIndex(&childIndex);
            //recover child node address
            AStarNode *pChildNode = this->pChildNodes[childIndex];

            //NOTE : debug only 
            if(this->pChildNodes[childIndex]->teams[1].robots[1].location == 22){
                //std::cout<< "I visited 22" << endl;
            }
            //perform selection from child node then return best leaf and associated cost
            std::tie(pLeafNode, cost) = pChildNode->selectFromLeaves();
            //if better cost is found update the values to minimize
            if (cost < minCost){
                pSelectedLeafNode = pLeafNode;
                minCost = cost;
            }
        }

        //NOTE : debug only
        /*
        if(minCost == 7){
            //std::cout << "I'm here" << endl;
        }
        */

        return {pSelectedLeafNode, minCost};
    }
}
//expands node from the current node, simulate a child and return values obtained
void AStarNode::generateChild(char childIndex){
    //create a new A star node (with backward cost + 1 & same residual cost param)
    this->pChildNodes[childIndex] = new AStarNode(*this, this, this->backwardCost+1, this->computeResidualCost);
    //configure it
    this->pChildNodes[childIndex]->configureChild(childIndex);
    this->pChildNodes[childIndex]->pParentNode = this;
}

//checks if node is a leaf node
bool AStarNode::isLeafNode(){
    for (int i=0; i < game::BRANCHING_FACTOR; i++){
        if (this->pChildNodes[i] != nullptr)
            return false;
    }

    return true;
}

//get residual cost value (cost after a terminal state is reached)
int AStarNode::getResidualCost(){
    int residualCost = 0;
    //if number of clusters increases
    if (getNumberOfCoinClusters() > this->pParentNode->getNumberOfCoinClusters()){
        //TODO : may be tuned
        residualCost += 1;
    }
    
    //if not on a border, add cost (the higher the distance to the border the higher the cost)
    int costForDistanceToBorder = getDistanceToBorder() - 1;
    //TODO : may be tuned
    residualCost += costForDistanceToBorder;

    //TODO : add some conditions...


    return residualCost;
}

//get value of forward cost (heuristic)
int AStarNode::getHeuristicValue(){
    //if node is not terminal, get classical heuristic (distance to closest coin)
    if (!this->AStarNode::isTerminal())
        return getDistanceToClosestCoin();
    //otherwise
    else{
        //return the residual cost after the goal is reached (only if computeResidualCost is set to true)
        if(this->computeResidualCost)
            return getResidualCost();
        else
            return 0;
    }
        
}

//get total cost value
int AStarNode::getCost(){
    //return h + g
    return getHeuristicValue() + this->backwardCost;
}

bool AStarNode::isTerminal()
{
    // if a coin was found (we have less coins than in parent node)
    if (this->pParentNode != nullptr && this->coinsOnGround < this->pParentNode->coinsOnGround)
        return true;
    else
        return false;
}

void AStarNode::backTrackPathToAStar(){
    this->isOnPathToAStar = true;
    if (this->pParentNode != nullptr)
        this->pParentNode->backTrackPathToAStar();
}

int AStarNode::getDistanceToClosestCoin(){
    bool robotTakingItsTurn = this->teams[this->teamTakingItsTurn].robotTakingItsTurn;
    int robotLocation = this->teams[this->teamTakingItsTurn].robots[robotTakingItsTurn].location;

    int minDist = 1000;
    //loop on all square
    for (int i =0; i < game::NB_OF_MAZE_SQUARES; i++){
        char mazeSquare = this->maze[i];
        //if we find a coin on the ground
        if (mazeSquare & constants::COIN_MASK){
            
            //compute manhattan distance to coin
            int dist = abs(robotLocation%game::MAZE_WIDTH - i%game::MAZE_WIDTH) + abs(robotLocation/game::MAZE_WIDTH - i/game::MAZE_WIDTH);

            //NOTE : debug purpose only
            //if (dist == 0)
                //cout << "look here" << endl;

            //if smaller than minimum, record it
            if (dist < minDist)
                minDist = dist;
        }
    }

    return minDist;       
}

//get the distance to the closest border (we assume dist = 1 when closest to the border)
int AStarNode::getDistanceToBorder(){
    bool robotTakingItsTurn = this->teams[this->teamTakingItsTurn].robotTakingItsTurn;
    int robotLocation = this->teams[this->teamTakingItsTurn].robots[robotTakingItsTurn].location;

    int distToBorders[4] = {robotLocation%game::MAZE_WIDTH + 1,
    game::MAZE_WIDTH - robotLocation%game::MAZE_WIDTH,
    robotLocation/game::MAZE_WIDTH + 1,
    game::MAZE_WIDTH - robotLocation/game::MAZE_WIDTH
    };

    return *min_element(distToBorders, distToBorders + 4);

}

//will modify the maze of the node to have only one coin in the center
void AStarNode::modifyToMazeWithOneCoin(){
    //erase all coins in the game
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i ++){
        if (this->maze[i] & constants::COIN_MASK){
            this->maze[i] += - constants::COIN_MASK;
        }
    }

    //add one coin the center of the maze
    this->maze[game::NB_OF_MAZE_SQUARES/2 - game::MAZE_WIDTH/2] += constants::COIN_MASK;
}

bool AStarNode::isPossibleToReachMazeCenter(){
    //copy current node except you don't want to compute residual costs in it
    AStarNode nodeWithOneCoin(*this, this, 0, false);
    //set only one coin in the middle of the maze
    nodeWithOneCoin.modifyToMazeWithOneCoin();

    int costToLonelyCoin;
    int indexToLonelyCoin;

    std::tie(costToLonelyCoin, indexToLonelyCoin) = nodeWithOneCoin.runAStar();
}

void AStarNode::setClusterIdInNeighbours(int coinClusters[], int i, int clusterId){
    //set cluster of current coin
    coinClusters[i] = clusterId;

    //set neighbours
    int neighbours[4] = {-1000,-1000,-1000,-1000};
    
    if (i%game::MAZE_WIDTH != 0)
        neighbours[0] = i - 1;
    if (i%game::MAZE_WIDTH != game::MAZE_WIDTH -1)
        neighbours[1] = i + 1;
    if (i/game::MAZE_WIDTH != 0)
        neighbours[2] = i - game::MAZE_WIDTH;
    if (i/game::MAZE_WIDTH != game::MAZE_WIDTH -1)
        neighbours[3] = i + game::MAZE_WIDTH;

    //propagate cluster id in neighbours !
    for (int j=0; j < 4; j++){
        if (neighbours[j] != -1000 && coinClusters[neighbours[j]] == 0 && this->maze[neighbours[j]] & constants::COIN_MASK)
            setClusterIdInNeighbours(coinClusters, neighbours[j], clusterId);
    }

}

//get the distance between coin clusters a & b
int AStarNode::getDistanceBetweenCoinClusters(int a, int b, int coinClusters[]){
    int minDist = 1000;

    //loop over all coins on the ground
    for (int i =0; i < game::NB_OF_MAZE_SQUARES; i++){
        char mazeSquare = this->maze[i];
        if (mazeSquare & constants::COIN_MASK){

            //if current coin belongs to cluster a
            if (coinClusters[i] == a){

                //loop over all coins on the ground
                for (int j =0; j < game::NB_OF_MAZE_SQUARES; j++){
                    char mazeSquare = this->maze[j];
                    if (mazeSquare & constants::COIN_MASK){

                        //if current coin belongs to cluster b
                        if (coinClusters[j] == b){
                            //measure the distance
                            int dist = abs(i%game::MAZE_WIDTH - j%game::MAZE_WIDTH) + abs(i/game::MAZE_WIDTH - j/game::MAZE_WIDTH);
                            //record distance if smaller than current minimum
                            if (dist < minDist)
                                minDist = dist;
                        }
                    }
                }

            }
        }
    }

    return minDist;
}

int AStarNode::getNumberOfCoinClusters(){
    int coinClusters[game::NB_OF_MAZE_SQUARES] = {0};
    int nbOfClusters = 0;

    //build coin clusters :
    //loop over all coins on the ground
    for (int i =0; i < game::NB_OF_MAZE_SQUARES; i++){
        char mazeSquare = this->maze[i];
        if (mazeSquare & constants::COIN_MASK){

            //if current coin has no cluster yet
            if (coinClusters[i] == 0){
                //update cluster id
                nbOfClusters++;
                //set cluster id to all coins in the cluster
                setClusterIdInNeighbours(coinClusters, i, nbOfClusters);
            }
        }
    }

    return nbOfClusters;
}

int AStarNode::getDistanceBetweenAllCoinClusters(){
    int coinClusters[game::NB_OF_MAZE_SQUARES] = {0};
    int nbOfClusters = 0;

    //build coin clusters :
    //loop over all coins on the ground
    for (int i =0; i < game::NB_OF_MAZE_SQUARES; i++){
        char mazeSquare = this->maze[i];
        if (mazeSquare & constants::COIN_MASK){

            //if current coin has no cluster yet
            if (coinClusters[i] == 0){
                //update cluster id
                nbOfClusters++;
                //set cluster id to all coins in the cluster
                setClusterIdInNeighbours(coinClusters, i, nbOfClusters);
            }
        }
    }

    //if only one cluster, there is no distance 
    if (nbOfClusters == 1){
        return 0;
    }

    else{
        //get minimum distance between all the clusters
        int minDistBetweenClusters = 1000;

        for (int i = 0; i < nbOfClusters; i++){
            for (int j = 0; j < nbOfClusters; j++){
                int a = i + 1;
                int b = j + 1;
                if (a != b){
                    int dist = getDistanceBetweenCoinClusters(a,b,coinClusters);
                    if (dist < minDistBetweenClusters)
                        minDistBetweenClusters = dist;
                }
            }
        }

        return minDistBetweenClusters*(nbOfClusters-1);
    }


}


