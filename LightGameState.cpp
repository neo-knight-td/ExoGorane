#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "Constants.h"

using namespace std;

struct SimpleRobot{
    int location;
    int coinNb;
    bool isAlive;
};

class LightGameState{
    public :

        char maze[constants::NB_OF_MAZE_SQUARES];
        SimpleRobot robots[constants::NB_OF_ROBOTS];
        bool teamTakingItsTurn;
        int timeUntilGasClosing = 0;

    public :
        //default constructor
        LightGameState(char *paramMaze, SimpleRobot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing){
            //copy maze
            for (int i=0; i< constants::NB_OF_MAZE_SQUARES; i++)
                this->maze[i] = paramMaze[i];
            //copy robots
            for (int j=0; j < constants::NB_OF_ROBOTS; j++)
                this->robots[j] = paramRobots[j];
            
            this->teamTakingItsTurn = paramTeamTakingItsTurn;
            this->timeUntilGasClosing = paramTimeUntilGasClosing;
        }

        void configureSuccessor(int locationIncrement){

            //copy robots
            //TODO : optimize using this https://stackoverflow.com/a/16137997/15539525
            SimpleRobot successorRobots[constants::NB_OF_ROBOTS];
            for (int i=0; i< constants::NB_OF_ROBOTS; i++)
                successorRobots[i] = this->robots[i];

            //adapt the robot's location in successor state
            successorRobots[this->teamTakingItsTurn].location += locationIncrement;
            
            //copy maze content
            //TODO : optimize using this https://stackoverflow.com/a/16137997/15539525
            char successorMaze[constants::NB_OF_MAZE_SQUARES];
            for (int j=0; j< constants::NB_OF_MAZE_SQUARES; j++)
                successorMaze[j] = this->maze[j];

            //adapt the coins on ground in successor state only if we find a coin on the robot's next location
            if (successorRobots[this->teamTakingItsTurn].location & constants::COIN_MASK){
                successorRobots[this->teamTakingItsTurn].coinNb += 1;
                successorMaze[successorRobots[this->teamTakingItsTurn].location] += -constants::COIN_MASK;
            }
            
            //adapt time until gas closes in successor state (unless reaches 0, then close the gas)
            //TODO : time should be decreased only once on two when both robots are alive
            int successorTimeUntilGasClosing = this->timeUntilGasClosing -1;

            //TODO : if necessarry, close the gas
            if (successorTimeUntilGasClosing == 0){
                //close the gas !
                //flip the gas bit inside all squares that are in the gas                   
            }
          
            //adapt robots life if next location is in the gaz
            //NOTE : next 4 lines cost about 100 nanoseconds (on Thomas Desktop)
            //TODO : optimize these 4 lines
            for (int k=0; k< constants::NB_OF_ROBOTS; k++){
                if(successorMaze[successorRobots[k].location] & constants::GAS_MASK)
                    successorRobots[k].isAlive = false;
            }
            
            //adapt team taking its turn in successor state (change team only if other team robots are alive)
            bool successorTeamTakingItsTurn = this->teamTakingItsTurn;
            if (successorRobots[!(this->teamTakingItsTurn)].isAlive){
                bool successorTeamTakingItsTurn = !(this->teamTakingItsTurn);
            }
            
            LightGameState newState = LightGameState(successorMaze, successorRobots, successorTeamTakingItsTurn, successorTimeUntilGasClosing);
        }

        void generateSuccessors(){

            //retrieve location of robot taking his turn
            int robotLocation = this->robots[this->teamTakingItsTurn].location;
                
            if(this->maze[robotLocation] & constants::UP_MASK){
                int locationIncrement = -1;
                configureSuccessor(locationIncrement);
            }
                
            if(this->maze[robotLocation] & constants::DOWN_MASK){
                int locationIncrement = 1;
                configureSuccessor(locationIncrement);
            }
                
            if(this->maze[robotLocation] & constants::LEFT_MASK){
                int locationIncrement = -constants::MAZE_WIDTH;
                configureSuccessor(locationIncrement);
            }
                
            if(this->maze[robotLocation] & constants::RIGHT_MASK){
                int locationIncrement = constants::MAZE_WIDTH;
                configureSuccessor(locationIncrement);
            }
        }
};