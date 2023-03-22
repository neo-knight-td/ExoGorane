#include <iostream>
#include <algorithm>
#include "Node.h"

using namespace std;

// default constructor (should only be called when setting up the game)
Node::Node(char *paramMaze, Team *paramTeams, bool paramTeamTakingItsTurn, int paramTimeUntilGasClosing)
{
    // copy maze
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++)
        this->maze[i] = paramMaze[i];
    // copy teams

    // TODO : watch this constructor
    for (int j = 0; j < game::NB_OF_TEAMS; j++)
    {
        this->teams[j] = paramTeams[j];
    }

    this->teamTakingItsTurn = paramTeamTakingItsTurn;
    this->timeUntilGasClosing = paramTimeUntilGasClosing;
    // this->coinsOnGround = game::NB_OF_COINS;
    countCoinsOnGround();
}

//copy constructor (will copy everything from rhs in this node)
Node::Node(const Node &rhs){

    // copy maze
    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++)
        this->maze[i] = rhs.maze[i];
    // copy teams

    // TODO : watch this constructor
    for (int j = 0; j < game::NB_OF_TEAMS; j++)
    {
        this->teams[j] = rhs.teams[j];
    }
    

    this->teamTakingItsTurn = rhs.teamTakingItsTurn;
    this->timeUntilGasClosing = rhs.timeUntilGasClosing;
    this->gasClosures = rhs.gasClosures;
    this->coinsOnGround = rhs.coinsOnGround;
    //countCoinsOnGround();

    this->isCombatOngoing = rhs.isCombatOngoing;
    //copy robots in combat
    for (int k = 0; k < 2; k++)
    {
        this->robotsInCombat[k] = rhs.robotsInCombat[k];
    }
}

void Node::configureRobotsLocationInChildNode(int locationIncrement)
{
    // save robot taking turn (because will be re used multiple times in the function)
    bool robotTakingItsTurn = this->teams[this->teamTakingItsTurn].robotTakingItsTurn;

    // adapt the robot's previous & acutal location in child node
    this->teams[this->teamTakingItsTurn].robots[robotTakingItsTurn].previousLocation = this->teams[this->teamTakingItsTurn].robots[robotTakingItsTurn].location;
    this->teams[this->teamTakingItsTurn].robots[robotTakingItsTurn].location += locationIncrement;

    // save new location of robot taking the turn (because will be re used multiple times in the function)
    int robotLocation = this->teams[this->teamTakingItsTurn].robots[robotTakingItsTurn].location;

    int otherTeamFirstRobotLocation = this->teams[!this->teamTakingItsTurn].robots[false].location;
    bool otherTeamFirstRobotisAlive = this->teams[!this->teamTakingItsTurn].robots[false].isAlive;
    int otherTeamSecondRobotLocation = this->teams[!this->teamTakingItsTurn].robots[true].location;
    bool otherTeamSecondRobotisAlive = this->teams[!this->teamTakingItsTurn].robots[false].isAlive;

    //if new robot's position coincides with position of first robot from other team (and it's alive)
    if(otherTeamFirstRobotisAlive && robotLocation == otherTeamFirstRobotLocation){
        //combat is ongoing
        this->isCombatOngoing = true;
        //fill in robots in combat
        this->robotsInCombat[this->teamTakingItsTurn] = robotTakingItsTurn;
        this->robotsInCombat[!this->teamTakingItsTurn] = false;

    }
    //else if new robot's position coincides with position of second robot from other team (and it's alive)
    else if(otherTeamSecondRobotisAlive && robotLocation == otherTeamSecondRobotLocation){
        //combat is ongoing
        this->isCombatOngoing = true;
        //fill in robots in combat
        this->robotsInCombat[this->teamTakingItsTurn] = robotTakingItsTurn;
        this->robotsInCombat[!this->teamTakingItsTurn] = true;
    }

    if (robotLocation < 0)
        cout << "ERROR : Initializing robot at negative location" << endl;
}

void Node::configureCoinsInChildNode()
{
    // adapt the coins on ground in child node only if we find a coin on the robot's next location
    /*
    if (this->maze[this->robots[this->teamTakingItsTurn].location] & constants::COIN_MASK){
        this->robots[this->teamTakingItsTurn].coinNb += 1;
        this->coinsOnGround--;
        this->maze[this->robots[this->teamTakingItsTurn].location] += -constants::COIN_MASK;
    }
    */
    if (this->maze[this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].location] & constants::COIN_MASK)
    {
        this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].coinNb += 1;
        this->teams[this->teamTakingItsTurn].updateCoins();
        this->coinsOnGround--;
        this->maze[this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].location] += -constants::COIN_MASK;
    }
}

