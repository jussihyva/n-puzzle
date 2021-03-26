import sys
import re
import fileinput

def __split_map_line(line):
	words = line.split()
	tileArray = []
	for tile in words:
		tileArray.append(int(tile))
	return (tileArray)

def read_map_file():
	print('Read a map file')
	puzzleTileTable = []
	puzzleSize = 0
	tile_line_cnt = 0
	state = 'READ_SIZE'
	for line in fileinput.input():
		if (re.match("^\s*#.*$", line)):
			continue
		if state == 'READ_SIZE':
			puzzleSize = int(line.strip())
			state = 'READ_TILES'
		elif state == 'READ_TILES':
			puzzleTileTable.append(__split_map_line(line.strip()))
			tile_line_cnt += 1
			if puzzleSize == tile_line_cnt:
				break
		else:
			print('Line: ' + line, end='')
	fileinput.close()
	return (puzzleSize, puzzleTileTable)
