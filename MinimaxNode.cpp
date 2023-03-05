#include <iostream>
#include <algorithm>
#include <cmath>
#include "MinimaxNode.h"
#include "Node.h"
#include "Node.cpp"

MinimaxNode::MinimaxNode(const Node &rhs, int paramDepth, int paramMaxDepth) : Node::Node(rhs){
    this->depth = paramDepth;
    this->maxDepth = paramMaxDepth;
    this->depthLastEvalDown = paramMaxDepth;
    this->depthLastEvalUp = paramMaxDepth;
}

tuple<double, char, int, int> MinimaxNode :: runMinimax(){

    //if terminal state    
    if (isTerminal())
        return {(double) getNodeValue(), constants::CHAR_DUMMY_VALUE, this->depthLastEvalUp, this->depthLastEvalDown};
    //if max depth is reached
    else if (this->depth >= this->maxDepth)
        return{(double) evaluate(), constants::CHAR_DUMMY_VALUE, this->depthLastEvalUp, this->depthLastEvalDown};

    //otherwise
    else {
        double minimax;
        char indexToMinimax;

        //if it's expectimizer's turn
        if (this->isCombatOngoing){
            
            minimax = 0;
            char childIndex = -1;
            char numberOfChildren = getDescendanceSize();
            for (char i = 0; i < numberOfChildren; i++){
                    
                double successorMinimax;

                setToNextLegalChildIndex(&childIndex);
                MinimaxNode childNode = generateChild(childIndex);

                std::tie(successorMinimax, std::ignore, std::ignore, std::ignore) = childNode.runMinimax();

                minimax += (double) successorMinimax/numberOfChildren;

            }
            
        }

        //if its maximizer turn then return the value that maximizes the minimum gains of the opponent
        else if (this->teamTakingItsTurn == constants::GORANE_TEAM){
            minimax = -2.0;

            selectFromChildren(std::greater<double>(), std::less<int>(), &minimax, &indexToMinimax, &this->depthLastEvalUp, &this->depthLastEvalDown);
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

            selectFromChildren(std::less<double>(), std::greater<int>(), &minimax, &indexToMinimax, &this->depthLastEvalUp, &this->depthLastEvalDown);
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

        return {minimax, indexToMinimax, this->depthLastEvalUp, this->depthLastEvalDown};
    }
}

//selectFromChildren contains the logical core of Minimax. Based on the state of the game and the team taking the turn, it will return which successor
//is to be chosen. This function can be used for both the maximizer and the minimizer. Only the comparators will vary depending on which one is playing.
void MinimaxNode :: selectFromChildren(std::function<bool(double,double)> comparatorGreaterLesser, std::function<bool(int,int)> comparatorLesserGreater, double *minimax,
    char *indexToMinimax, int *pDepthLastEvalUp, int *pDepthLastEvalDown){
    
    char childIndex = -1;
    //NOTE : TS
    //char numberOfChildren = 1;//getDescendanceSize();
    char numberOfChildren = getDescendanceSize();
    //MinimaxNode *pSelectedChildNode;
    for (char i = 0; i < numberOfChildren; i++){
            
        double successorMinimax;
        int successorDepthToLastEvalUp;
        int successorDepthToLastEvalDown;

        //NOTE : TS
        //int locationIncrement = 5;//getLocationIncrement(&childIndex);
        setToNextLegalChildIndex(&childIndex);
        //int locationIncrement = getLocationIncrement(&childIndex);
        MinimaxNode childNode = generateChild(childIndex);
        std::tie(successorMinimax, std::ignore, successorDepthToLastEvalUp, successorDepthToLastEvalDown) = childNode.runMinimax();

        //NOTE : debug purpose only -> bug
        if (this->depth == 0){//(gameState.depthOfState == 2 && gameState.robots[1].location == 23){
            //cout << "Hello" << endl;
        }
                                            
        //if minimax from current successor is higher, update all values to return
        if (comparatorGreaterLesser(successorMinimax,*minimax)){
            *minimax = successorMinimax;
            *indexToMinimax = childIndex;
            *pDepthLastEvalUp = successorDepthToLastEvalUp;
            *pDepthLastEvalDown = successorDepthToLastEvalDown;
        }
        
        //if 2 successors lead to same minimax
        else if (successorMinimax == *minimax){
            if(this->teamTakingItsTurn == constants::GORANE_TEAM){
                
                if (successorDepthToLastEvalUp < *pDepthLastEvalUp){
                    *indexToMinimax = childIndex;
                    *pDepthLastEvalUp = successorDepthToLastEvalUp;
                    *pDepthLastEvalDown = successorDepthToLastEvalDown;
                }                
            }

            else if(this->teamTakingItsTurn == constants::ENEMY_TEAM){

                if (successorDepthToLastEvalDown < *pDepthLastEvalDown){
                    *indexToMinimax = childIndex;
                    *pDepthLastEvalUp = successorDepthToLastEvalUp;
                    *pDepthLastEvalDown = successorDepthToLastEvalDown;
                }   
            }
        }
    }

    /*

    //TODO : implement kind of util goes up ! idea ? add feature as closest manhattan distance to next coin as eval
    //check if we don't already have the minimax as utility (or higher)
    if(comparatorGreaterLesser((double) evaluate(),pSelectedChildNode->evaluate())){
        //if its the case then depth should be reset
        //*depthToMinimax = 0;
        *minimax = (double) (*minimax)*getDepthRegressionFactor(1);
    }

    */


}

MinimaxNode MinimaxNode::generateChild(char childIndex){

    //copy node (and adapt depth in it)
    MinimaxNode childNode(*this, this->depth+1, this->maxDepth);
    //configure child node
    childNode.configureChild(childIndex);

    if(childNode.evaluate() > evaluate()){
        childNode.depthLastEvalUp = childNode.depth;
        childNode.depthLastEvalDown = this->depthLastEvalDown;
    }
    else if(childNode.evaluate() < evaluate()){
        childNode.depthLastEvalDown = childNode.depth;
        childNode.depthLastEvalUp = this->depthLastEvalUp;
    }
    else{
        childNode.depthLastEvalDown = this->depthLastEvalDown;
        childNode.depthLastEvalUp = this->depthLastEvalUp;
    }

    return childNode;
}

double MinimaxNode::getDepthRegressionFactor(int paramDepth){
    return (double) pow((double) pow(2,(double) 1/(2*(this->maxDepth -1 ))), paramDepth);
}
