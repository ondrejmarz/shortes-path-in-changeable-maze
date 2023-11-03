# Shortes path in changeable maze

tldr: Finding the shortest path in a maze using BFA but at the beginning there are levers that change the maze.



## Input

The input begins with two numbers, n﻿ and k﻿, which represent the size of a square maze and the number of levers, respectively. 
The following constraints apply:
1 ≤ n ≤ 1000 and 0 ≤ k ≤ 10﻿.

Next come k﻿ lines representing the configuration of each lever. On each of the k﻿ lines, there is first a number y_i, -1 ≤ y_i ≤ n﻿, representing the position of the lever on the vertical axis relative to the solver's initial position. After the lever's position, there is always a sequence of n﻿ numbers from the set {0,1} representing the maze changes when the lever is used, known as the change vector.

Following this is the maze definition, which consists of a sequence of n^2 characters from the alphabet {0,1}﻿, where 0﻿ denotes an open field, and 1
1﻿ denotes an obstacle (impassable field).

The last line contains a pair of numbers x﻿ and y﻿ representing the position of the destination, with 1 ≤ x, y ≤ n﻿.

No need to validate the input as it will always be valid.



## Output

If it's impossible to reach the destination in any lever configuration, the output will display the number −1﻿.

If a solution exists, the output will follow this format:
* On the first line, it will show the length of the shortest path between the entrance to the maze and the destination.
* The number above will be followed on the next line by a sequence of k﻿ numbers from the set {0,1}﻿ representing the lever configuration (0﻿ = off, 1﻿ = on) for this shortest path.
* On the last line of the output, there will be a sequence of coordinates of the squares forming a shortest path from the entrance to the destination.



## Example

Input:

5 1<br>
3 00100<br>
00001 00010 00100 01000 10000<br>
5 5

Output:

14<br>
1<br>
[1;1],[1;2],[1;3],[2;3],[3;3],[4;3],[4;4],[4;5],[5;5]



## Comments

First are set the levers. After turning on any combination of levers (multiple levers can be active at the same time), the XOR operation is applied to the maze from the highest value of y_i to the lowest. Then, return to the initial position is needed, enter the maze, and find the shortest path to the destination.
If multiple levers are activated, it is possible to activate them in the same direction within one move. Specifically, if we have two levers with y_0 = 2﻿ and y_1 = 3﻿ and we want to activate both, the cost of activating the levers will be only 6﻿.
As evident from the example, move can be only upwards, downwards, left, and right. Diagonal movement is not possible.
The outer wall of the maze is always present and is not part of the input. Furthermore, when switching a lever, it does not modify the outer wall; the XOR operation is applied only to the inner part of the maze.
The STL library and std::string are not available for solving the problem.
