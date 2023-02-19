#include <iostream>
#include <algorithm>
#include "MinimaxNode.h"
#include "Node.h"
#include "Node.cpp"

MinimaxNode::MinimaxNode(char *paramMaze, Robot *paramRobots, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing, int paramDepth, int paramMaxDepth) : Node::Node(paramMaze, paramRobots, paramTeamTakingItsTurn, paramTimeUntilGasClosing){
    this->depth = paramDepth;
    this->maxDepth = paramMaxDepth;
}

//getValueOfNextState is a recursive function that will explore the tree of states and return the maximum utility
//value reachable from the current game state. It will also provide the move required to reach that value & the depth
//at which that value appears in the tree
tuple<double, int, int> MinimaxNode :: runMinimax(){

    //if terminal state    
    if (isTerminal())
        return {getNodeValue(), constants::CHAR_DUMMY_VALUE, 0};
    //if max depth is reached
    else if (this->depth >= this->maxDepth)
        return{evaluate(), constants::CHAR_DUMMY_VALUE, 0};

    //otherwise
    else {
        double minimax;
        int moveToMinimax;
        int depthToMinimax;

        //generate the successor states from the current state
        //MinimaxNode::generateChildren();

        //if its maximizer turn then return the value that maximizes the minimum gains of the opponent
        if (this->teamTakingItsTurn == constants::GORANE_TEAM){
            minimax = -2.0;
            depthToMinimax= 1000;

            selectFromChildren(std::greater<int>(), std::less<int>(), &minimax, &moveToMinimax, &depthToMinimax);
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
        else if (this->teamTakingItsTurn == constants::ENEMY_TEAM) {
            minimax = 2.0;
            depthToMinimax = -1000;

            selectFromChildren(std::less<int>(), std::greater<int>(), &minimax, &moveToMinimax, &depthToMinimax);
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

        return {minimax, moveToMinimax, depthToMinimax};
    }
}

//selectFromChildren contains the logical core of Minimax. Based on the state of the game and the team taking the turn, it will return which successor
//is to be chosen. This function can be used for both the maximizer and the minimizer. Only the comparators will vary depending on which one is playing.
void MinimaxNode :: selectFromChildren(std::function<bool(int,int)> comparatorGreaterLesser, std::function<bool(int,int)> comparatorLesserGreater, double *minimax,
    int *moveToMinimax, int *depthToMinimax){
    
    char childIndex = 0;
    char numberOfChildren = getDescendanceSize();
    for (char i = 0; i < numberOfChildren; i++){
            
        double successorMinimax;
        int successorDepthToMinimax;

        int locationIncrement = getLocationIncrement(&childIndex);
        MinimaxNode childNode = generateMinimaxNode(locationIncrement);
        std::tie(successorMinimax, std::ignore, successorDepthToMinimax) = childNode.runMinimax();
        successorDepthToMinimax++;

        //NOTE : debug purpose only -> bug
        if (this->depth == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
            //cout << "Hello" << endl;
        }
                                            
        //if minimax from current successor is higher, update all values to return
        if (comparatorGreaterLesser(successorMinimax,*minimax)){
            *minimax = successorMinimax;
            *moveToMinimax = locationIncrement;
            *depthToMinimax = successorDepthToMinimax;
        }
        //if 2 successors lead to same minimax
        else if (successorMinimax == *minimax){
            //only update if current child node leads to minimax faster (if depth is smaller)
            if (comparatorLesserGreater(successorDepthToMinimax, *depthToMinimax)){
                *moveToMinimax = locationIncrement;
                *depthToMinimax = successorDepthToMinimax;
            }
        }
    }
}

MinimaxNode MinimaxNode::generateMinimaxNode(int locationIncrement){

    //copy node (and adapt depth in it)
    MinimaxNode childNode(this->maze, this->robots, this->teamTakingItsTurn, this->timeUntilGasClosing, this->depth+1, this->maxDepth);
    //connfigure child node
    childNode.configureChild(locationIncrement);

    return childNode;
}
