#include "Constants.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <list>
#include <tuple>
#include <cmath>
#include <chrono>
//#include "MCTSNode.h"
//#include "MCTSNode.cpp"
//#include "AStarNode.h"
#include "AStarNode.cpp"
#include "MazeStore.h"
#include "Simulator.h"
#include "Simulator.cpp"

int main()
{
    std::cout << "Hello Gorane !" << std::endl;

    //Create a Maze Store
    MazeStore mazeStore;
    //Create Simulator
    Simulator simulator(mazeStore.RegularMaze, 5);
    
    int simIsOngoing = true;
    while(simIsOngoing){
        char selectedIndex;

        //run a search algorithm (e.g. A Star)
        //TODO : encapsulate code once fully developped
        //--------------------------------------------------------------------------
        AStarNode buffNode = AStarNode(simulator.node, nullptr, 0, true);
        buffNode.killAllRobotExceptOneTakingTurn();
        std::tie(std::ignore, selectedIndex) = buffNode.runAStar();
        //if A star returns no solution, pick one random move
        if (selectedIndex == -1){
            selectedIndex = std::experimental::randint(-1, BRANCHING_FACTOR - 2);
            buffNode.getDescendanceSize();
            buffNode.setToNextLegalChildIndex(&selectedIndex);
        }
        //--------------------------------------------------------------------------

        //input child index in simulator
        simIsOngoing = simulator.iterate(selectedIndex);
    }
}