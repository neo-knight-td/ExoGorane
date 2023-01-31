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

    public:
        GameState(vector<vector <int>> paramMazeSquares, int paramMazeHDim, list<int> paramCoinsOnGround, vector <Robot> paramRobots, int paramDepthOfState, int  paramTeamId, bool paramUtilGoesUp){
            this->mazeSquares = paramMazeSquares;
            this->mazeHDim = paramMazeHDim;
            this->mazeVDim = this->mazeSquares.size()/mazeHDim;
            this->coinsOnGround = paramCoinsOnGround;
            this->robots = paramRobots;
            this->depthOfState = paramDepthOfState;
            this->teamId = paramTeamId;
            this->utilGoesUp = paramUtilGoesUp;
        }


        //this function returns the utility of the state. Only parameter is the id of team on top of the tree
        int getStateUtility(int topOfTreeTeamId){
            //utility should remain monotone function of depth
            return this->robots[topOfTreeTeamId].coinNb - this->robots[(topOfTreeTeamId+1)%2].coinNb;
        }

        bool isTerminalState(){
            if (this->coinsOnGround.size() == 0){
                return true;
            }
            else{
                return false;
            }
        }

        //TODO resolve utilGoesUp here
        void generateSuccessors(int topOfTreeTeamId){

            //select index of robot who has its turn
            int i = this->teamId;

            //iterate on all future robot's locations that are possible
            vector<int> robotNextLocations = this->mazeSquares[this->robots[i].location];
            for(int robotNextLocation : robotNextLocations){

                //adapt the robot's location in successor state
                vector<Robot> adaptedRobots = this->robots;
                adaptedRobots[i].location = robotNextLocation;

                //adapt the coins on ground in successor state only if we find a coin on the robot's next location
                list<int> adaptedCoinsOnGround = this->coinsOnGround;
                bool utilGoesUpInSuccessorState = false;
                int scoreMaxBeforeUpdatingCoins = adaptedRobots[topOfTreeTeamId].coinNb;
                updateCoins(&adaptedCoinsOnGround, &(adaptedRobots[i]));

                //util goes up to true if score of maximizer increases
                if (adaptedRobots[topOfTreeTeamId].coinNb > scoreMaxBeforeUpdatingCoins)
                    utilGoesUpInSuccessorState = true;

                //add the successor to the list of successors of current game state
                //NOTE : next step is to create a new successor & add it to the list of successors.
                //better do this in 2 steps. Otherwise you need to use the "new" keyword which allocates memory on the heap
                //and is never freed. this lead to a huge amount of RAM consummed. 
                GameState successorGameState(this->mazeSquares,this->mazeHDim,adaptedCoinsOnGround,adaptedRobots,this->depthOfState+1,(this->teamId+1)%2, utilGoesUpInSuccessorState);
                this->successors.push_back(successorGameState);
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

        /*tuple<int, int> getMinimax(){
            //default move returned is -1
            int moveToMinimax = -1;
            //if terminal state, return Minimax value & -1 (no next move)
            if (this->isTerminalState()){
                //TODO : next lines to be modified. Friendly robot is not always at index 0
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score
                if (this->robots[0].isAlive){
                    //return the state utility (nb of coins gathered)
                    return {this->robots[0].coinNb, moveToMinimax};
                }
                else{
                    //if friendly robot died, terminal state utility is 0
                    return {0, moveToMinimax};
                }
            }
            else {
                //if not a terminal state, need to compute successor states
                this->generateSuccessors();

                //select index of robot who has its turn
                int i = 0*this->friendTurn + 1*(!this->friendTurn);

                //if its friend's turn (maximizer) then return the value that maximizes the minimum gains of the adversary
                if (this->friendTurn){
                    int value = -1000;
                    for(list<GameState>::iterator it = (this->successors).begin(); it != (this->successors).end(); it++){
                        //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                        int successorMinimax = get<0>((*it).getMinimax());

                        if (successorMinimax > value){
                            value = successorMinimax;
                            moveToMinimax = (*it).robots[i].location;
                        }
                    }
                    return {value, moveToMinimax};
                }

                //if its adversary's turn (minimizer) then return the value that minimizes the maximums gains of the friend
                else {
                    int value = 1000;
                    for(list<GameState>::iterator it = (this->successors).begin(); it != (this->successors).end(); it++){
                        //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                        int successorMinimax = get<0>((*it).getMinimax());

                        if (successorMinimax < value){
                            value = successorMinimax;
                            moveToMinimax = (*it).robots[i].location;
                        }
                    }
                    return {value, moveToMinimax};
                }
            }
        }
        */

        void printGameState(){
            //TODO solve display bug
            string outerWall = "*";
            string innerVWall = "|";
            string innerHWall = "-";
            string blank = " ";
            string goraneRobot = "G";
            string enemyRobot = "E";
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
                                std::cout << goraneRobot;
                            }
                            //we print Enemy if it is located in the current square
                            //NOTE : if Enemy & Robot have same location, Gorane will be printed
                            else if(this->robots[1].location == currentSquareId){
                                currentSquareIdShouldBeBlank = false;
                                std::cout << enemyRobot;
                            }

                            //if no robot is to print, maybe a coin should be printed
                            for(int coinLocation: this->coinsOnGround){
                                if (coinLocation == currentSquareId){
                                    currentSquareIdShouldBeBlank = false;
                                    std::cout << coin;
                                }
                            }

                            //if we did not print a robot nor a coin, print nothing
                            if (currentSquareIdShouldBeBlank)
                                std::cout << blank;
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