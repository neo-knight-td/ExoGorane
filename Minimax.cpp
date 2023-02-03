#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include "Minimax.h"

using namespace std;


    //constructor for Minimax object
    Minimax::Minimax(int paramMaxDepth){
        this->maxDepth = paramMaxDepth;
    }

    //getValueOfNextState is a recursive function that will explore the tree of states and return the maximum utility
    //value reachable from the current game state. It will also provide the move required to reach that value, the depth
    //at which that value appears in the tree & the depth to the nearest state in which utility increases
    tuple<int, int, int, int> Minimax :: getValueOfNextState(GameState gameState, int topOfTreeTeamId){

        //if terminal state
        if (gameState.isTerminalState() || gameState.depthOfState >= maxDepth){
            int depthZero = 0;
            int dummyMove = -1;
            
            //if playing team's robot is alive
            if (gameState.robots[topOfTreeTeamId].isAlive){
                //return the state utility (playing team's robot coin score minus coin score of opponent robot)
                return {gameState.getStateUtility(topOfTreeTeamId), dummyMove, depthZero, depthZero};
            }
            else{
                //if robot died, return the same utility (under investigation what to exactly return)
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score --> ok, written in the rules of the game
                return {gameState.getStateUtility(topOfTreeTeamId), dummyMove, depthZero, depthZero};
            }
        }
        
        //if state is not terminal
        else {
            //initiate values to be returned
            int minimax;
            int moveToMinimax;
            int depthToMinimax;
            int depthToFirstUtilGoesUp;

            //generate the successor states from the current state
            gameState.generateSuccessors(topOfTreeTeamId);

            //if its maximizer turn then return the minimax that maximizes the minimum gains of the opponent
            if (gameState.teamId == topOfTreeTeamId){
                minimax = -1000;
                depthToMinimax= 1000;
                depthToFirstUtilGoesUp = 1000;
                for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                    //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                    int successorMinimax;
                    int successorDepthToMinimax;
                    int successorDepthToFirstUtilGoesUp;
                    
                    std::tie(successorMinimax, std::ignore, successorDepthToMinimax, successorDepthToFirstUtilGoesUp) = getValueOfNextState(*it, topOfTreeTeamId);
                    successorDepthToMinimax++;
                    successorDepthToFirstUtilGoesUp++;

                    //NOTE : debug purpose only -> bug
                    if (gameState.depthOfState == 2){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }
                                                        
                    //if minimax from current successor is higher, update all 4 values to return
                    if (successorMinimax > minimax){
                        minimax = successorMinimax;
                        moveToMinimax = (*it).robots[gameState.teamId].location;
                        depthToMinimax = successorDepthToMinimax;//
                        depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                    }
                    //if 2 successors lead to same minimax minimax
                    else if (successorMinimax == minimax){
                        //check if depth to minimax from current successor is smaller
                        if (successorDepthToMinimax < depthToMinimax){
                            //if its the case then update move & depth. This allows to reach faster the same minimax value
                            moveToMinimax = (*it).robots[gameState.teamId].location;
                            depthToMinimax = successorDepthToMinimax;//
                            depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                        }

                        //check if depth are the same
                        else if (successorDepthToMinimax == depthToMinimax) {
                            //update move to minimax only if depth to first utility goes up in current successor state is smaller
                            if (successorDepthToFirstUtilGoesUp < depthToFirstUtilGoesUp){
                                moveToMinimax = (*it).robots[gameState.teamId].location;
                                depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                            }
                        }
                    }

                    //NOTE : debug purpose only                    
                    if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }
                    
                }

            }

            //if its minimizer's turn then return the value that minimizes the maximums gains of the opponent
            else if (gameState.teamId != topOfTreeTeamId) {
                minimax = 1000;
                depthToMinimax = -1000;
                depthToFirstUtilGoesUp = -1000;
                
                for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                    //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                    int successorMinimax;
                    int successorDepthToMinimax;
                    int successorDepthToFirstUtilGoesUp;

                    std::tie(successorMinimax, std::ignore, successorDepthToMinimax, successorDepthToFirstUtilGoesUp) = getValueOfNextState(*it, topOfTreeTeamId);
                    successorDepthToMinimax++;
                    successorDepthToFirstUtilGoesUp++;

                    //NOTE : debug purpose only                    
                    if (gameState.depthOfState == 1){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }

                    //if minimax from current successor is lower, update all 4 values to return
                    if (successorMinimax < minimax){
                        minimax = successorMinimax;
                        moveToMinimax = (*it).robots[gameState.teamId].location;
                        depthToMinimax = successorDepthToMinimax;
                        depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                    }
                    
                    //if 2 successors lead to same minimax value
                    else if (successorMinimax == minimax){
                        //check if depth to minimax from current successor is bigger. This allows maximizer to reach its minimax slower 
                        if (successorDepthToMinimax > depthToMinimax){
                            moveToMinimax = (*it).robots[gameState.teamId].location;
                            depthToMinimax = successorDepthToMinimax;
                            depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                        }

                        //check if depth are the same
                        else if (successorDepthToMinimax == depthToMinimax) {
                            //update move to minimax only if depth to first utilility goes up in current successor state is bigger
                            if (successorDepthToFirstUtilGoesUp > depthToFirstUtilGoesUp){
                                moveToMinimax = (*it).robots[gameState.teamId].location;
                                depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                            }
                        }
                    }

                    //NOTE : debug purpose only                    
                    if (gameState.depthOfState == 1){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }
                } 
            }

            //check if we don't already have the minimax as utility (or a higher value)
            if (gameState.getStateUtility(topOfTreeTeamId) >= minimax)
                //if its the case then depth should be reset
                depthToMinimax = 0;
            
            //if utility goes up in this state, reset variable to 0
            if (gameState.utilGoesUp)
                depthToFirstUtilGoesUp = 0;

            return {minimax, moveToMinimax, depthToMinimax, depthToFirstUtilGoesUp};
        }
    }