void Node::configureTimeInChildNode()
{

    //NOTE : hard coded for 2 robots

    // if both teams are alive
    if (this->teams[constants::ENEMY_TEAM].isAlive && this->teams[constants::GORANE_TEAM].isAlive){
        
        bool secondRobotGoraneIsAlive =  this->teams[constants::GORANE_TEAM].robots[constants::GORANE2_INDEX].isAlive;
        bool robotTakingTurn = this->teams[this->teamTakingItsTurn].robotTakingItsTurn;

        //if second robot from gorane team is alive
        if (secondRobotGoraneIsAlive){
            //decrease time only when he has its turn
            if (this->teamTakingItsTurn == constants::GORANE_TEAM && robotTakingTurn == constants::GORANE2_INDEX){
                this->timeUntilGasClosing = this->timeUntilGasClosing - 1;
            }
        }
        //if second robot from gorane team is dead
        else {
            //decrease time only when first robot from the team has its turn
            if (this->teamTakingItsTurn == constants::GORANE_TEAM && robotTakingTurn == constants::GORANE1_INDEX){
                this->timeUntilGasClosing = this->timeUntilGasClosing - 1;
            }
        }
    }
    //if only one team is alive
    else{

        bool secondRobotIsAlive =  this->teams[this->teamTakingItsTurn].robots[true].isAlive;
        bool robotTakingTurn = this->teams[this->teamTakingItsTurn].robotTakingItsTurn;

        //if second robot from team alive is alive
        if (secondRobotIsAlive){
            //decrease time only when he has its turn
            if (robotTakingTurn == true){
                this->timeUntilGasClosing = this->timeUntilGasClosing - 1;
            }
        }
        //if second robot from team alive is dead
        else {
            //decrease time
            this->timeUntilGasClosing = this->timeUntilGasClosing - 1;
        }
    }

        /*
        // TODO : code in case 4 robots alive, 3, 2, 1...
        if (!this->teamTakingItsTurn)
        {
            if (!this->teams[this->teamTakingItsTurn].robotTakingItsTurn)
                // adapt time until gas closes in child node (unless reaches 0, then close the gas)
                // TODO : time should be decreased only once on two when both robots are alive
                this->timeUntilGasClosing = this->timeUntilGasClosing - 1;
        }
    }
    // otherwise, increase time independently of the depth
    else
        this->timeUntilGasClosing = this->timeUntilGasClosing - 1;
        */
}

void Node::configureGasInChildNode()
{

    // TODO : if necessarry, close the gas
    if (this->timeUntilGasClosing == 0)
    {
        this->gasClosures++;
        // close the gas !
        // flip the gas bit inside all squares that are in the gas
        for (int h = 0; h < game::NB_OF_MAZE_SQUARES; h++)
        {
            // erase possible moves for first column(s) of the maze
            if (h < game::MAZE_WIDTH * this->gasClosures)
            {
                if (!(this->maze[h] & constants::GAS_MASK))
                {
                    this->maze[h] += constants::GAS_MASK;
                }
            }

            // erase possible moves for first line(s) of the maze
            else if (h % game::MAZE_WIDTH < this->gasClosures)
            {
                if (!(this->maze[h] & constants::GAS_MASK))
                {
                    this->maze[h] += constants::GAS_MASK;
                }
            }

            // erase possible moves for last line(s) of the maze
            else if (h % game::MAZE_WIDTH >= game::MAZE_WIDTH - this->gasClosures)
            {
                if (!(this->maze[h] & constants::GAS_MASK))
                {
                    this->maze[h] += constants::GAS_MASK;
                }
            }

            // erase possible moves for the last column(s) of the maze
            else if (h > game::MAZE_WIDTH * game::MAZE_WIDTH - this->gasClosures * game::MAZE_WIDTH)
            {
                if (!(this->maze[h] & constants::GAS_MASK))
                {
                    this->maze[h] += constants::GAS_MASK;
                }
            }
        }
        this->timeUntilGasClosing = game::GAS_CLOSING_INTERVAL;
    }
}

