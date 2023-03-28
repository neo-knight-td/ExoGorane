#include "Simulator.h"
#include "Node.h"
#include <experimental/random>

//default constructor for the Simulator. Initiates a maze based on empty maze in parameters, sets coins in all squares (except thos on which a robot lies),
//generates the robots, teams and finally the node object (stores it as class member)
Simulator::Simulator(const char *emptyMaze, int paramGasInterval){

    const int GORANE1_DEFAULT_LOCATION = NB_OF_MAZE_SQUARES - MAZE_WIDTH/2;
    const int GORANE2_DEFAULT_LOCATION = NB_OF_MAZE_SQUARES/2 - 1;
    const int ENEMY1_DEFAULT_LOCATION = MAZE_WIDTH/2 - 1;
    const int ENEMY2_DEFAULT_LOCATION = NB_OF_MAZE_SQUARES/2;

    char maze[NB_OF_MAZE_SQUARES];
    for (int i = 0; i < NB_OF_MAZE_SQUARES; i++){
        maze[i] = emptyMaze[i];

        //add a coin on all squares except those on which a robot lies
        if (i != ENEMY1_DEFAULT_LOCATION && i != ENEMY2_DEFAULT_LOCATION && i != GORANE1_DEFAULT_LOCATION && i != GORANE2_DEFAULT_LOCATION)
             maze[i] += COIN_MASK;
    }

    struct Robot G1 = {GORANE1_DEFAULT_LOCATION, 0, true};
    struct Robot G2 = {GORANE2_DEFAULT_LOCATION, 0, true};
    struct Robot E1 = {ENEMY1_DEFAULT_LOCATION, 0, true};
    struct Robot E2 = {ENEMY2_DEFAULT_LOCATION, 0, true};

    Robot goraneRobots[NB_OF_ROBOTS_PER_TEAMS];
    Robot enemyRobots[NB_OF_ROBOTS_PER_TEAMS];

    goraneRobots[GORANE1_INDEX] = G1;
    goraneRobots[GORANE2_INDEX] = G2;
    enemyRobots[ENEMY1_INDEX] = E1;
    enemyRobots[ENEMY2_INDEX] = E2;

    Team goraneTeam(goraneRobots);
    Team enemyTeam(enemyRobots);

    Team teams[NB_OF_TEAMS];

    teams[GORANE_TEAM] = goraneTeam;
    teams[ENEMY_TEAM] = enemyTeam;

    //init node
    this->node = Node(maze, teams, ENEMY_TEAM, paramGasInterval);

    //print it
    this->node.printNode();
}

//simulate the environment if selectedChildIndex is chosen, returns 0 if simulation reaches it's end
//NOTE : code does not check if selectedChildIndex is legaal
bool Simulator::iterate(char selectedChildIndex){
    bool simulationResult = true;

    if (!this->node.isTerminal())
    {
        vector<string> robotNames = {"E","R","G","H"};
        string robotName = robotNames[(int) this->node.teamTakingItsTurn*2 + (int) this->node.teams[this->node.teamTakingItsTurn].robotTakingItsTurn];
        std:cout << "Turn to " << robotName << " robot." << endl;

        std::cout << "Robot " << robotName << " should move to "<< this->node.getLocationIncrement(selectedChildIndex) << "." << std::endl;

        //update node
        this->node.configureChild(selectedChildIndex);

        std::cout << "Time until next gas closure is " << this->node.timeUntilGasClosing << endl;

        //print new node
        this->node.printNode();

        //check if combat is ongoing
        if (this->node.isCombatOngoing){
            //random kill one of the robots in combat
            selectedChildIndex = std::experimental::randint(0, 1);

            std::cout << "Combat is ongoing !" << endl;

            //update node
            this->node.configureChild(selectedChildIndex);

            //print new node
            this->node.printNode();
        }

    }

    //check if node is terminal (not else if because can become terminal after configure child is called)
    if(this->node.isTerminal()){
        simulationResult = false;

        std::cout << "Game Over" << endl;
        std::cout << "Result is " << this->node.getNodeValue() << endl;
        std::cout << "Score Gorane Team is " << this->node.teams[1].coinNb << endl;
        std::cout << "Score Enemy Team is " << this->node.teams[0].coinNb << endl;
    }

    return simulationResult;
}