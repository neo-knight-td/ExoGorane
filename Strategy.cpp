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
        int const defaultValueOfNextState = -1;
        int const defaultMoveToNextState = -1;

    public :
        tuple<int, int> getValueOfNextState(GameState gameState, int teamId){
            int valueOfNextState = defaultValueOfNextState;
            int moveToNextState = defaultMoveToNextState;

            //if terminal state, return current state utility value & default next move (-1)
            if (gameState.isTerminalState()){
                //TODO : next lines to be modified. Does not implement more than 2 robots
                //TODO : ask on ExoLegend Discord if coins of dead robot count in team score
                if (gameState.robots[teamId].isAlive){
                    //return the state utility (nb of coins gathered)
                    return {gameState.robots[teamId].coinNb, moveToNextState};
                }
                else{
                    //if friendly robot died, terminal state utility is 0
                    return {0, moveToNextState};
                }
            }

            return {valueOfNextState, moveToNextState};
        }
};