void Node::configureRobotsLivesInChildNode()
{
        // adapt robots life if next location is in the gaz
        // NOTE : next 4 lines cost about 100 nanoseconds (on Thomas Desktop)
        // TODO : optimize these 4 lines
        /*
        for (int k=0; k< game::NB_OF_ROBOTS; k++){
            if(this->maze[this->robots[k].location] & constants::GAS_MASK)
                this->robots[k].isAlive = false;
        }
        */

    for (int k = 0; k < game::NB_OF_TEAMS; k++)
    {
        for (int l = 0; l < game::NB_OF_ROBOTS_PER_TEAM; l++)
        {
            if (isSquareInTheGas(this->teams[k].robots[l].location))
                this->teams[k].robots[l].isAlive = false;
        }
        this->teams[k].updateLives();
    }
}

void Node::configureRobotTakingTurnInChildNode()
{
    /*
    //adapt team in successor state only if other team is alive
    if (this->robots[!(this->teamTakingItsTurn)].isAlive){
        this->teamTakingItsTurn = !(this->teamTakingItsTurn);
    }
    */
    /*
    // adapt team in successor state only if other team is alive
    if (this->teams[!(this->teamTakingItsTurn)].isAlive)
    {
        this->teamTakingItsTurn = !(this->teamTakingItsTurn);
    }

    // inside team taking its turn, change robot taking its turn (only if its alive)
    if (this->teams[this->teamTakingItsTurn].robots[!(this->teams[this->teamTakingItsTurn].robotTakingItsTurn)].isAlive)
        this->teams[this->teamTakingItsTurn].robotTakingItsTurn = !(this->teams[this->teamTakingItsTurn].robotTakingItsTurn);
    */
    bool secondRobotFromCurrentTeamIsAlive =  this->teams[this->teamTakingItsTurn].robots[!(this->teams[this->teamTakingItsTurn].robotTakingItsTurn)].isAlive;
    // inside team taking its turn, if robot taking turn is first robot & other robot from team is alive
    if(!(this->teams[this->teamTakingItsTurn].robotTakingItsTurn) && secondRobotFromCurrentTeamIsAlive){
        //switch robot taking turn in the team
        this->teams[this->teamTakingItsTurn].robotTakingItsTurn = true;
    }
    //otherwise change team taking turn (but only if other team is alive !)
    else if (this->teams[!(this->teamTakingItsTurn)].isAlive)
    {
        this->teamTakingItsTurn = !(this->teamTakingItsTurn);

        bool firstRobotFromCurrentTeamIsAlive =  this->teams[this->teamTakingItsTurn].robots[false].isAlive;

        //if first robot from current team is alive, give him the turn
        if(firstRobotFromCurrentTeamIsAlive){
            this->teams[this->teamTakingItsTurn].robotTakingItsTurn = false;
        }
        //otherwise, give it to the next robot (which it alive as team is alive & first robot is dead)
        else{
            this->teams[this->teamTakingItsTurn].robotTakingItsTurn = true;
        }
    }
}
    

void Node::configureChild(char childIndex)
{
    //if no combat is ongoing
    if (!this->isCombatOngoing){
        int locationIncrement = getLocationIncrement(childIndex);

        configureRobotsLocationInChildNode(locationIncrement);
        configureCoinsInChildNode();
        configureTimeInChildNode();
        configureGasInChildNode();
        configureRobotsLivesInChildNode();
        configureRobotTakingTurnInChildNode();
    }
    else{
        //kill a robot
        //NOTE : for debug purposes, next lines might are commented
        this->teams[(childIndex+1)%2].robots[this->robotsInCombat[(childIndex+1)%2]].isAlive = false;
        this->teams[(childIndex+1)%2].updateLives();

        //update team taking turn
        configureRobotTakingTurnInChildNode();
        
        //Reset combat ongoing bool
        this->isCombatOngoing = false;
    }

}

