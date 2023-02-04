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

    //chooseFromSuccessor contains the logical core of Minimax. Based on the state of the game and the team taking the turn, it will return which successor
    //is to be chosen. This function can be used for both the maximizer and the minimizer. Only the comparators will vary depending on which one is playing.
    void Minimax :: chooseFromSuccessors(GameState gameState, int topOfTreeTeamId, std::function<bool(int,int)> comparatorGreaterLesser, std::function<bool(int,int)> comparatorLesserGreater, int *minimax,
        int *moveToMinimax, int *depthToMinimax, int *depthToFirstUtilGoesUp, int *depthToDeath){
        for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
            //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
            int successorMinimax;
            int successorDepthToMinimax;
            int successorDepthToFirstUtilGoesUp;
            int successordepthToDeath;
            
            std::tie(successorMinimax, std::ignore, successorDepthToMinimax, successorDepthToFirstUtilGoesUp, successordepthToDeath) = getValueOfNextState(*it, topOfTreeTeamId);
            successorDepthToMinimax++;
            if (successorDepthToFirstUtilGoesUp!=DUMMY_DEPTH)
                successorDepthToFirstUtilGoesUp++;
            //if (gameState.robots[topOfTreeTeamId].isAlive)
            successordepthToDeath++;

            //NOTE : debug purpose only -> bug
            if (gameState.depthOfState == 2){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                //cout << "Hello" << endl;
            }
                                                
            //if minimax from current successor is higher, update all 4 values to return
            if (comparatorGreaterLesser(successorMinimax,*minimax)){
                *minimax = successorMinimax;
                *moveToMinimax = (*it).robots[gameState.teamId].location;
                *depthToMinimax = successorDepthToMinimax;//
                *depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                *depthToDeath = successordepthToDeath;
            }
            //if 2 successors lead to same minimax minimax
            else if (successorMinimax == *minimax){
                //check if depth to minimax from current successor is smaller and that maximizer robot is alive in successor state
                //indeed, we want to reach the minimax value as soon as possible, except if this implies to commit suicide
                if (comparatorGreaterLesser(successordepthToDeath,*depthToDeath)){// invert in min
                //if (successorDepthToMinimax < depthToMinimax){//} && (*it).robots[topOfTreeTeamId].isAlive){
                    //if its the case then update the 3 values. This allows to reach faster the same minimax value
                    *moveToMinimax = (*it).robots[gameState.teamId].location;
                    *depthToMinimax = successorDepthToMinimax;//
                    *depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                    *depthToDeath = successordepthToDeath;
                }

                //check if depth are the same
                else if (successordepthToDeath == *depthToDeath){
                //else if (successorDepthToMinimax == depthToMinimax) {
                    //TODO : check depth to robot alive
                    //if (successordepthToDeath > depthToDeath){
                    if (comparatorLesserGreater(successorDepthToMinimax, *depthToMinimax)){// invert in min
                        *moveToMinimax = (*it).robots[gameState.teamId].location;
                        *depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                        //depthToDeath = successordepthToDeath;
                        *depthToMinimax = successorDepthToMinimax;
                    }

                    //else if (successordepthToDeath == depthToDeath){
                    else if (successorDepthToMinimax == *depthToMinimax){
                        //update move to minimax only if depth to first utility goes up in current successor state is smaller
                        if (comparatorLesserGreater(successorDepthToFirstUtilGoesUp, *depthToFirstUtilGoesUp) && successorDepthToFirstUtilGoesUp != DUMMY_DEPTH){// invert in min
                            *moveToMinimax = (*it).robots[gameState.teamId].location;
                            *depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                        }

                    }
                }
            }

            //NOTE : debug purpose only                    
            if (gameState.depthOfState == 2){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                //cout << "Hello" << endl;
            }
            
        }
    }

    //getValueOfNextState is a recursive function that will explore the tree of states and return the maximum utility
    //value reachable from the current game state. It will also provide the move required to reach that value, the depth
    //at which that value appears in the tree, the depth at which utility increases & the depth to the death of the robot
    tuple<int, int, int, int, int> Minimax :: getValueOfNextState(GameState gameState, int topOfTreeTeamId){

        //if terminal state
        if (gameState.isTerminalState() || gameState.depthOfState >= maxDepth){
            int depthZero = 0;
            int depthUtilGoesUp = DUMMY_DEPTH;
            int dummyMove = -1;

            //if utility goes up in this state, set it to 0, otherwise leave it to dummy value
            if (gameState.utilGoesUp)
                depthUtilGoesUp = 0;
            
            //if playing team's robot is alive
            if (gameState.robots[topOfTreeTeamId].isAlive){
                //return the state utility (playing team's robot coin score minus coin score of opponent robot)
                return {gameState.getStateUtility(topOfTreeTeamId), dummyMove, depthZero, depthUtilGoesUp, depthZero};
            }
            else{
                //if robot died, return the same utility (under investigation what to exactly return)
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score --> ok, written in the rules of the game
                return {gameState.getStateUtility(topOfTreeTeamId), dummyMove, depthZero, depthUtilGoesUp, depthZero};
            }
        }
        
        //if state is not terminal
        else {
            //initiate values to be returned
            int minimax;
            int moveToMinimax;
            int depthToMinimax;
            int depthToFirstUtilGoesUp;
            int depthToDeath;

            //generate the successor states from the current state
            gameState.generateSuccessors(topOfTreeTeamId);

            //if its maximizer turn then return the minimax that maximizes the minimum gains of the opponent
            if (gameState.teamId == topOfTreeTeamId){
                minimax = -1000;
                depthToMinimax= 1000;
                depthToFirstUtilGoesUp = 1000;
                depthToDeath = -1000;

                chooseFromSuccessors(gameState, topOfTreeTeamId, std::greater<int>(), std::less<int>(), &minimax, &moveToMinimax, &depthToMinimax, &depthToFirstUtilGoesUp, &depthToDeath);
                /*
                for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                    //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                    int successorMinimax;
                    int successorDepthToMinimax;
                    int successorDepthToFirstUtilGoesUp;
                    int successordepthToDeath;
                    
                    std::tie(successorMinimax, std::ignore, successorDepthToMinimax, successorDepthToFirstUtilGoesUp, successordepthToDeath) = getValueOfNextState(*it, topOfTreeTeamId);
                    successorDepthToMinimax++;
                    if (successorDepthToFirstUtilGoesUp!=DUMMY_DEPTH)
                        successorDepthToFirstUtilGoesUp++;
                    //if (gameState.robots[topOfTreeTeamId].isAlive)
                    successordepthToDeath++;

                    //NOTE : debug purpose only -> bug
                    if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }
                                                        
                    //if minimax from current successor is higher, update all 4 values to return
                    if (successorMinimax > minimax){
                        minimax = successorMinimax;
                        moveToMinimax = (*it).robots[gameState.teamId].location;
                        depthToMinimax = successorDepthToMinimax;//
                        depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                        depthToDeath = successordepthToDeath;
                    }
                    //if 2 successors lead to same minimax minimax
                    else if (successorMinimax == minimax){
                        //check if depth to minimax from current successor is smaller and that maximizer robot is alive in successor state
                        //indeed, we want to reach the minimax value as soon as possible, except if this implies to commit suicide
                        if (successordepthToDeath > depthToDeath){// invert in min
                        //if (successorDepthToMinimax < depthToMinimax){//} && (*it).robots[topOfTreeTeamId].isAlive){
                            //if its the case then update the 3 values. This allows to reach faster the same minimax value
                            moveToMinimax = (*it).robots[gameState.teamId].location;
                            depthToMinimax = successorDepthToMinimax;//
                            depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                            depthToDeath = successordepthToDeath;
                        }

                        //check if depth are the same
                        else if (successordepthToDeath == depthToDeath){
                        //else if (successorDepthToMinimax == depthToMinimax) {
                            //TODO : check depth to robot alive
                            //if (successordepthToDeath > depthToDeath){
                            if (successorDepthToMinimax < depthToMinimax){// invert in min
                                moveToMinimax = (*it).robots[gameState.teamId].location;
                                depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                                //depthToDeath = successordepthToDeath;
                                depthToMinimax = successorDepthToMinimax;
                            }

                            //else if (successordepthToDeath == depthToDeath){
                            else if (successorDepthToMinimax == successorDepthToMinimax){
                                //update move to minimax only if depth to first utility goes up in current successor state is smaller
                                if (successorDepthToFirstUtilGoesUp < depthToFirstUtilGoesUp && successorDepthToFirstUtilGoesUp != DUMMY_DEPTH){// invert in min
                                    moveToMinimax = (*it).robots[gameState.teamId].location;
                                    depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                                }

                            }
                        }
                    }

                    //NOTE : debug purpose only                    
                    if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }
                    
                }
                */

            }

            //if its minimizer's turn then return the value that minimizes the maximums gains of the opponent
            else if (gameState.teamId != topOfTreeTeamId) {
                minimax = 1000;
                depthToMinimax = -1000;
                depthToFirstUtilGoesUp = -1000;
                depthToDeath = 1000;

                chooseFromSuccessors(gameState, topOfTreeTeamId, std::less<int>(), std::greater<int>(), &minimax, &moveToMinimax, &depthToMinimax, &depthToFirstUtilGoesUp, &depthToDeath);

                /*
                for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                    //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                    int successorMinimax;
                    int successorDepthToMinimax;
                    int successorDepthToFirstUtilGoesUp;
                    int successordepthToDeath;

                    std::tie(successorMinimax, std::ignore, successorDepthToMinimax, successorDepthToFirstUtilGoesUp, successordepthToDeath) = getValueOfNextState(*it, topOfTreeTeamId);
                    successorDepthToMinimax++;
                    if (successorDepthToFirstUtilGoesUp!=DUMMY_DEPTH)
                        successorDepthToFirstUtilGoesUp++;
                    //if (gameState.robots[topOfTreeTeamId].isAlive)
                    successordepthToDeath++;

                    //NOTE : debug purpose only                    
                    if (gameState.depthOfState == 1){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }

                    //if minimax from current successor is lower, update all 5 values to return
                    if (successorMinimax < minimax){
                        minimax = successorMinimax;
                        moveToMinimax = (*it).robots[gameState.teamId].location;
                        depthToMinimax = successorDepthToMinimax;
                        depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                        depthToDeath = successordepthToDeath;
                    }
                    
                    //if 2 successors lead to same minimax minimax
                    else if (successorMinimax == minimax){
                        //check if depth to minimax from current successor is smaller and that maximizer robot is alive in successor state
                        //indeed, we want to reach the minimax value as soon as possible, except if this implies to commit suicide
                        if (successordepthToDeath < depthToDeath){
                        //if (successorDepthToMinimax < depthToMinimax){//} && (*it).robots[topOfTreeTeamId].isAlive){
                            //if its the case then update the 3 values. This allows to reach faster the same minimax value
                            moveToMinimax = (*it).robots[gameState.teamId].location;
                            depthToMinimax = successorDepthToMinimax;//
                            depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                            depthToDeath = successordepthToDeath;
                        }

                        //check if depth are the same
                        else if (successordepthToDeath == depthToDeath){
                        //else if (successorDepthToMinimax == depthToMinimax) {
                            //TODO : check depth to robot alive
                            //if (successordepthToDeath > depthToDeath){
                            if (successorDepthToMinimax > depthToMinimax){
                                moveToMinimax = (*it).robots[gameState.teamId].location;
                                depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                                //depthToDeath = successordepthToDeath;
                                depthToMinimax = successorDepthToMinimax;
                            }

                            //else if (successordepthToDeath == depthToDeath){
                            else if (successorDepthToMinimax == successorDepthToMinimax){
                                //update move to minimax only if depth to first utility goes up in current successor state is smaller
                                if (successorDepthToFirstUtilGoesUp > depthToFirstUtilGoesUp && successorDepthToFirstUtilGoesUp != DUMMY_DEPTH){
                                    moveToMinimax = (*it).robots[gameState.teamId].location;
                                    depthToFirstUtilGoesUp = successorDepthToFirstUtilGoesUp;
                                }

                            }
                        }
                    }
                    //NOTE : debug purpose only                    
                    if (gameState.depthOfState == 1){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        //cout << "Hello" << endl;
                    }
                } 
                */
            }

            //check if we don't already have the minimax as utility (or a higher value)
            if (gameState.getStateUtility(topOfTreeTeamId) >= minimax)
                //if its the case then depth should be reset
                depthToMinimax = 0;
            
            //if utility goes up in this state, initiate value to 0
            if (gameState.utilGoesUp)
                depthToFirstUtilGoesUp = 0;

            if (!gameState.robots[topOfTreeTeamId].isAlive)
                depthToDeath = 0;

            return {minimax, moveToMinimax, depthToMinimax, depthToFirstUtilGoesUp, depthToDeath};
        }
    }
