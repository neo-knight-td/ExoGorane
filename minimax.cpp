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
        //NOTE : use a list of coins on the ground iso vector. This to avoid pointer invalidation when creating/erasing
        //elements from the vector. More info : https://stackoverflow.com/a/61409233/15539525
        std::list<int> coinsOnGround;
        std::vector <Robot> robots;
        //NOTE : use a list of successors. This to avoid pointer invalidation when creating/erasing
        //elements from the vector. More info : https://stackoverflow.com/a/61409233/15539525
        std::list <GameState> successors;
        int depthOfState;
        bool friendTurn;

        //for the moment, max depth is set by default to 3 (constant)
        const int MAX_DEPTH = 3;

    public:
        GameState(vector<vector <int>> paramMazeSquares, list<int> paramCoinsOnGround, vector <Robot> paramRobots, int paramDepthOfState, bool paramFriendTurn){
            this->mazeSquares = paramMazeSquares;
            this->coinsOnGround = paramCoinsOnGround;
            this->robots = paramRobots;
            this->depthOfState = paramDepthOfState;
            this->friendTurn = paramFriendTurn;
        }

        bool isTerminalState(){
            
            if (this->coinsOnGround.size() == 0 || this->depthOfState >= MAX_DEPTH){
                return true;
            }
            else{
                return false;
            }
        }

        void generateSuccessors(){

            //select index of robot who has its turn
            int i = 0*this->friendTurn + 1*(!this->friendTurn);

            //iterate on all future robot's locations that are possible
            vector<int> robotNextLocations = this->mazeSquares[this->robots[i].location];
            for(int robotNextLocation : robotNextLocations){

                //adapt the robot's location in successor state
                vector<Robot> adaptedRobots = this->robots;
                adaptedRobots[i].location = robotNextLocation;

                //adapt the coins on ground in successor state only if we find a coin on the robot's next location
                list<int> adaptedCoinsOnGround = this->coinsOnGround;
                
                auto it = std::find(coinsOnGround.begin(), coinsOnGround.end(), robotNextLocation);
                if (it != coinsOnGround.end()){     
                    //NOTE : malloc() error with "erase" if vector of coins on the ground
                    adaptedCoinsOnGround.erase(it);
                    adaptedRobots[i].coinNb++;
                }

                //add the successor to the list of successors of current game state
                //NOTE : "new Obj()" returns reference to newly created object. Need to add * to access value of that object
                this->successors.push_back(* new GameState(this->mazeSquares,adaptedCoinsOnGround,adaptedRobots,this->depthOfState+1,!this->friendTurn));
            }
        }

        tuple<int, int> getMinimax(){
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
                    for(list<GameState>::iterator it = this->successors.begin(); it != this->successors.end(); it++){
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
                    for(list<GameState>::iterator it = this->successors.begin(); it != this->successors.end(); it++){
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
};

int main()
{
    std::cout << "Hello Gorane !" << std::endl;


    vector<vector <int>> mazeVector = {{1,3},{0,2},{1,5},{0,4},{3,5},{2,4}};
    list<int> coinsVector = {3};
    Robot robot1 = Robot(0, 0, true, true);
    Robot robot2 = Robot(5, 0, true, false);
    vector<Robot> robotVector = {robot1, robot2};

    // Following simplified maze (3 x 2) is setup with 2 robots:

    //  *****
    //  *A o*
    //  * | *
    //  *  B*
    //  *****

    //  A is our friendly robot
    //  B is our adversary
    //  o is a coin

    //  A is only 1 square away from o whereas B is 2 squares away from o
    //  A should win by moving to square index 3 and capturing coin o

    GameState simpleGameState = GameState(mazeVector, coinsVector, robotVector, 0, true);

    int valueOfMinimax;
    int moveToMinimax;

    std::tie(valueOfMinimax, moveToMinimax) = simpleGameState.getMinimax();

    std::cout << "Robot A MiniMax value is " << valueOfMinimax << std::endl; 
    std::cout << "Robot A should move to square " << moveToMinimax << std::endl;

}