// returns the number of children from the current node (number of legal moves from the current node)
char Node::getDescendanceSize()
{
    //if state is terminal, descendance size is zero
    if (this->isTerminal()){
        return 0;
    }

    //if current node is a lottery node (a combat is ongoing), there is a fixed number of oucomes possible
    if (this->isCombatOngoing){
        //NOTE : let's suppose there are two outcomes to a combat. Either gorane or enemy robot dies !
        //TODO : may be interesting to think of a 3rd & 4th oucome : both die or both stay alive

        return 2;
    }

    //if no fight is ongoing, just return the number of moves that are possible
    else{
        char descendanceSize = 0;
        // retrieve maze square on which robot taking its turn is located
        char mazeSquare = this->maze[this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].location];

        if ((mazeSquare & constants::UP_MASK))
        {
            descendanceSize++;
        }

        if (mazeSquare & constants::DOWN_MASK)
        {
            descendanceSize++;
        }

        if (mazeSquare & constants::LEFT_MASK)
        {
            descendanceSize++;
        }

        if (mazeSquare & constants::RIGHT_MASK)
        {
            descendanceSize++;
        }

        //if in tunnel and robot has a valid previous location 
        if (descendanceSize == 2 && this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].previousLocation >= 0){
            //record that robot cannot turn back in the tunnel
            //TODO : think back where this line should be added (MCTS does not call getDescendanceSize)
            //TODO : add conditions before adding this

            //NOTE : next two lines (if commented) are setting cannot turn back to off !
            //this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].cannotTurnBack = true;
            //return 1;

            return descendanceSize;
        }

        else{
            //record that robot can turn back again
            this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].cannotTurnBack = false;
            return descendanceSize;
        }
    }

}

// this function sets value of child index to the next legal child index
void Node::setToNextLegalChildIndex(char *pChildIndex)
{ 

    if (this->isCombatOngoing){
        if (*pChildIndex <= -1){
            *pChildIndex = 0;
        }

        else if (*pChildIndex <= 0){
            *pChildIndex = 1;
        }

        else {
            std::cout << "ERROR : trying to access child that does not exist when Combat is ongoing." << std::endl;
        }

        return;
    }

    else if(this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].cannotTurnBack){

        // current location of robot taking its turn
        int robotLocation = this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].location;
        // retrieve maze square on which robot taking its turn is located
        char mazeSquare = this->maze[robotLocation];
        // current previous location of robot taking its turn
        int robotPreviousLocation = this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].previousLocation;

        // TODO : add default child (child index 0)
        if (*pChildIndex <= 0 && (mazeSquare & constants::UP_MASK) && (robotLocation -1 != robotPreviousLocation))
        {
            *pChildIndex = 1;
        }

        else if (*pChildIndex <= 1 && (mazeSquare & constants::DOWN_MASK) && (robotLocation +1  != robotPreviousLocation))
        {
            *pChildIndex = 2;
        }

        else if (*pChildIndex <= 2 && (mazeSquare & constants::LEFT_MASK) && (robotLocation - game::MAZE_WIDTH != robotPreviousLocation))
        {
            *pChildIndex = 3;
        }

        else if (*pChildIndex <= 3 && (mazeSquare & constants::RIGHT_MASK) && (robotLocation + game::MAZE_WIDTH != robotPreviousLocation))
        {
            *pChildIndex = 4;
        }

        // if previous index was equal to 4, reset value of child Index and call function again (required for MCTS)
        else if (*pChildIndex <= 4)
        {
            *pChildIndex = -1;
            setToNextLegalChildIndex(pChildIndex);
        }
        else
        {
            std::cout << "ERROR : trying to access child that does not exist." << std::endl;
        }
    }

    else{

        // current location of robot taking its turn
        int robotLocation = this->teams[this->teamTakingItsTurn].robots[this->teams[this->teamTakingItsTurn].robotTakingItsTurn].location;
        // retrieve maze square on which robot taking its turn is located
        char mazeSquare = this->maze[robotLocation];

        // TODO : add default child (child index 0)
        if (*pChildIndex <= 0 && (mazeSquare & constants::UP_MASK))
        {
            *pChildIndex = 1;
        }

        else if (*pChildIndex <= 1 && (mazeSquare & constants::DOWN_MASK))
        {
            *pChildIndex = 2;
        }

        else if (*pChildIndex <= 2 && (mazeSquare & constants::LEFT_MASK))
        {
            *pChildIndex = 3;
        }

        else if (*pChildIndex <= 3 && (mazeSquare & constants::RIGHT_MASK))
        {
            *pChildIndex = 4;
        }
        // if previous index was equal to 4, reset value of child Index and call function again (required for MCTS)
        else if (*pChildIndex <= 4)
        {
            *pChildIndex = -1;
            setToNextLegalChildIndex(pChildIndex);
        }
        else
        {
            std::cout << "ERROR : trying to access child that does not exist." << std::endl;
        }
        
    }

}


// this function return the location increment required to reach child node at index childIndex. The function supposes that child at child index is legal. This 
// function is only called on non-lottery nodes
int Node::getLocationIncrement(char childIndex)
{
    // TODO : add default child (child index 0)

    if (childIndex == 1)
        return -1;

    else if (childIndex == 2)
        return 1;

    else if (childIndex == 3)
        return -game::MAZE_WIDTH;

    else if (childIndex == 4)
        return game::MAZE_WIDTH;

    else{
        std::cout << "ERROR : trying to access child that does not exist." << std::endl;
        return -1000;
    }
}

