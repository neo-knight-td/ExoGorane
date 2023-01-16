#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include "GameState.cpp"
#include "Strategy.cpp"

using namespace std;

class Minimax : public Strategy{
    public :
        tuple<int, int, int> getValueOfNextState(GameState gameState, int topOfTreeTeamId){
            //default move & utility returned are -1
            int valueOfNextState;
            int moveToNextState;
            int depthToTerminalState;

            //executed checks common to all strategies
            std::tie(valueOfNextState,moveToNextState,depthToTerminalState) = Strategy::getValueOfNextState(gameState, topOfTreeTeamId);
            //if value of or/and move to next state is/are different that default value, next state is terminal state 
            if(valueOfNextState != this->defaultValueOfNextState || moveToNextState != this->defaultMoveToNextState)
                return {valueOfNextState, moveToNextState, depthToTerminalState};
            

            else {
                gameState.generateSuccessors();

                //select index of robot who has its turn
                //int i = 0*gameState.friendTurn + 1*(!gameState.friendTurn);

                //if its maximizer turn then return the value that maximizes the minimum gains of the opponent
                if (gameState.teamId == topOfTreeTeamId){
                    int value = -1000;
                    int depth = 1000;
                    for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                        //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                        int successorMinimax;
                        int depthToMinimax;
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
                    }
                    return {value, moveToNextState, depth};
                }

                //if its minimizer's turn then return the value that minimizes the maximums gains of the opponent
                else {
                    int value = 1000;
                    int depth = 1000;
                    for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                        //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                        int successorMinimax;
                        int depthToMinimax;
                        std::tie(successorMinimax, std::ignore, depthToMinimax) = getValueOfNextState(*it, topOfTreeTeamId);

                        if (successorMinimax < value){
                            value = successorMinimax;
                            moveToNextState = (*it).robots[gameState.teamId].location;
                        }
                        //if 2 successors lead to same minimax value
                        else if (successorMinimax == value){
                            //check if depth to minimax from current successor is smaller
                            if (depthToMinimax < depth){
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