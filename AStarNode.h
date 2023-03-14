#include "Node.h"

#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

class AStarNode: public Node {
    public :
        //heuristic (h) is forward cost
        //int forwardCost = 0;
        //cumulative cost is backward cost
        int backwardCost = 0;
        bool isOnPathToAStar = false;
        bool computeResidualCost = false;
        AStarNode *pParentNode = nullptr;
        AStarNode *pChildNodes[game::BRANCHING_FACTOR];

    public :
        //constructor for AStar Node
        AStarNode(const Node &rhs, AStarNode* pParamParentNode, int paramBackwardCost, bool paramComputeResidualCost);
        //TODO : create a destructor !
        ~AStarNode();
        //returns the best child node from current node based on A Star algorithm
        tuple<int, char> runAStar();
        //selects one leaf node from current node based g + h cost and return pointer to it
        tuple<AStarNode*, int> selectFromLeaves();
        //expands node from the current node, simulate a child and return values obtained
        void generateChild(char childIndex);
        //checks if node is a leaf node
        bool isLeafNode();
        //get total cost value
        int getCost();
        //get value of forward cost (heuristic)
        int getHeuristicValue();
        bool isTerminal();
        void backTrackPathToAStar();
        int getDistanceToClosestCoin();
        int getResidualCost();
        int getNumberOfCoinClusters();
        int getDistanceToBorder();
        void modifyToMazeWithOneCoin();
        bool isPossibleToReachMazeCenter();


        void setClusterIdInNeighbours(int coinClusters[], int i, int clusterId);
        int getDistanceBetweenCoinClusters(int a, int b, int coinClusters[]);
        int getDistanceBetweenAllCoinClusters();
        

};

#endif