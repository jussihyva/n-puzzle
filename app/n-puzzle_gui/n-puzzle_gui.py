from puzzle import *
from read_input_map import *

# Example of puzzle input
# puzzleTileTable = [ [ 0,  1,  6,  2,  5],
# 					[ 7, 15,  3, 13,  4],
# 					[11,  8,  9, 14, 10],
# 					[12, 16, 17, 18, 19],
# 					[20, 21, 22, 23, 24]]
#
# puzzleSize = 5

if __name__ == "__main__":
	puzzleTileTable = read_map_file()
	puzzleSize = 5
	n_puzzle = PuzzleDemo(puzzleTileTable, puzzleSize)
	tileButtonList = n_puzzle.getTileButtons()
	n_puzzle.puzzle_switch(tileButtonList[24])
	n_puzzle.mainloop()
