# N-puzzle

N-Puzzle is a project at Hive (Helsinki) coding school.

## 1. Overview

### 1.1 A goal of the project

NOTE. Text below is direct copy from the N-Puzzle project description from Hive Coding school.

The goal of this project is to solve the N-puzzle ("taquin" in French) game using the A*
search algorithm or one of its variants.
You start with a square board made up of N*N cells. One of these cells will be empty,
the others will contain numbers, starting from 1, that will be unique in this instance of
the puzzle.
Your search algorithm will have to find a valid sequence of moves in order to reach the
final state, a.k.a the "snail solution", which depends on the size of the puzzle (Example
below). While there will be no direct evaluation of its performance in this instance of the
project, it has to have at least a vaguely reasonable perfomance : Taking a few second to
solve a 3-puzzle is pushing it, ten seconds is unacceptable.

**3x3 Puzzle**
||||
|-|-|-|
|1|2|3|
|8||4|
|7|6|5|

**4x4 Puzzle**
|||||
|-|-|-|-|
|1|2|3|4|
|12|13|14|5|
|11||15|6|
|10|9|8|7|

**5x5 Puzzle**
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

### 1.2 Visualization of 3x3 Puzzle algorithms

Here is link to a page which demonstrate different kind of solutions (algorithms) to solve 3x3 Puzzle. The page is not related to the Hive N-Puzzle project.
* https://tristanpenman.com/demos/n-puzzle/

## 2. Implemented search algorithms

| Based on | Algorithm name | Abbreviation| Description | Refer to |
| :- | :- | :-: | :- | - |
|**DFS**|
|| DFS Random | dfs_1 | Depth-first search (DFS) with random selection of next move ||
|| DFS Deeping | dfs_2 | Depth-first search (DFS). Depth is increased step by step until solution of a puzzle is reached ||
|| DFS Deeping mem | dfs_3 | Depth-first search (DFS). Like dfs_2, but all N-puzzle states are saved which avoid tile moves already verified direction ||
|**BFS**|
|*Linked list*| BFS List | bfs_1 | Breadth-first search (BFS) with all visited N-puzzle states are saved in a linked list ||
|*B-Tree*| BFS B-tree | bfs_2 | Breadth-first search (BFS) with all visited N-puzzle states are saved in a B-tree ||

## 3. Implemented heuristic algorihms

| Algorithm | Abbreviation| Description | Refer to |
| :- | :-: | :- | -|
|**Tile out of place**||||
||toop_1| ||

## 4. Implemented utilities

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
||Will be added|||

## 5. Adapted (modified) open source functions

| Function | Function name | Description | Refer to |
| :- | :- | :- | :- |
| **N-Puzzle GUI** | | **Visualize tile moves in N-Puzzle** | [Welcome to N-Puzzle](https://pyinmyeye.blogspot.com/2012/07/tkinter-15-puzzle-demo-placer-geometry.html) |

## 6. Ready made script for creating input (N-puzzle) for a solution

## 7. Example
