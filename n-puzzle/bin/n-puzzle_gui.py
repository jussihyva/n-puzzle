#!/usr/bin/env python3

import sys
import os
sys.path.append(os.path.abspath(os.path.dirname(__file__)
	+ '/../src/n-puzzle_gui'))
from puzzle import *
from read_input_map import *
from read_solution_steps import *
import threading

# Example of puzzle input
# puzzleTileTable = [ [ 0,  1,  6,  2,  5],
# 					[ 7, 15,  3, 13,  4],
# 					[11,  8,  9, 14, 10],
# 					[12, 16, 17, 18, 19],
# 					[20, 21, 22, 23, 24]]
#
# puzzleSize = 5

if __name__ == "__main__":
	(puzzleSize, puzzleTileTable) = read_map()
	n_puzzle = PuzzleDemo(puzzleTileTable, puzzleSize)
	t = threading.Thread(group=None,target=readSolution, args=[n_puzzle, puzzleSize])
	t.daemon = True
	t.start()
	n_puzzle.mainloop()