bool Node::isTerminal()
{
    //TODO if more than 50 % of coins on the ground belong to a team, state is terminal
    
    // if no more coins on the ground
    if (this->coinsOnGround == 0)
        return true;
    // if all robots are dead
    else if (areAllRobotsDead())
        return true;
    else
        return false;
}

bool Node::areAllRobotsDead(){
    return (!this->teams[constants::GORANE_TEAM].isAlive && !this->teams[constants::ENEMY_TEAM].isAlive);
}

void Node::countCoinsOnGround()
{
    int count = 0;

    for (int i = 0; i < game::NB_OF_MAZE_SQUARES; i++)
    {
        if (this->maze[i] & constants::COIN_MASK)
            count++;
    }

    this->coinsOnGround = count;
}

double Node::evaluate()
{
    // temporary evaluation function
    // cout << "hello there" << endl;
    return 0.5 + (double)(this->teams[constants::GORANE_TEAM].coinNb - this->teams[constants::ENEMY_TEAM].coinNb) / (2 * game::NB_OF_COINS);
}

double Node::getNodeValue()
{

    // if G collected more coins than E, G wins (value is 1)
    if (this->teams[constants::GORANE_TEAM].coinNb > this->teams[constants::ENEMY_TEAM].coinNb)
        return constants::MAX_NODE_VALUE;
    else if (this->teams[constants::GORANE_TEAM].coinNb == this->teams[constants::ENEMY_TEAM].coinNb)
        return constants::DRAW_NODE_VALUE;
    // if G collected less coins (or draw), G loses (value is 0)
    else
        return constants::MIN_NODE_VALUE;
}

bool Node::isSquareInTheGas(int location){
    bool isSquareInTheGas = false;

    if (this->maze[location] & constants::GAS_MASK)
        isSquareInTheGas = true;

    return isSquareInTheGas;
}

