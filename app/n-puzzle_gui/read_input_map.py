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
	tile_cnt = 0
	state = 'READ_SIZE'
	for line in fileinput.input():
		if (re.match("^\s*#.*$", line)):
			continue
		if state == 'READ_SIZE':
			puzzleSize = int(line.strip())
			state = 'READ_TILES'
		elif state == 'READ_TILES':
			puzzleTileTable.append(__split_map_line(line.strip()))
			tile_cnt += 1
		else:
			print('Line: ' + line, end='')
	for line in fileinput.input():
		print(line)
	return (puzzleTileTable)
