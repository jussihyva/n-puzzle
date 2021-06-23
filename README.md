# N-puzzle

N-Puzzle is a project at Hive (Helsinki) coding school.

## 1. Project description

### 1.1 What is N-Puzzle

N-Puzzle is sliding puzzle and the most common one is 15-Puzzle.

#### 1.1.1 Description of 15-Puzzle in Wikipedia (https://en.wikipedia.org/wiki/15_puzzle)

The 15 puzzle (also called Gem Puzzle, Boss Puzzle, Game of Fifteen, Mystic Square and many others) is a sliding puzzle having 15 square tiles numbered 1–15 in a frame that is 4 tiles high and 4 tiles wide, leaving one unoccupied tile position. Tiles in the same row or column of the open position can be moved by sliding them horizontally or vertically, respectively. The goal of the puzzle is to place the tiles in numerical order.

Named for the number of tiles in the frame, the 15 puzzle may also be called a 16 puzzle, alluding to its total tile capacity. Similar names are used for different sized variants of the 15 puzzle, such as the 8 puzzle that has 8 tiles in a 3×3 frame.

The n puzzle is a classical problem for modelling algorithms involving heuristics. Commonly used heuristics for this problem include counting the number of misplaced tiles and finding the sum of the taxicab distances between each block and its position in the goal configuration.[1] Note that both are admissible, i.e. they never overestimate the number of moves left, which ensures optimality for certain search algorithms such as A*.


#### 1.1.2 Useful links to get more information