void Node::printNode()
{
    // TODO solve display bug
    string outerWall = "*";
    string innerVWall = "|";
    string innerHWall = "-";
    string blank = " ";
    string gaz = "x";
    string aliveGoraneRobot = "G";
    string aliveEnemyRobot = "E";
    string deadGoraneRobot = "g";
    string deadEnemyRobot = "e";
    string aliveG1 = "G";
    string aliveG2 = "H";
    string aliveE1 = "E";
    string aliveE2 = "R";
    string aliveRobots[4] = {aliveE1, aliveE2, aliveG1, aliveG2};
    string deadG1 = "g";
    string deadG2 = "h";
    string deadE1 = "e";
    string deadE2 = "r";
    string deadRobots[4] = {deadE1, deadE2, deadG1, deadG2};
    string coin = ".";
    string coinInGas = "€";

    // only works with a squared number of mazes
    int dim_h = game::MAZE_WIDTH;
    int dim_v = game::MAZE_WIDTH;

    // first line is line of outer walls
    // draw outer walls at tile intersections only → i+=2
    for (int i = 0; i < (dim_h * 2 + 1); i += 2)
        std::cout << outerWall << blank;
    std::cout << std::endl;

    for (int i = 1; i < (dim_v * 2); i++)
    {
        // draw outer walls at tile intersections only
        if (i % 2 == 0)
        {
            std::cout << outerWall;
        }
        else
        {
            std::cout << blank;
        }

        for (int j = 0; j < (dim_h * 2 + 1); j++)
        {
            // if i is odd, print line with square ids or vertical walls
            if (i % 2 != 0)
            {
                // if j is odd, you are in a square
                if (j % 2 != 0)
                {
                    int currentSquareId = (i - 1) / 2 + (j - 1) / 2 * dim_v;
                    bool currentSquareIdShouldBeBlank = true;

                    // print robots
                    for (int i = 0; i < game::NB_OF_TEAMS; i++)
                    {
                        for (int j = 0; j < game::NB_OF_ROBOTS_PER_TEAM; j++)
                        {
                            if (this->teams[i].robots[j].location == currentSquareId)
                            {
                                currentSquareIdShouldBeBlank = false;
                                if (this->teams[i].robots[j].isAlive)
                                    std::cout << aliveRobots[i * game::NB_OF_TEAMS + j];
                                else
                                    std::cout << deadRobots[i * game::NB_OF_TEAMS + j];
                            }
                        }
                    }
                    /*
                    if (game::NB_OF_ROBOTS == 2){
                        //we print Gorane if it is located in the current square
                        if (this->robots[constants::GORANE_TEAM].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::GORANE_TEAM].isAlive)
                                std::cout << aliveGoraneRobot;
                            else
                                std::cout << deadGoraneRobot;
                        }
                        //we print Enemy if it is located in the current square
                        //NOTE : if Enemy & Robot have same location, Gorane will be printed
                        else if(this->robots[constants::ENEMY_TEAM].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::ENEMY_TEAM].isAlive)
                                std::cout << aliveEnemyRobot;
                            else
                                std::cout << deadEnemyRobot;
                        }
                    }

                    else if (game::NB_OF_ROBOTS == 4){
                        //we print G1 if it is located in the current square
                        if (this->teams[constants::GORANE_TEAM].robots[constants::GORANE1_INDEX].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::GORANE1_INDEX].isAlive)
                                std::cout << aliveG1;
                            else
                                std::cout << deadG1;
                        }

                        //we print G2 if it is located in the current square
                        else if (this->teams[constants::GORANE_TEAM].robots[constants::GORANE2_INDEX].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::GORANE2_INDEX].isAlive)
                                std::cout << aliveG2;
                            else
                                std::cout << deadG2;
                        }

                        //we print E1 if it is located in the current square
                        else if (this->teams[constants::ENEMY_TEAM].robots[constants::ENEMY1_INDEX].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::ENEMY1_INDEX].isAlive)
                                std::cout << aliveE1;
                            else
                                std::cout << deadE1;
                        }

                        //we print E2 if it is located in the current square
                        else if (this->robots[constants::ENEMY2_INDEX].location == currentSquareId){
                            currentSquareIdShouldBeBlank = false;
                            if(this->robots[constants::ENEMY2_INDEX].isAlive)
                                std::cout << aliveE2;
                            else
                                std::cout << deadE2;
                        }
                    }
                    */
                    if (currentSquareIdShouldBeBlank)
                    {

                        // if no robot is to printed, maybe a coin should be printed
                        if (this->maze[currentSquareId] & constants::COIN_MASK)
                        {
                            currentSquareIdShouldBeBlank = false;
                            if (this->maze[currentSquareId] & constants::GAS_MASK)
                                std::cout << coinInGas;
                            else
                                std::cout << coin;
                        }

                        // if no robot is to printed, maybe gas should be printed
                        else if (this->maze[currentSquareId] & constants::GAS_MASK)
                        {
                            currentSquareIdShouldBeBlank = false;
                            std::cout << gaz;
                        }

                        // if we did not print a robot nor a coin nor a gaz, print nothing
                        if (currentSquareIdShouldBeBlank)
                            std::cout << blank;
                    }
                }

                // if j is even and not equal either to first nor last value, an inner wall or blank should be printed
                else if (j % 2 == 0 && j != 0 && j != (dim_h * 2))
                {
                    int leftSquareId = (i - 1) / 2 + (j - 2) / 2 * dim_v;
                    int rightSquareId = (i - 1) / 2 + j / 2 * dim_v;

                    if (this->maze[leftSquareId] & constants::RIGHT_MASK)
                        std::cout << blank;
                    // otherwise print wall
                    else
                        std::cout << innerVWall;
                }
            }
            // if i is even, print line of horizontal walls or blanks
            else if (i % 2 == 0)
            {
                // if j is odd, print square id
                if (j % 2 != 0)
                {
                    int upperSquareId = (i - 2) / 2 + (j - 1) / 2 * dim_v;
                    int lowerSquareId = i / 2 + (j - 1) / 2 * dim_v;

                    if (this->maze[upperSquareId] & constants::DOWN_MASK)
                        std::cout << blank;
                    // otherwise print wall
                    else
                        std::cout << innerHWall;
                }
                // if j is even and not equal either to first nor last value (square intersections)
                else if (j % 2 == 0 && j != 0 && j != (dim_h * 2))
                {
                    std::cout << blank;
                }
            }
        }
        if (i % 2 == 0)
        {
            std::cout << outerWall << std::endl;
        }
        else
        {
            std::cout << blank << std::endl;
        }
    }

    // last line is line of outer walls
    for (int i = 0; i < (dim_h * 2 + 1); i += 2)
        std::cout << outerWall << blank;
    std::cout << std::endl;
}