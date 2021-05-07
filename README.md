# N-puzzle

N-Puzzle is a project at Hive (Helsinki) coding school.

## GUI to solve N-Puzzle manually

Appliction is based on a python script from 'https://pyinmyeye.blogspot.com/2012/07/tkinter-15-puzzle-demo-placer-geometry.html'

### Overview

### Implemented search algorithms

| Based on | Algorithm name | Abbreviation| Description | Refer to |
| :- | :- | :-: | :- | - |
|**DFS**|
|| DFS Random | dfs_1 | Depth-first search (DFS) with random selection of next move ||
|| DFS Deeping | dfs_2 | Depth-first search (DFS). Depth is increased step by step until solution of a puzzle is reached ||
|| DFS Deeping mem | dfs_3 | Depth-first search (DFS). Like dfs_2, but all N-puzzle states are saved which avoid tile moves already verified direction ||
|**BFS**|
|*Linked list*| BFS List | bfs_1 | Breadth-first search (BFS) with all visited N-puzzle states are saved in a linked list ||
|*B-Tree*| BFS B-tree | bfs_2 | Breadth-first search (BFS) with all visited N-puzzle states are saved in a B-tree ||

### Implemented heuristic algorihms

| Algorithm | Abbreviation| Description |
| :- | :-: | :- |

### Implemented utilities

| Function | Function name | Description | Refer to |
| :- | :- | :- | :- |
| **Stack** | | **Save data to a stack** | |
| | ft_stack_push | Push data to a stack | |
| | ft_stack_pop | Pop data from a stack | |
| **Queue** | | **Save data to a queue** | |
| | ft_enqueue | Push data to a queue | |
| | ft_dequeue | Pop data from a queue | |
