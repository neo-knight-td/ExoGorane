#ifndef MAZE_STORE_H
#define MAZE_STORE_H

#include "Constants.h"

struct MazeStore
{
    const char LargeMaze[196] =
        {
            // column 1
            DOWN_MASK + RIGHT_MASK,//1
            UP_MASK + DOWN_MASK,//2
            UP_MASK + DOWN_MASK,//3
            UP_MASK + RIGHT_MASK,//4
            DOWN_MASK + RIGHT_MASK,//5
            UP_MASK + RIGHT_MASK,//6
            DOWN_MASK + RIGHT_MASK,//7
            UP_MASK + RIGHT_MASK,//8
            DOWN_MASK + RIGHT_MASK,//9
            UP_MASK + RIGHT_MASK,//10
            DOWN_MASK + RIGHT_MASK,//11
            UP_MASK + DOWN_MASK,//12
            UP_MASK + DOWN_MASK,//13
            UP_MASK + RIGHT_MASK,//14
            // column 2
            DOWN_MASK + LEFT_MASK + RIGHT_MASK,//1
            UP_MASK + RIGHT_MASK,//2
            DOWN_MASK + RIGHT_MASK,//3
            UP_MASK + DOWN_MASK + LEFT_MASK,//4
            UP_MASK + LEFT_MASK,//5
            LEFT_MASK + RIGHT_MASK,//6
            LEFT_MASK + RIGHT_MASK,//7
            LEFT_MASK + RIGHT_MASK,//8
            LEFT_MASK + RIGHT_MASK,//9
            DOWN_MASK + LEFT_MASK,//10
            UP_MASK + DOWN_MASK + LEFT_MASK,//11
            UP_MASK + RIGHT_MASK,//12
            DOWN_MASK + RIGHT_MASK,//13
            UP_MASK + LEFT_MASK + RIGHT_MASK,//14
            // column 3
            LEFT_MASK + RIGHT_MASK,//1
            LEFT_MASK + RIGHT_MASK,//2
            DOWN_MASK + LEFT_MASK,//3
            UP_MASK + RIGHT_MASK,//4
            DOWN_MASK + RIGHT_MASK,//5
            UP_MASK + LEFT_MASK,//6
            LEFT_MASK + RIGHT_MASK,//7
            LEFT_MASK + RIGHT_MASK,//8
            DOWN_MASK + LEFT_MASK,//9
            UP_MASK + RIGHT_MASK,//10
            DOWN_MASK + RIGHT_MASK,//11
            UP_MASK + LEFT_MASK,//12
            LEFT_MASK + RIGHT_MASK,//13
            LEFT_MASK + RIGHT_MASK,//14
            // column 4
            LEFT_MASK + RIGHT_MASK,//1
            DOWN_MASK + LEFT_MASK,//2
            UP_MASK + DOWN_MASK,//3
            UP_MASK + LEFT_MASK,//4
            LEFT_MASK + RIGHT_MASK,//5
            DOWN_MASK + RIGHT_MASK,//6
            UP_MASK + DOWN_MASK + LEFT_MASK,//7
            UP_MASK + DOWN_MASK + LEFT_MASK,//8
            UP_MASK + RIGHT_MASK,//9
            LEFT_MASK + RIGHT_MASK,//10
            DOWN_MASK + LEFT_MASK,//11
            UP_MASK + DOWN_MASK,//12
            LEFT_MASK + UP_MASK,//13
            LEFT_MASK + RIGHT_MASK,//14
            // column 5
            DOWN_MASK + LEFT_MASK,//1
            UP_MASK + RIGHT_MASK,//2
            DOWN_MASK + RIGHT_MASK,//3
            UP_MASK + DOWN_MASK,//4
            UP_MASK + DOWN_MASK + LEFT_MASK + RIGHT_MASK,//5
            UP_MASK + LEFT_MASK,//6
            DOWN_MASK + RIGHT_MASK,//7
            UP_MASK + RIGHT_MASK,//8
            DOWN_MASK + LEFT_MASK,//9
            UP_MASK + DOWN_MASK + LEFT_MASK + RIGHT_MASK,//10
            UP_MASK + DOWN_MASK,//11
            UP_MASK + RIGHT_MASK,//12
            DOWN_MASK + RIGHT_MASK,//13
            UP_MASK + LEFT_MASK,//14
            // column 6
            DOWN_MASK + RIGHT_MASK,//1
            UP_MASK + LEFT_MASK,//2
            DOWN_MASK + LEFT_MASK + RIGHT_MASK,//3
            UP_MASK,//4
            DOWN_MASK + LEFT_MASK,//5
            UP_MASK + DOWN_MASK + RIGHT_MASK,//6
            UP_MASK + LEFT_MASK,//7
            DOWN_MASK + LEFT_MASK + RIGHT_MASK,//8
            UP_MASK + DOWN_MASK + RIGHT_MASK,//9
            UP_MASK + LEFT_MASK,//10
            DOWN_MASK,//11
            UP_MASK + LEFT_MASK + RIGHT_MASK,//12
            DOWN_MASK + LEFT_MASK,//13
            UP_MASK + RIGHT_MASK,//14
            // column 7
            DOWN_MASK + LEFT_MASK + RIGHT_MASK,//1
            UP_MASK + DOWN_MASK + RIGHT_MASK,//2
            UP_MASK + LEFT_MASK,//3
            DOWN_MASK + RIGHT_MASK,//4
            UP_MASK + DOWN_MASK,//5
            UP_MASK + DOWN_MASK + LEFT_MASK,//6
            UP_MASK + DOWN_MASK + RIGHT_MASK,//7
            UP_MASK + LEFT_MASK + RIGHT_MASK,//8
            DOWN_MASK + LEFT_MASK,//9
            UP_MASK + DOWN_MASK,//10
            UP_MASK + RIGHT_MASK,//11
            DOWN_MASK + LEFT_MASK,//12
            UP_MASK + DOWN_MASK + RIGHT_MASK,//13
            UP_MASK + LEFT_MASK + RIGHT_MASK,//14
            // column 8
            DOWN_MASK + RIGHT_MASK + LEFT_MASK,//1
            UP_MASK + DOWN_MASK + LEFT_MASK,//2
            UP_MASK + RIGHT_MASK,//3
            DOWN_MASK + LEFT_MASK,//4
            UP_MASK + DOWN_MASK,//5
            UP_MASK + RIGHT_MASK,//6
            RIGHT_MASK + DOWN_MASK + LEFT_MASK,//7
            UP_MASK + DOWN_MASK + LEFT_MASK,//8
            UP_MASK + DOWN_MASK + RIGHT_MASK,//9
            UP_MASK + DOWN_MASK,//10
            UP_MASK + LEFT_MASK,//11
            DOWN_MASK + RIGHT_MASK,//12
            UP_MASK + DOWN_MASK + LEFT_MASK,//13
            UP_MASK + RIGHT_MASK + LEFT_MASK,//14
            // column 9
            DOWN_MASK + LEFT_MASK,//1
            UP_MASK + RIGHT_MASK,//2
            DOWN_MASK + RIGHT_MASK + LEFT_MASK,//3
            UP_MASK,//4
            DOWN_MASK + RIGHT_MASK,//5
            UP_MASK + DOWN_MASK + LEFT_MASK,//6
            UP_MASK + RIGHT_MASK + LEFT_MASK,//7
            DOWN_MASK + RIGHT_MASK,//8
            UP_MASK + DOWN_MASK + LEFT_MASK,//9
            UP_MASK + RIGHT_MASK,//10
            DOWN_MASK,//11
            UP_MASK + RIGHT_MASK + LEFT_MASK,//12
            DOWN_MASK + RIGHT_MASK,//13
            UP_MASK + LEFT_MASK,//14
            // column 10
            DOWN_MASK + RIGHT_MASK,//1
            UP_MASK + LEFT_MASK,//2
            DOWN_MASK + LEFT_MASK,//3
            UP_MASK + DOWN_MASK,//4
            UP_MASK + DOWN_MASK + RIGHT_MASK + LEFT_MASK,//5
            UP_MASK + RIGHT_MASK,//6
            DOWN_MASK + LEFT_MASK,//7
            UP_MASK + LEFT_MASK,//8
            DOWN_MASK + RIGHT_MASK,//9
            UP_MASK + DOWN_MASK + RIGHT_MASK + LEFT_MASK,//10
            UP_MASK + DOWN_MASK,//11
            UP_MASK + LEFT_MASK,//12
            DOWN_MASK + LEFT_MASK,//13
            UP_MASK + RIGHT_MASK,//14
            // column 11
            RIGHT_MASK + LEFT_MASK,//1
            DOWN_MASK + RIGHT_MASK,//2
            UP_MASK + DOWN_MASK,//3
            UP_MASK + RIGHT_MASK,//4
            RIGHT_MASK + LEFT_MASK,//5
            DOWN_MASK + LEFT_MASK,//6
            UP_MASK + DOWN_MASK + RIGHT_MASK,//7
            UP_MASK + DOWN_MASK + RIGHT_MASK,//8
            UP_MASK + LEFT_MASK,//9
            RIGHT_MASK + LEFT_MASK,//10
            DOWN_MASK + RIGHT_MASK,//11
            UP_MASK + DOWN_MASK,//12
            RIGHT_MASK + UP_MASK,//13
            RIGHT_MASK + LEFT_MASK,//14
            // column 12
            RIGHT_MASK + LEFT_MASK,//1
            RIGHT_MASK + LEFT_MASK,//2
            DOWN_MASK + RIGHT_MASK,//3
            UP_MASK + LEFT_MASK,//4
            DOWN_MASK + LEFT_MASK,//5
            UP_MASK + RIGHT_MASK,//6
            RIGHT_MASK + LEFT_MASK,//7
            RIGHT_MASK + LEFT_MASK,//8
            DOWN_MASK + RIGHT_MASK,//9
            UP_MASK + LEFT_MASK,//10
            DOWN_MASK + LEFT_MASK,//11
            UP_MASK + RIGHT_MASK,//12
            RIGHT_MASK + LEFT_MASK,//13
            RIGHT_MASK + LEFT_MASK,//14
            // column 13
            DOWN_MASK + RIGHT_MASK + LEFT_MASK,//1
            UP_MASK + LEFT_MASK,//2
            DOWN_MASK + LEFT_MASK,//3
            UP_MASK + DOWN_MASK + RIGHT_MASK,//4
            UP_MASK + RIGHT_MASK,//5
            RIGHT_MASK + LEFT_MASK,//6
            RIGHT_MASK + LEFT_MASK,//7
            RIGHT_MASK + LEFT_MASK,//8
            RIGHT_MASK + LEFT_MASK,//9
            DOWN_MASK + RIGHT_MASK,//10
            UP_MASK + DOWN_MASK + RIGHT_MASK,//11
            UP_MASK + LEFT_MASK,//12
            DOWN_MASK + LEFT_MASK,//13
            UP_MASK + RIGHT_MASK + LEFT_MASK,//14
            // column 14
            DOWN_MASK + LEFT_MASK,//1
            UP_MASK + DOWN_MASK,//2
            UP_MASK + DOWN_MASK,//3
            UP_MASK + LEFT_MASK,//4
            DOWN_MASK + LEFT_MASK,//5
            UP_MASK + LEFT_MASK,//6
            DOWN_MASK + LEFT_MASK,//7
            UP_MASK + LEFT_MASK,//8
            DOWN_MASK + LEFT_MASK,//9
            UP_MASK + LEFT_MASK,//10
            DOWN_MASK + LEFT_MASK,//11
            UP_MASK + DOWN_MASK,//12
            UP_MASK + DOWN_MASK,//13
            UP_MASK + LEFT_MASK//14
        };

