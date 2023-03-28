#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "MazeStore.h"
#include "Node.h"

class Simulator
{   
    public: 
        Node node;
    public :
        Simulator(const char *paramMaze, int paramGasInterval);
        bool iterate(char selectedChildIndex);
};

#endif