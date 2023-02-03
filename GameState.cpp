#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>

using namespace std;

class Robot{
    public:
        int location;
        int coinNb;
        bool isAlive;
        bool isFriend;

    public :
        Robot(int paramLocation, int paramCoinNb, bool paramIsAlive, bool paramIsFriend){
            this->location = paramLocation;
            this->coinNb = paramCoinNb;
            this->isAlive = paramIsAlive;
            this->isFriend = paramIsFriend;
        }
};

class GameState {
    public:
        std::vector<vector <int>> mazeSquares;
        int mazeHDim;
        int mazeVDim;
        //NOTE : use a list of coins on the ground iso vector. This to avoid pointer invalidation when creating/erasing
        //elements from the vector. More info : https://stackoverflow.com/a/61409233/15539525
        std::list<int> coinsOnGround;
        std::vector <Robot> robots;
        //NOTE : use a list of successors. This to avoid pointer invalidation when creating/erasing
        //elements from the vector. More info : https://stackoverflow.com/a/61409233/15539525
        std::list <GameState> successors;
        int depthOfState;
        //id of team who has its turn
        int teamId;
        //bool true if utility of state increases compared to parent state (for team with id teamId)
        bool utilGoesUp;
        //time since start of game. Units are game turns (int)
        int timeSinceStartOfGame;
        //time interval at which gas closes
        int gasClosingInterval;

    public:
        GameState(vector<vector <int>> paramMazeSquares, int paramMazeHDim, list<int> paramCoinsOnGround, vector <Robot> paramRobots, int paramDepthOfState, int  paramTeamId, bool paramUtilGoesUp, int paramTimeSinceStartOfGame, int paramGasClosingInterval){
            this->mazeSquares = paramMazeSquares;
            this->mazeHDim = paramMazeHDim;
            this->mazeVDim = this->mazeSquares.size()/mazeHDim;
            this->coinsOnGround = paramCoinsOnGround;
            this->robots = paramRobots;
            this->depthOfState = paramDepthOfState;
            this->teamId = paramTeamId;
            this->utilGoesUp = paramUtilGoesUp;
            this->timeSinceStartOfGame = paramTimeSinceStartOfGame;
            this->gasClosingInterval = paramGasClosingInterval;
        }


        //this function returns the utility of the state. Only parameter is the id of team on top of the tree
        int getStateUtility(int topOfTreeTeamId){
            //utility should remain monotone function of depth
            return this->robots[topOfTreeTeamId].coinNb - this->robots[(topOfTreeTeamId+1)%2].coinNb;
        }

        bool isTerminalState(){
            //if no more coins on the ground
            if (this->coinsOnGround.size() == 0)
                return true;
            //if both robots are dead
            else if(!this->robots[0].isAlive && !this->robots[1].isAlive)
                return true;
            else
                return false;
        }


        void generateSuccessors(int topOfTreeTeamId){

            //select index of robot that has his turn
            int i = this->teamId;

            //generate all future robot's locations that are possible
            vector<int> robotNextLocations = this->mazeSquares[this->robots[i].location];

            //if robot can move (is not in the gas), create a successor for each to the next locations
            if (!robotNextLocations.empty()){

                for(int robotNextLocation : robotNextLocations){

                //adapt the robot's location in successor state
                vector<Robot> successorRobots = this->robots;
                successorRobots[i].location = robotNextLocation;

                //save robot's score before updating coins
                bool utilGoesUpInSuccessorState = false;
                int scoreMaxBeforeUpdatingCoins = successorRobots[topOfTreeTeamId].coinNb;

                //adapt the coins on ground in successor state only if we find a coin on the robot's next location
                list<int> successorCoinsOnGround = this->coinsOnGround;
                updateCoins(&successorCoinsOnGround, &(successorRobots[i]));

                //util goes up to true if score of maximizer increases
                if (successorRobots[topOfTreeTeamId].coinNb > scoreMaxBeforeUpdatingCoins)
                    utilGoesUpInSuccessorState = true;

                //adapt successor depth
                int successorDepthOfState = this->depthOfState + 1;

                //adapt time in successor state
                int successorTimeSinceStartOfGame = this->timeSinceStartOfGame;
                updateTime(&successorDepthOfState, &successorTimeSinceStartOfGame);

                //adapt the maze if gas closing interval is reach
                std::vector<vector <int>> successorMazeSquares = this->mazeSquares;
                updateMaze(&successorMazeSquares, successorTimeSinceStartOfGame);

                //adapt robots if next location is in the gaz. 
                updateRobotsLife(&successorMazeSquares, &successorRobots);

                //adapted team id
                int successorTeamId = this->teamId;
                if (successorRobots[(this->teamId+1)%2].isAlive)
                    successorTeamId = (teamId+1)%2;   

                //add the successor to the list of successors of current game state
                //NOTE : next step is to create a new successor & add it to the list of successors.
                //better do this in 2 steps. Otherwise you need to use the "new" keyword which allocates memory on the heap
                //which is never freed. This lead to a huge amount of RAM consummed. 
                GameState successorGameState(successorMazeSquares, this->mazeHDim, successorCoinsOnGround, successorRobots, successorDepthOfState, successorTeamId, utilGoesUpInSuccessorState, successorTimeSinceStartOfGame, this->gasClosingInterval);
                this->successors.push_back(successorGameState);
                }

            }
            else {
                //under construction (this section should never be reached)
                std::cout << "WARNING : Trying to generate successors for a robot with no move possible." << endl;
            }
            
        }

