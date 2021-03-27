import fileinput
from read_input_map import *

def		readSolution(n_puzzle):
	tileButtonList = n_puzzle.getTileButtons()
	emptyTilePos = n_puzzle.getEmptyTilePos()
	while (1):
		(puzzleSize, puzzleTileTable) = read_map()
		tileToMove = puzzleTileTable[emptyTilePos[0]][emptyTilePos[1]]
		n_puzzle.puzzle_switch(tileButtonList[tileToMove])
		tileButtonList = n_puzzle.getTileButtons()
		emptyTilePos = n_puzzle.getEmptyTilePos()
