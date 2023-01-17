# Introduction
This is the repository for all code files related to the ExoLegend Hackathon.

# Coding Style Conventions
## Comments
Independently of the programming language, as many comments as possible should be used. Comments related to code synthax (e.g. choice of certain variable type iso another) should start by "`NOTE :`". Comments concerning code improvement (e.g. addition of a functionnality or function) should start by "`TODO :`"

The other comments, related to the code semantic, should not start with a specific prefix.

## Example
```cpp

//generateSuccessor will create a new successor for the parent game state
//NOTE : should pass reference to parent game state for it to be mutable
void generateSuccessor(GameState& parentGameState){
    //TODO : function content to be written
}
```

## CPP
C++ [naming conventions](https://www.geeksforgeeks.org/naming-convention-in-c/) should be respected as much as possible inside all `.hpp` & `.cpp` files.

### Minimax.cpp

This file implements the minimax algorithm to a simplified maze with only 2 robots and 1 coin.

#### GameState Class
The `GameState` Class first attribute - `mazeSquares` - describes the configuration of the maze squares. It has type `vector<vector <int>>`. Each element of the first dimension vector corresonds to a square of the maze. Each elements of the second dimension vector (of type `int`) corresponds to the neighbour squares that are accessible from the current square.

```cpp
    //  Let's consider the following simple maze (3x2):

    //  *****
    //  *   *
    //  * | *
    //  *   *
    //  *****

    // * is an outer wall
    // | is an inter wall

    // the squares (their id's) are distributed as follow :
    //  *****
    //  *0 3*
    //  *1|4*
    //  *2 5*
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
Second attribute of the `GameState` class is a list of remaining coins on the ground. It is named `coinsOnGround`. Its a simple list of square id's in which a coin lies.

Third attribute of the `GameState` class is a vector of robots (ref `Robot` class).

Fourth attribute of the `GameState` class is a list of successor state to the current state. These successors are also of type `GameState`.

```Results
Ez Win!


