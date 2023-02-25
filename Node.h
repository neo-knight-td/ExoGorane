
#ifndef NODE_H
#define NODE_H

using namespace std;

struct Robot{
    int location = 0;
    int coinNb = 0;
    bool isAlive = false;
};

class Team{
    public :
        //create a team with 2 robots
        Robot robots[game::NB_OF_ROBOTS_PER_TEAM];
        int coinNb = 0;
        int isAlive = false;
        bool robotTakingItsTurn = false;

    public :
    Team(Robot *paramRobots){
        for(int i=0; i < game::NB_OF_ROBOTS_PER_TEAM; i++){
            this->robots[i] = paramRobots[i];
        }
        updateCoins();
        updateLives();
    }
    
    Team(){
        for(int i=0; i < game::NB_OF_ROBOTS_PER_TEAM; i++){ 
            struct Robot defaultRobot = {0, 0, true};
            this->robots[i] = defaultRobot;
        }
    }

    void updateCoins(){
        int count = 0;
        for(int i = 0; i < game::NB_OF_ROBOTS_PER_TEAM; i++){
            count += this->robots[i].coinNb;
        }
        this->coinNb = count;
    }

    void updateLives(){
        bool allRobotsDead = true;
        for(int i = 0; i < game::NB_OF_ROBOTS_PER_TEAM; i++){
            if (this->robots[i].isAlive)
                allRobotsDead = false;
        }
        this->isAlive = !allRobotsDead;
    }
};

class Node
{   public :
        //define pointer to parent node (easy, only one parent)
        //Node *pParentNode = nullptr;
        //define members purely related to the node (game state)
        char maze[game::NB_OF_MAZE_SQUARES];
        Team teams[game::NB_OF_TEAMS];
        //Robot robots[game::NB_OF_ROBOTS];
        bool teamTakingItsTurn;
        int timeUntilGasClosing;
        int gasClosures = 0;
        int coinsOnGround = -1;
        //define pointers to child nodes
        //NOTE : in order to avoid using vectors (ressource consumming), we use an array of pointers instead and set its size to the maximum number of childs possible a.k.a.
        //branching factor (defined in the constants header).
        //Node *pChildNodes[constants::BRANCHING_FACTOR];

    public :
        //default constructor, when no info about parent nor children
        Node(char *paramMaze, Team *paramTeams, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing);
        //Node();
        int getLocationIncrement(char *childIndex);
        void configureRobotsLocationInChildNode(int locationIncrement);
        void configureCoinsInChildNode();
        void configureTimeInChildNode();
        void configureGasInChildNode();
        void configureRobotsLivesInChildNode();
        void configureTeamInChildNode();
        void configureChild(int locationIncrement);
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