- [15 puzzle](https://en.wikipedia.org/wiki/15_puzzle)
- [Sliding puzzle](https://en.wikipedia.org/wiki/Sliding_puzzle)

#### 1.1.3 An example

![15-Puzzle looks like this](https://miro.medium.com/max/600/1*Kg5sN-5U3Q7hevW9qhz2rA.gif)
https://miro.medium.com/max/600/1*Kg5sN-5U3Q7hevW9qhz2rA.gif

#### 1.1.4 Complexity of N-Puzzle

| Puzzle size | Calculation | Number of possible states ([Refer to](https://en.wikipedia.org/wiki/15_puzzle#Solvability)) |
| :-: | :-: | :-: |
| 8 (3x3) | 9! / 2 | 181000 |
| 15 (4x4) | 16! / 2 | 10 461 394 944 000
| 24 (5x5) | 25! / 2 | 7 755 605 021 665 492 992 000 000

### 1.2 A goal of the project

The goal of this project is to solve the N-puzzle game using the A\* search algorithm or one of its variants.
You start with a square board made up of N*N cells. One of these cells will be empty,
the others will contain numbers, starting from 1, that will be unique in this instance of
the puzzle.
Your search algorithm will have to find a valid sequence of moves in order to reach the
final state, a.k.a the "snail solution", which depends on the size of the puzzle (Example
below). While there will be no direct evaluation of its performance in this instance of the
project, it has to have at least a vaguely reasonable perfomance : Taking a few second to
solve a 3-puzzle is pushing it, ten seconds is unacceptable.

**8-Puzzle (3x3)**
||||
|-|-|-|
|1|2|3|
|8||4|
|7|6|5|

**15-Puzzle (4x4)**
|||||
|-|-|-|-|
|1|2|3|4|
|12|13|14|5|
|11||15|6|
|10|9|8|7|

**24-Puzzle (5x5)**
||||||
|-|-|-|-|-|
|1|2|3|4|5|
|16|17|18|19|6|
|15|24||20|7|
|14|23|22|21|8|
|13|12|11|10|9|

The only move one can do in the N-puzzle is to swap the empty cell with one of its
neighbors (No diagonals, of course. Imagine you’re sliding a block with a number on it
towards an empty space).

### 1.3 Visualization of 3x3 Puzzle algorithms

Here is a link to a page which demonstrate (visualize) solutions for solving 3x3 Puzzle. The page is not related to the Hive N-Puzzle project.
* https://tristanpenman.com/demos/n-puzzle/

### 1.4 Ready made script for creating input (N-puzzle) for a solution

## 2. My Solution

### 2.1 Solution description

[Link to Solution description (PPT)](https://onedrive.live.com/embed?resid=7AEA86BDEF93781E%2178221&amp;authkey=%21AI75ceSh6FeMjX0&amp;em=2&amp;wdAr=1.7777777777777777)

#### 2.1.1 Overview of implemented search algorithms

| Search algorithm | Cost of the path from start node | Estimat cost to the goal | More like |
| :-: | :-: | :-: | :-: |
| [A*]((https://en.m.wikipedia.org/wiki/A*_search_algorithm)) | Yes | Yes | BFS |
| [IDA*](https://en.m.wikipedia.org/wiki/Iterative_deepening_A*) | Yes | Yes | DFS |
| [Greedy](https://en.wikipedia.org/wiki/Greedy_algorithm) | No | Yes | DFS |

#### 2.1.2 Overview of implemented heuristic algorithms

| Heuristic algorithm | Is admissible
| :-: | :-: |
| [Hamming](https://en.wikipedia.org/wiki/Hamming_distance) | Yes |
| [Taxicab](https://en.m.wikipedia.org/wiki/Taxicab_geometry) | Yes |
| [Taxicab with linear conflicts](https://medium.com/swlh/looking-into-k-puzzle-heuristics-6189318eaca2) | Yes |

#### 2.1.3 Key measurements

| Measurement | Valuable algorithm | goal |
| :-: | :-: | :-: |
| Moves to reach a goal | A*, IDA* | Least number of tile moves to reach a goal |
| Memory usage | IDA* | Least number of saved N-puzzle states |
| CPU usage time | | Shortist time to solve a N-puzzle |
| Solution complezity | | Least number of visited N-puzzle states (tile moves) |

### 2.2 Implemented search algorithms

| Based on | Algorithm name | Abbreviation| Description | Refer to |
| :- | :- | :-: | :- | - |
|**DFS**|
|| DFS Random | dfs_1 | Depth-first search (DFS) with random selection of next move ||
|| DFS Deeping | dfs_2 | Depth-first search (DFS). Depth is increased step by step until solution of a puzzle is reached ||
|| DFS Deeping mem | dfs_3 | Depth-first search (DFS). Like dfs_2, but all N-puzzle states are saved which avoid tile moves already verified direction ||
| **IDA*** | IDA* with a heuristic algorithm | ida | IDA* is based DFS, a heuristic algorithm and path cost to priorize tile moves. | [Iterative deepening A*](https://en.m.wikipedia.org/wiki/Iterative_deepening_A*) |
|**BFS**|
|*Linked list*| BFS List | bfs_1 | Breadth-first search (BFS) with all visited N-puzzle states are saved in a linked list ||
|*B-Tree*| BFS B-tree | bfs_2 | Breadth-first search (BFS) with all visited N-puzzle states are saved in a B-tree ||
| **A*** | A* with taxicab (hardcoded heuristic algorithm) | a | A* is based BFS, a heuristic algorithm and path cost to priorize tile moves. | [A* search algorithm](https://en.m.wikipedia.org/wiki/A*_search_algorithm) |
| **Uniform-cost search** | UCS | ucs --> bfs_2 | Selection of the next move is based on a cost from an initial (root) state. A lowest value is the first in a priority queue. In case of N-Puzzle, because of a cost of every move is 1 implementation is same as BFS (refer bfs_2) | [What is uniform-cost search?](https://www.educative.io/edpresso/what-is-uniform-cost-search) |
| **Greedy search** |  | greedy | Greedy is based a search with a heuristic algorithm (only) to priorize tile moves. Cont from initial state is not included into calculation.| [Greedy algorithm](https://en.wikipedia.org/wiki/Greedy_algorithm) |

### 2.3 Implemented heuristic algorihms

| Algorithm | Abbreviation| Description | Refer to |
| :- | :-: | :- | -|
|**Hamming distance** (Tiles out of place) |h| Selcection of the next move is based a number of tiles out of the right place. A lowest value is the first in a priority queue. | [Hamming distance](https://en.wikipedia.org/wiki/Hamming_distance) |
| **Taxicab geometry** (Manhattan distance) | t | Selection of the next move is based a sum of tiles absolute distances (cartesian distance) from the right place. A lowest value is the first in a priority queue. | [Taxicab geometry](https://en.m.wikipedia.org/wiki/Taxicab_geometry) |
| **Taxicab geometry with direct reversal of tiles penalty** | l | Selection of the next move is based to taxicab geometry and direct reversal of tiles. A lowest value is the first in a priority queue. | [Taxicab geometry](https://en.m.wikipedia.org/wiki/Taxicab_geometry)|

### 2.4 Implemented N-puzzle search algorithm

| Function | Function name | Description | Refer to |
| :- | :- | :- | :- |
| n_puzzle_search_algorithm | n_puzzle_search_algorithm | Searches all possible tile move alternatives from a n-puzzle state. The function is used by higher-level algorithms (A*, IDA*, etc.) as input (the next possible n-puzzle states). | |

### 2.5 Implemented N-Puzzle specific functions

| Function | Function name | Description | Refer to |
| :- | :- | :- | :- |
| **Is N-Puzzle solvable** | is_puzzle_solvable | Verifies is N-puzzle initail state solvable. | [Check if 15 puzzle is solvable](https://stackoverflow.com/questions/34570344/check-if-15-puzzle-is-solvable) |

### 2.6 Implemented utilities

| Function | Function name | Description | Refer to |
| :- | :- | :- | :- |
| **Stack** | | **Push/Pop data to/from a stack** | [Stack (abstract data type)](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)) |
| | ft_stack_push | Push data to a stack | |
| | ft_stack_pop | Pop data from a stack | |
| **Queue** | | **Push/Pop data to/from a queue** | [Queue (abstract data type)](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) |
| | ft_enqueue | Push data to a queue | |
| | ft_dequeue | Pop data from a queue | |
| **B-Tree** | | **Save data to a B-Tree** | [B-Tree](https://en.wikipedia.org/wiki/B-tree) |
| | ft_bt_insert | Push data to a B-Tree | |
| | ft_bt_find | Find data from a B-Tree | |
| | ft_bt_print | Print all data (keys) from a B-Tree | |
| | ft_bt_delete | Delete all data from a B-Tree | |
| **Prio Queue** | | **Save data to a priorized queue** | |
| | ft_prio_enqueue | Push data to a queue | |
| | ft_prio_dequeue | Pop data from a queue | |
| **Event logging** | | Print events to stderr during a program execution. A logging level (five levels) could be specified in input argument (-L) | Based on [A simple logging library implemented in C99](https://github.com/rxi/log.c)|
| | FT_LOG_\<level\>| level = TRACE, DEBUG, INFO, WARN, ERROR, FATAL.  Logging level TRACE (0) print all kind of events to stderr during execution of a program. A default value is WARN (3). | |

## 2.7 Adapted (modified) open source programs

| Function | Function name | Description | Refer to |
| :- | :- | :- | :- |
| **N-Puzzle GUI** | | **Visualize tile moves in N-Puzzle** | Based on [Welcome to N-Puzzle](https://pyinmyeye.blogspot.com/2012/07/tkinter-15-puzzle-demo-placer-geometry.html) |

## 3. Installation

### 1. Verify prerequisites

python2 --version
>Python 2.xxxxx

python3 --version
>Python 3.xxxxx

docker --version
>Docker version 20.10.5, build 55c4c88

docker-compose --version
>docker-compose version 1.29.0, build 07737305

clang -v
>fgfddfgfdgdffggff

valgrind
>fdsdsfdfsdfdsfdsfdsfsdf

### 2. Clone the project from github

git clone https://github.com/jussihyva/n-puzzle.git

### 3. Compile and start docker containers

cd n-puzzle
>NOTE. make command will fail if docker requires admin rights. Use sudo to avoid an issue.

make

### 4. Verify installation

./n-puzzle/bin/n_puzzle -h

>Help printout should be printed

## 4. Use cases

## 5. Examples

### 5.1 N-Puzzle input creator

python2 n-puzzle/bin/PuzzleGenerator.py -s 3

>\# This puzzle is solvable
3
6 5 3
2 7 8
4 1 0

### 5.2 N-Puzzle solver (My Solution)

python n-puzzle/bin/PuzzleGenerator.py -s 3 -i 2 | ./n-puzzle/bin/n_puzzle -A a -H t

>3
    0    1    3
    8    2    4
    7    6    5
 3
    1    0    3
    8    2    4
    7    6    5
 3
    1    2    3
    8    0    4
    7    6    5
SUMMARY
Puzzle size:                           3
Used algorithm:                        a taxicab
Execution time:                        69 ms
CPU usage time:                        8 ms
Memory usage:                          2 Mb
Total number of tile moves:            5
Total number of tile move collisions:  1
Max. number of saved states:           4
Number of solution moves:              2
======================================

### 5.2 N-puzzle GUI (Modified in my solution)

![N-puzzle GUI](n-puzzle/data/Manual_Puzzle_demo.gif)

### 5.3 N-Puzzle report visualizer

make -C n-puzzle run_test S=6

## 6. Lessons learned

Breafly, learning point of view this project were long enough, challenging enough to understand graph related algorithms deep enough. Understanding pros. and cons. of different algorithms, fitfalls in implementation (algorithm could be powerless not because of algorithm itself but bad implementation). Now I have execellent (wide) understanding how, when and why selected algorithm is usefull or useless solution for a specific issue. Also, now I have much more experience to learn and discuss (talk) different kind of algorithm solution alternatives with other high experience algorithm guys.

### 6.1 Stack, Queue, B-Tree and Prio-Queue

The first time whan I implemented these function by C-language. Stack is based on linked list. Queue is based on two stacks. Idea is to put (ENQUEUE) new data into Stack A. DEQUEUE function move data from stack A (If stack B is empty) to stack B and pull data from stack B. I implemented B-tree from my head (Cannot say is it best of all). Because of B-tree were quite new functionality for me I read some articles from internet and then just started to write. I didn't use tearm "leaf-node" in my implemantaion. Once again, I cannot say is the implementation best of all. Learning point of view it was valuable session to get B-tree implemented in my way. Prio-Queue is miz of Queue and B-tree functionality. Funny solution, I think, and seems working well.

### 6.2 BFS (Breadth-First Search) and DFS (Depth-First Search)

I played with DFS and BFS algorithms in pervious projects (Push swap and Lem-in), so I had some experience already. Any case I re-wrote everytihing from my head once again. Now I feel that those algorithms are in may back-bone. N-puzzle solving point of view both algorithms are powerless. I wrote those just to start implementation from most powerless algorithms and re-freshing my memory how basig algoritms work and how to write those.

### 6.3 A\*, IDS\* and Greedy

A\*, IDA\* and Greedy were new algorithms for me. To be honest, I read and heared somothing abouth these several months ago but nothing so deep that I did not feel that this will be peace of cake. Learning session takes time even these are quite simple algorithms. I think that main reaason (why learing takes time) is realted to mixing A\*, IDA\* and Greedy algorithms all the time. Not only those three words but many others like Uniform, Uninformed, Dijkstra, heuristic, admissible etc... caused confusion (full mess) in my head. Implementation (once again, from my own head) was quite straight forward. Actually, at the end of the project I got bit worried that some speed and memory usage issues (maybe too slow, maybe too high memory usage) are related to not bet of all implementation. In this project I didn't analyse my solution speed point of view. Evaluations required less than 10sec exectuion time for 8-Puzzle. Mine waste less than 100ms. So, noo need for speed analysis.

### 6.4 Heuristic Algorithms

#### 6.4.1 Hamming

#### 6.4.2 Taxicab (Manhattan)

#### 6.4.3 Taxicab with linear conflicts
