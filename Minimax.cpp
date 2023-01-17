#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "GameState.cpp"
//#include "Strategy.cpp"

using namespace std;

class Minimax {//: public Strategy{
    public :

        tuple<int, int, int> getValueOfNextState(GameState gameState, int topOfTreeTeamId){
            int moveToNextState;
            int depthToTerminalState;
            /*
            //default move & utility returned are -1
            int valueOfNextState;
            int moveToNextState;
            int depthToTerminalState;

            //executed checks common to all strategies
            std::tie(valueOfNextState,moveToNextState,depthToTerminalState) = Strategy::getValueOfNextState(gameState, topOfTreeTeamId);
            //if value of or/and move to next state is/are different that default value, next state is terminal state 
            if(valueOfNextState != this->defaultValueOfNextState || moveToNextState != this->defaultMoveToNextState)
                return {valueOfNextState, moveToNextState, depthToTerminalState};

            */

            //if terminal state, return current state utility value & default next move (-1)
            if (gameState.isTerminalState()){
                depthToTerminalState = gameState.depthOfState;
                //TODO : next lines to be modified. Does not implement more than 2 robots
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score
                if (gameState.robots[topOfTreeTeamId].isAlive){
                    //return the state utility
                    return {gameState.robots[topOfTreeTeamId].coinNb - gameState.robots[(topOfTreeTeamId+1)%2].coinNb, moveToNextState, depthToTerminalState};
                }
                else{
                    //if friendly robot died, terminal state utility is 0
                    return {0, moveToNextState, depthToTerminalState};
                }
            }
            
            //if state is not terminal
            else {
                gameState.generateSuccessors();

                //if its maximizer turn then return the value that maximizes the minimum gains of the opponent
                if (gameState.teamId == topOfTreeTeamId){
                    int value = -1000;
                    int depth = 1000;
                    for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                        //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                        int successorMinimax;
                        int depthToMinimax;

                        //NOTE : debug purpose only -> bug; depthToMinimax is crap
                        if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                            cout << "Hello" << endl;
                        }
                        std::tie(successorMinimax, std::ignore, depthToMinimax) = getValueOfNextState(*it, topOfTreeTeamId);

                        if (successorMinimax > value){
                            value = successorMinimax;
                            moveToNextState = (*it).robots[gameState.teamId].location;
                            depth = depthToMinimax;
                        }
                        //if 2 successors lead to same minimax value
                        else if (successorMinimax == value){
                            //check if depth to minimax from current successor is smaller
                            if (depthToMinimax < depth){
                                moveToNextState = (*it).robots[gameState.teamId].location;
                                depth = depthToMinimax;
                            }
                        }

                        //NOTE : debug purpose only
                        if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                            cout << "Hello" << endl;
                        }
                    }
                    return {value, moveToNextState, depth};
                }

                //if its minimizer's turn then return the value that minimizes the maximums gains of the opponent
                else {
                    int value = 1000;
                    int depth = -1000;
                    for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                        //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                        int successorMinimax;
                        int depthToMinimax;

                        std::tie(successorMinimax, std::ignore, depthToMinimax) = getValueOfNextState(*it, topOfTreeTeamId);

                        if (successorMinimax < value){
                            value = successorMinimax;
                            moveToNextState = (*it).robots[gameState.teamId].location;
                            depth = depthToMinimax;
                        }
                        
                        //if 2 successors lead to same minimax value
                        else if (successorMinimax == value){
                            //check if depth to minimax from current successor is bigger
                            if (depthToMinimax > depth){
                                moveToNextState = (*it).robots[gameState.teamId].location;
                                depth = depthToMinimax;
                            }
                        }
                        
                    }
                    return {value, moveToNextState, depth};
                }
            }
        }
};