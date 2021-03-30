import fileinput
from read_input_map import *
import time

def		readSolution(n_puzzle, original_size):
	tileButtonList = n_puzzle.getTileButtons()
	emptyTilePos = n_puzzle.getEmptyTilePos()
	puzzleSize = 1
	while (puzzleSize > 0):
		(puzzleSize, puzzleTileTable) = read_map()
		if (original_size == puzzleSize):
			tileToMove = puzzleTileTable[emptyTilePos[0]][emptyTilePos[1]]
			n_puzzle.puzzle_switch(tileButtonList[tileToMove])
			tileButtonList = n_puzzle.getTileButtons()
			emptyTilePos = n_puzzle.getEmptyTilePos()
