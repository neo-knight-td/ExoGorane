#include <iostream>
#include <algorithm>
#include "Node.h"

using namespace std;

    //default constructor
    Node::Node(char *paramMaze, Robot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing){
        //copy maze
        for (int i=0; i< constants::NB_OF_MAZE_SQUARES; i++)
            this->maze[i] = paramMaze[i];
        //copy robots
        for (int j=0; j < constants::NB_OF_ROBOTS; j++){
            this->robots[j] = paramRobots[j];
            if (this->robots[j].location >= constants::NB_OF_MAZE_SQUARES)
                cout << "ERROR : trying to initiate robot outside the maze" << endl;
        }
            
        this->teamTakingItsTurn = paramTeamTakingItsTurn;
        this->timeUntilGasClosing = paramTimeUntilGasClosing;
        countCoinsOnGround();
    }

    void Node::configureRobotsLocationInChildNode(Robot childRobots[], int locationIncrement){
        //adapt the robot's location in child node
        //NOTE : no need to return anything as the array is passed by referenced (default in C++). Any modification to childRobots made here will persist outside this function
        childRobots[this->teamTakingItsTurn].location += locationIncrement;        
    }

    void Node::configureCoinsInChildNode(char childMaze[], Robot childRobots[]){
        //adapt the coins on ground in child node only if we find a coin on the robot's next location
        if (childMaze[childRobots[this->teamTakingItsTurn].location] & constants::COIN_MASK){
            childRobots[this->teamTakingItsTurn].coinNb += 1;
            childMaze[childRobots[this->teamTakingItsTurn].location] += -constants::COIN_MASK;
            countCoinsOnGround();
        }
    }

    void Node::configureGasInChildNode(char childMaze[], int *childTimeUntilGasClosing){
        //adapt time until gas closes in child node (unless reaches 0, then close the gas)
        //TODO : time should be decreased only once on two when both robots are alive
        *childTimeUntilGasClosing = this->timeUntilGasClosing -1;

        //TODO : if necessarry, close the gas
        if (*childTimeUntilGasClosing == 0){
            //close the gas !
            //flip the gas bit inside all squares that are in the gas                
        }
    }

    void Node::configureRobotsLivesInChildNode(char childMaze[], Robot childRobots[]){
        //adapt robots life if next location is in the gaz
        //NOTE : next 4 lines cost about 100 nanoseconds (on Thomas Desktop)
        //TODO : optimize these 4 lines
        for (int k=0; k< constants::NB_OF_ROBOTS; k++){
            if(childMaze[childRobots[k].location] & constants::GAS_MASK)
                childRobots[k].isAlive = false;
        }
    }
    
    void Node::configureTeamInChildNode(Robot childRobots[], bool *childTeamTakingItsTurn){
        //adapt team in successor state only if other team robots are alive
        *childTeamTakingItsTurn = this->teamTakingItsTurn;
        if (childRobots[!(this->teamTakingItsTurn)].isAlive){
            *childTeamTakingItsTurn = !(this->teamTakingItsTurn);
        }
    }

    //returns the number of children from the current node (number of legal moves from the current node)
    char Node::getDescendanceSize(){
        //retrieve maze square on which robot taking its turn is located
        char mazeSquare = this->maze[this->robots[this->teamTakingItsTurn].location];
        char descendanceSize = 0;

        if(mazeSquare & constants::UP_MASK){
            descendanceSize++;
        }
            
        if(mazeSquare & constants::DOWN_MASK){
            descendanceSize++;
        }
            
        if(mazeSquare & constants::LEFT_MASK){
            descendanceSize++;
        }
            
        if(mazeSquare & constants::RIGHT_MASK){
            descendanceSize++;
        }

        return descendanceSize;
    }
    
    //this function return the location increment required to reach child node at index childIndex. If however child index refers to a non-legal move, the function
    //returns the location increment to reach child node accessible from next legal move. If updateChildIndex is left to default value (true), the function also modifies the child index to the current child index.
    //TODO change name of this function to getLocationIncrementAndUpdateChildIndex()
    int Node::getLocationIncrement(char *pChildIndex){

        //retrieve maze square on which robot taking its turn is located
        char mazeSquare = this->maze[this->robots[this->teamTakingItsTurn].location];

        //TODO : add default child (child index 0)
        if(*pChildIndex <= 0 && (mazeSquare & constants::UP_MASK)){
            *pChildIndex = 1;
            return -1;
        }
            
        if(*pChildIndex <= 1 && (mazeSquare & constants::DOWN_MASK)){
            *pChildIndex = 2;
            return 1;
        }
            
        if(*pChildIndex <= 2 && (mazeSquare & constants::LEFT_MASK)){
            *pChildIndex = 3;
            return -constants::MAZE_WIDTH;
        }
            
        if(*pChildIndex <= 3 && (mazeSquare & constants::RIGHT_MASK)){
            *pChildIndex = 4;
            return constants::MAZE_WIDTH;
        }
        //if previous index was equal to 4, reset value of child Index and rerun function
        if(*pChildIndex <= 4){
            *pChildIndex = 0;
            return getLocationIncrement(pChildIndex);
        }
        else{
            std::cout << "ERROR : trying to access child that does not exist." << std::endl;
            return -1000;
        }
    }

    
    void Node::configureChild(int locationIncrement){

        configureRobotsLocationInChildNode(this->robots, locationIncrement);
        configureCoinsInChildNode(this->maze, this->robots);
        configureGasInChildNode(this->maze, &(this->timeUntilGasClosing));
        configureRobotsLivesInChildNode(this->maze, this->robots);
        configureTeamInChildNode(this->robots, &(this->teamTakingItsTurn));

    }
    

    /*
    int Node::getLocationIncrement(char childIndex){
        //return the location increment corresponding to the child index
        if(childIndex == 1)
            return -1;
        else if(childIndex == 2)
            return 1;
        else if(childIndex == 3)
            return -constants::MAZE_WIDTH;
        else if (childIndex == 4)
            return constants::MAZE_WIDTH;
        else
            std::cout << "ERROR : Child Index not valid" << std::endl;
    }
    */
    

   /*
    void Node::generateChildren(){

        //retrieve location of robot taking his turn
        int robotLocation = this->robots[this->teamTakingItsTurn].location;

        //TODO : add default child (child index 0)
            
        if(this->maze[robotLocation] & constants::UP_MASK){
            int locationIncrement = -1;
            char childIndex = 1;
            configureChild(childIndex, locationIncrement);
        }
            
        if(this->maze[robotLocation] & constants::DOWN_MASK){
            int locationIncrement = 1;
            char childIndex = 2;
            configureChild(childIndex, locationIncrement);
        }
            
        if(this->maze[robotLocation] & constants::LEFT_MASK){
            int locationIncrement = -constants::MAZE_WIDTH;
            char childIndex = 3;
            configureChild(childIndex, locationIncrement);
        }
            
        if(this->maze[robotLocation] & constants::RIGHT_MASK){
            int locationIncrement = constants::MAZE_WIDTH;
            char childIndex = 4;
            configureChild(childIndex, locationIncrement);
        }
    }
    */

    bool Node::isTerminal(){
        //if no more coins on the ground
        if (this->coinsOnGround == 0)
            return true;
        //if both robots are dead
        else if(!this->robots[0].isAlive && !this->robots[1].isAlive)
            return true;
        else
            return false;
    }

    void Node::countCoinsOnGround(){
        int count = 0;

        for(int i=0; i < constants::NB_OF_MAZE_SQUARES; i++){
            if (this->maze[i] & constants::COIN_MASK)
                count++;
        }

        this->coinsOnGround = count;
    }

    double Node::evaluate(){
        //temporary evaluation function
        return 0.5 + (this->robots[constants::GORANE_TEAM].coinNb - this->robots[constants::ENEMY_TEAM].coinNb)/(2*constants::NB_OF_COINS);
    }

    double Node::getNodeValue(){
        //if G collected more coins than E, G wins (value is 1)
        if (this->robots[constants::GORANE_TEAM].coinNb > this->robots[constants::ENEMY_TEAM].coinNb)
            return constants::MAX_NODE_VALUE;
        //if G collected less coins (or draw), G loses (value is 0)
        else
            return constants::MIN_NODE_VALUE;
    }

    void Node::printNode(){
        //TODO solve display bug
        string outerWall = "*";
        string innerVWall = "|";
        string innerHWall = "-";
        string blank = " ";
        string gaz = "x";
        string aliveGoraneRobot = "G";
        string aliveEnemyRobot = "E";
        string deadGoraneRobot = "g";
        string deadEnemyRobot = "e";
        string coin = "$";

        //only works with a squared number of mazes
        int dim_h = constants::MAZE_WIDTH;
        int dim_v = constants::MAZE_WIDTH;

        //first line is line of outer walls
        //draw outer walls at tile intersections only → i+=2
        for (int i=0; i < (dim_h*2 + 1);i+=2)
            std::cout << outerWall << blank;
        std::cout << std::endl;
            
        for (int i=1; i<(dim_v*2); i++){
            //draw outer walls at tile intersections only 
            if (i%2==0)
            {
                std::cout << outerWall;
            }else{
                std::cout << blank;
            }
            
            

            for (int j = 0; j< (dim_h*2 + 1); j++){
                //if i is odd, print line with square ids or vertical walls
                if(i%2 != 0){
                    //if j is odd, you are in a square
                    if(j%2 != 0){
                        int currentSquareId = (i-1)/2 + (j-1)/2*dim_v;
                        bool currentSquareIdShouldBeBlank = true;
                        
                        //we print Gorane if it is located in the current square
                        if (this->robots[constants::GORANE_TEAM].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::GORANE_TEAM].isAlive)
                                std::cout << aliveGoraneRobot;
                            else
                                std::cout << deadGoraneRobot;
                        }
                        //we print Enemy if it is located in the current square
                        //NOTE : if Enemy & Robot have same location, Gorane will be printed
                        else if(this->robots[constants::ENEMY_TEAM].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::ENEMY_TEAM].isAlive)
                                std::cout << aliveEnemyRobot;
                            else
                                std::cout << deadEnemyRobot;
                        }
                        else {

                            //if no robot is to printed, maybe a coin should be printed
                            if (this->maze[currentSquareId] & constants::COIN_MASK){
                                currentSquareIdShouldBeBlank = false;
                                std::cout << coin;
                            }

                            //if no robot is to printed, maybe a coin should be printed
                            if (this->maze[currentSquareId] & constants::GAS_MASK){
                                currentSquareIdShouldBeBlank = false;
                                std::cout << gaz;
                            }
                                    
                            //if we did not print a robot nor a coin nor a gaz, print nothing
                            if (currentSquareIdShouldBeBlank)
                                std::cout << blank;
                        }

                    }

                    //if j is even and not equal either to first nor last value, an inner wall or blank should be printed
                    else if(j%2 == 0 && j!=0 &&  j != (dim_h*2)){
                        int leftSquareId = (i-1)/2 + (j-2)/2*dim_v;
                        int rightSquareId = (i-1)/2 + j/2*dim_v;

                        if (this->maze[leftSquareId] & constants::RIGHT_MASK)
                            std::cout << blank;
                        //otherwise print wall
                        else
                            std::cout << innerVWall;
                        
                    }
                }
                //if i is even, print line of horizontal walls or blanks
                else if(i%2 == 0){
                    //if j is odd, print square id
                    if(j%2 != 0){
                        int upperSquareId = (i-2)/2 + (j-1)/2*dim_v;
                        int lowerSquareId = i/2 + (j-1)/2*dim_v;

                        if (this->maze[upperSquareId] & constants::DOWN_MASK)
                            std::cout << blank;
                        //otherwise print wall
                        else
                            std::cout << innerHWall;

                    }
                    //if j is even and not equal either to first nor last value (square intersections)
                    else if(j%2 == 0 && j!=0 &&  j != (dim_h*2)){
                        std::cout << blank;
                    }
                }
            }
            if (i%2==0)
            {
                std::cout << outerWall << std::endl;
            }else{
                std::cout << blank << std::endl;
            }
            
        }

        //last line is line of outer walls
        for (int i=0; i < (dim_h*2 + 1);i+=2)
            std::cout << outerWall << blank;
        std::cout << std::endl;
    }