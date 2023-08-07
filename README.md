# Introduction
This is the repository for all code files related to the ExoLegend Hackathon. Code used for the final game of the hackathon is located under the ```Code_Dutra``` folder. This code allowed the team "Les Goranes" to hit the 2nd place of the competition.

Youtube extract of the hackathon is available below :

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/I6lq8xZG_MM/0.jpg)](https://www.youtube.com/watch?v=I6lq8xZG_MM)

# Documentation
## Coding Style Conventions
### Comments
Independently of the programming language, as many comments as possible should be used. Comments related to code synthax (e.g. choice of certain variable type iso another) should start by "`NOTE :`". Comments concerning code improvement (e.g. addition of a functionnality or function) should start by "`TODO :`"

The other comments, related to the code semantic, should not start with a specific prefix.

### Example
```cpp

//generateSuccessor will create a new successor for the parent game state
//NOTE : should pass reference to parent game state for it to be mutable
void generateSuccessor(GameState& parentGameState){
    //TODO : function content to be written
}
```

### C++
C++ [naming conventions](https://www.geeksforgeeks.org/naming-convention-in-c/) should be respected as much as possible inside all `.h` & `.cpp` files.

#### GameState Class
The `GameState` Class first attribute - `mazeSquares` - describes the configuration of the maze squares. It has type `vector<vector <int>>`. Each element of the first dimension vector corresonds to a square of the maze. Each elements of the second dimension vector (of type `int`) corresponds to the neighbour squares id that are accessible from the current square.

```cpp
    //  Let's consider the following simple maze (3x2):

    //  *****
    //  *   *
    //  *   *
    //  * | *
    //  *   *
    //  *   *
    //  *****

    // * is an outer wall
    // | is an inter wall

    // the squares (their id's) are distributed as follow :
    //  *****
    //  *G  *
    //  *   *
    //  * | *
    //  *   *
    //  *$ E*
    //  *****

    // the mazeVector variable representing this maze is :
    vector<vector <int>> mazeVector = {{1,3},{0,2},{1,5},{0,4},{3,5},{2,4}};

    // Example 1 : access neighbour squares of square 0 (squares 1 & 3)
    mazeVector[0];//will return vector {1,3}

    // Example 2 : loop over neighbour squares of square 0
    for(int i : mazeVector[0]{
        mazeVector[0][i];
    })

```
Another attribute of the `GameState` class is a list of remaining coins on the ground. It is named `coinsOnGround`. Its a simple list of square id's in which a coin lies.

The `GameState` class also contains a vector of robots (ref `Robot` class) with their location on the maze an coin score.

#### Minimax.cpp

This file implements the minimax algorithm to a simplified maze with only 2 robots.

### Evaluation function
terminal state : 1 or 0 depending if win or lose
non-terminal state : function bounded between 0 & 1 and that takes as parameters :
    coins gorane team
    coints enemy team
    ... think about other features !



