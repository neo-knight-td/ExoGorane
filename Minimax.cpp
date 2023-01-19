#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include "Minimax.h"

using namespace std;

    tuple<int, int, int> Minimax :: getValueOfNextState(GameState gameState, int topOfTreeTeamId){
        int moveToMinimax;

        //if terminal state
        if (gameState.isTerminalState()){
            int depthReseted = 0;
            int dummyMove = -1;
            
            //if playing team's robot is alive
            if (gameState.robots[topOfTreeTeamId].isAlive){
                //return the state utility (playing team's robot coin score minus coin score of opponent robot)
                return {gameState.robots[topOfTreeTeamId].coinNb - gameState.robots[(topOfTreeTeamId+1)%2].coinNb, dummyMove, depthReseted};
            }
            else{
                //if friendly robot died, terminal state utility is 0
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score
                return {0, dummyMove, depthReseted};
            }
        }
        
        //if state is not terminal
        else {
            //generate the successor states from the current state
            gameState.generateSuccessors();

            //if its maximizer turn then return the value that maximizes the minimum gains of the opponent
            if (gameState.teamId == topOfTreeTeamId){
                int value = -1000;
                int depth = 1000;
                for(list<GameState>::iterator it = (gameState.successors).begin(); it != (gameState.successors).end(); it++){
                    //NOTE : "it" is an iterator (pointer). Need to add * to access successor object value
                    int successorMinimax;
                    int depthToMinimax;

                    //NOTE : debug purpose only -> bug;
                    /*
                    if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        cout << "Hello" << endl;
                    }
                    */
                    
                    std::tie(successorMinimax, std::ignore, depthToMinimax) = getValueOfNextState(*it, topOfTreeTeamId);

                    //if utility went up in this state, reset depth variable to 0
                    if (gameState.utilGoesUp)
                        depthToMinimax = 0;
                    else
                        depthToMinimax++;

                    //if minimax from current successor is higher, update all 3 values to return
                    if (successorMinimax > value){
                        value = successorMinimax;
                        moveToMinimax = (*it).robots[gameState.teamId].location;
                        depth = depthToMinimax;
                    }
                    //if 2 successors lead to same minimax value
                    else if (successorMinimax == value){
                        //check if depth to minimax from current successor is smaller
                        if (depthToMinimax < depth){
                            //if its the case then update move & depth. This allows to reach faster the same minimax value
                            moveToMinimax = (*it).robots[gameState.teamId].location;
                            depth = depthToMinimax;
                        }
                    }

                    //NOTE : debug purpose only
                    /*
                    if (gameState.depthOfState == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
                        cout << "Hello" << endl;
                    }
                    */
                    
                }

                return {value, moveToMinimax, depth};
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
                    
                    //if utility went up in this state, reset depth variable to 0
                    if (gameState.utilGoesUp)
                        depthToMinimax = 0;
                    else
                        depthToMinimax++;

                    //if minimax from current successor is lower, update all 3 values to return
                    if (successorMinimax < value){
                        value = successorMinimax;
                        moveToMinimax = (*it).robots[gameState.teamId].location;
                        depth = depthToMinimax;
                    }
                    
                    //if 2 successors lead to same minimax value
                    else if (successorMinimax == value){
                        //check if depth to minimax from current successor is bigger. This allows maximizer to reach its minimax slower 
                        if (depthToMinimax > depth){
                            moveToMinimax = (*it).robots[gameState.teamId].location;
                            depth = depthToMinimax;
                        }
                    }
                    
                }
                return {value, moveToMinimax, depth};
            }
        }
    }
