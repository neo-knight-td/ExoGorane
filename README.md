# Introduction
This is the repository for all code files related to the ExoLegend Hackathon.

# Coding Style Conventions
## Comments
Independently of the programming language, as many comments as possible should be used. Comments related to code synthax (e.g. choice of certain variable type iso another) should start by "`NOTE :`". Comments concerning code improvement (e.g. addition of a functionnality or function) should start by "`TODO :`"

The other comments, related to the code semantic, should not start with a specific prefix.

## Example
```C++

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