    const char RegularMaze[36] =
        {
            // first column
            RIGHT_MASK + DOWN_MASK,
            UP_MASK + DOWN_MASK,
            UP_MASK + RIGHT_MASK,
            DOWN_MASK,
            RIGHT_MASK + UP_MASK + DOWN_MASK,
            RIGHT_MASK + UP_MASK,
            // second column
            RIGHT_MASK + LEFT_MASK + DOWN_MASK,
            UP_MASK + RIGHT_MASK,
            DOWN_MASK + LEFT_MASK,
            UP_MASK + DOWN_MASK + RIGHT_MASK,
            UP_MASK + LEFT_MASK,
            RIGHT_MASK + LEFT_MASK,
            // third column
            LEFT_MASK,
            RIGHT_MASK + LEFT_MASK + DOWN_MASK,
            UP_MASK + DOWN_MASK + RIGHT_MASK,
            UP_MASK + LEFT_MASK + RIGHT_MASK,
            RIGHT_MASK + DOWN_MASK,
            LEFT_MASK + UP_MASK,
            // fourth column
            RIGHT_MASK + DOWN_MASK,
            UP_MASK + LEFT_MASK,
            RIGHT_MASK + DOWN_MASK + LEFT_MASK,
            UP_MASK + DOWN_MASK + LEFT_MASK,
            UP_MASK + LEFT_MASK + RIGHT_MASK,
            RIGHT_MASK,
            // fith column
            LEFT_MASK + RIGHT_MASK,
            DOWN_MASK + RIGHT_MASK,
            UP_MASK + DOWN_MASK + LEFT_MASK,
            UP_MASK + RIGHT_MASK,
            DOWN_MASK + LEFT_MASK,
            RIGHT_MASK + LEFT_MASK + UP_MASK,
            // sixth column
            LEFT_MASK + DOWN_MASK,
            DOWN_MASK + LEFT_MASK + UP_MASK,
            UP_MASK,
            DOWN_MASK + LEFT_MASK,
            DOWN_MASK + UP_MASK,
            LEFT_MASK + UP_MASK,
        };
};

#endif