        //update coins on ground (& in robot) in successor state
        void updateCoins(list<int> *pCoinsOnGround, Robot *pRobot){
            auto it = std::find((*pCoinsOnGround).begin(), (*pCoinsOnGround).end(), (*pRobot).location);
            if (it != (*pCoinsOnGround).end()){     
                (*pCoinsOnGround).remove(*it);
                (*pRobot).coinNb++;
            }
        }

        void updateMaze(vector<vector <int>> *pMazeSquares, int time){
            //adapt the maze if gas closing interval is reach
            if (time%this->gasClosingInterval == 0){
                int nbOfSquaresInTheGaz = time/gasClosingInterval;

                for(int h=0; h < (*pMazeSquares).size(); h++){
                    //erase possible moves for first column(s) of the maze
                    if (h < this->mazeVDim*nbOfSquaresInTheGaz)
                        (*pMazeSquares)[h] = {};
                    //erase possible moves for first line(s) of the maze
                    else if (h%this->mazeVDim < nbOfSquaresInTheGaz)
                        (*pMazeSquares)[h] = {};
                    //erase possible moves for last line(s) of the maze
                    else if (h%this->mazeVDim >= this->mazeVDim - nbOfSquaresInTheGaz)
                        (*pMazeSquares)[h] = {};
                    //erase possible moves for the last column(s) of the maze
                    else if (h > this->mazeHDim*this->mazeVDim - nbOfSquaresInTheGaz*this->mazeVDim)
                        (*pMazeSquares)[h] = {};
                }
            }
        }

        void updateRobotsLife(vector<vector <int>> *pMazeSquares, vector<Robot> *pRobots){
            for (int k; k < (*pRobots).size(); k++){
                //if square is empty (gas), robot is dead
                if((*pMazeSquares)[(*pRobots)[k].location].empty())
                    (*pRobots)[k].isAlive = false;
            }
        }

        void updateTime(int *depth, int *time){
            //if both teams are alive, increase time once on two
            if(this->robots[0].isAlive && this->robots[1].isAlive){
                if ((*depth)%2 == 0){
                    *time = *time + 1;
                }
            }
            //otherwise, increase time independently of the depth
            else
                *time = *time + 1;
        }

        void printGameState(){
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
            int dim_h = this->mazeHDim;
            int dim_v = this->mazeVDim;

            int square_id;

            //first line is line of outer walls
            for (int i=0; i < (dim_h*2 + 1);i++)
                std::cout << outerWall;
            std::cout << std::endl;
                
            for (int i=1; i<(dim_v*2); i++){
                std::cout << outerWall;

                for (int j = 0; j< (dim_h*2 + 1); j++){
                    //if i is odd, print line with square ids or vertical walls
                    if(i%2 != 0){
                        //if j is odd, you are in a square
                        if(j%2 != 0){
                            int currentSquareId = (i-1)/2 + (j-1)/2*dim_v;
                            bool currentSquareIdShouldBeBlank = true;
                            
                            //we print Gorane if it is located in the current square
                            if (this->robots[0].location == currentSquareId){
                                currentSquareIdShouldBeBlank = false;
                                if(this->robots[0].isAlive)
                                    std::cout << aliveGoraneRobot;
                                else
                                    std::cout << deadGoraneRobot;
                            }
                            //we print Enemy if it is located in the current square
                            //NOTE : if Enemy & Robot have same location, Gorane will be printed
                            else if(this->robots[1].location == currentSquareId){
                                currentSquareIdShouldBeBlank = false;
                                if(this->robots[1].isAlive)
                                    std::cout << aliveEnemyRobot;
                                else
                                    std::cout << deadEnemyRobot;
                            }
                            else {

                                //if no robot is to printed, maybe a coin should be printed
                                for(int coinLocation: this->coinsOnGround){
                                    if (coinLocation == currentSquareId){
                                        currentSquareIdShouldBeBlank = false;
                                        std::cout << coin;
                                    }
                                }

                                //print gaz if the current square is empty of possible moves
                                if (this->mazeSquares[currentSquareId].empty() && currentSquareIdShouldBeBlank){
                                    std::cout << gaz;
                                    currentSquareIdShouldBeBlank = false;
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

                            auto it = std::find(this->mazeSquares[leftSquareId].begin(), this->mazeSquares[leftSquareId].end(), rightSquareId);
                            //if right square is not accessible from left square, print inner wall
                            if (it == this->mazeSquares[leftSquareId].end())
                                std::cout << innerVWall;
                            //otherwise print blank
                            else
                                std::cout << blank;

                        }
                    }
                    //if i is even, print line of horizontal walls or blanks
                    else if(i%2 == 0){
                        //if j is odd, print square id
                        if(j%2 != 0){
                            int upperSquareId = (i-2)/2 + (j-1)/2*dim_v;
                            int lowerSquareId = i/2 + (j-1)/2*dim_v;

                            auto it = std::find(this->mazeSquares[upperSquareId].begin(), this->mazeSquares[upperSquareId].end(), lowerSquareId);
                            //if lower square is not accessible from upper square, print inner wall
                            if (it == this->mazeSquares[upperSquareId].end())
                                std::cout << innerHWall;
                            //otherwise print blank
                            else
                                std::cout << blank;
                        }
                        //if j is even and not equal either to first nor last value (square intersections)
                        else if(j%2 == 0 && j!=0 &&  j != (dim_h*2)){
                            std::cout << blank;
                        }
                    }
                }
                std::cout << outerWall << std::endl;
            }

            //last line is line of outer walls
            for (int i=0; i < (dim_h*2 + 1);i++)
                std::cout << outerWall;
            std::cout << std::endl;
        }
};