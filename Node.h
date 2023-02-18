#include "Constants.h"

#ifndef NODE_H
#define NODE_H

using namespace std;

struct Robot{
    int location;
    int coinNb;
    bool isAlive;
};

class Node
{   public :
        //define pointer to parent node (easy, only one parent)
        //Node *pParentNode = nullptr;
        //define members purely related to the node (game state)
        char maze[constants::NB_OF_MAZE_SQUARES];
        Robot robots[constants::NB_OF_ROBOTS];
        bool teamTakingItsTurn;
        int timeUntilGasClosing;
        int coinsOnGround = -1;
        //define pointers to child nodes
        //NOTE : in order to avoid using vectors (ressource consumming), we use an array of pointers instead and set its size to the maximum number of childs possible a.k.a.
        //branching factor (defined in the constants header).
        //Node *pChildNodes[constants::BRANCHING_FACTOR];

    public :
        //default constructor, when no info about parent nor children
        Node(char *paramMaze, Robot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing);
        //Node();
        int getLocationIncrement(char *childIndex);
        void configureRobotsLocationInChildNode(Robot childRobots[], int locationIncrement);
        void configureCoinsInChildNode(char childMaze[], Robot childRobots[]);
        void configureGasInChildNode(char childMaze[], int *childTimeUntilGasClosing);
        void configureRobotsLivesInChildNode(char childMaze[], Robot childRobots[]);
        void configureTeamInChildNode(Robot childRobots[], bool *childTeamTakingItsTurn);
        //Node configureChild(char childIndex, int locationIncrement);
        char getDescendanceSize();
        char getNextChildIndex(char previousChildIndex);
        //void generateChildren();
        void countCoinsOnGround();
        bool isTerminal();
        double evaluate();
        double getNodeValue();
        void printNode();
};

#endif
