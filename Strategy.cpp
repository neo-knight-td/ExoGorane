#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
//#include "GameState.cpp"

using namespace std;

class Strategy{
    public :
        //TODO : could lead to a bug if default value are equal to real value outputed by utility of terminal state
        int const defaultValueOfNextState = -1000;
        int const defaultMoveToNextState = -1000;
        int const defaultDepthToTerminalState = -1000;

    public :
        tuple<int, int, int> exploreStateTree(GameState gameState, int teamId){
            //this function needs to be redefined in each object that inherints from the Strategy class
        }
        tuple<int, int, int> getValueOfNextState(GameState gameState, int teamId){
            int valueOfNextState = defaultValueOfNextState;
            int moveToNextState = defaultMoveToNextState;
            int depthToTerminalState = defaultDepthToTerminalState;

            //if terminal state, return current state utility value & default next move (-1)
            if (gameState.isTerminalState()){
                depthToTerminalState = gameState.depthOfState;
                //TODO : next lines to be modified. Does not implement more than 2 robots
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score
                if (gameState.robots[teamId].isAlive){
                    //return the state utility
                    return {gameState.robots[teamId].coinNb - gameState.robots[(teamId+1)%2].coinNb, moveToNextState, depthToTerminalState};
                }
                else{
                    //if friendly robot died, terminal state utility is 0
                    return {0, moveToNextState, depthToTerminalState};
                }
            }

            else{
                this->exploreStateTree();
            }

            return {valueOfNextState, moveToNextState, defaultDepthToTerminalState};
        }
};