import os
from posixpath import join
import subprocess
import os
import sys
import time
import platform

def	generate_puzzle(command_path, python):
	puzzle_lines = []
	command = os.path.join(command_path, "PuzzleGenerator.py")
	process_create_puzzle = subprocess.Popen([python, command, "-s", "3"],
								stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	for line in process_create_puzzle.stdout.readlines():
		line = str(line.decode("UTF-8").strip())
		puzzle_lines.append(line)
	return (puzzle_lines)

def	solve_puzzle(command_path, puzzle_lines, algorithm):
	solution_lines = []
	summary_lines = []

	command = os.path.join(command_path, "n_puzzle")
	process_solve_puzzle = subprocess.Popen(
		[command, "-L", "3", "-A", algorithm, "-H", "t"], stdin =subprocess.PIPE,
								stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	for line in puzzle_lines:
		process_solve_puzzle.stdin.write(str(line + "\n").encode())
	process_solve_puzzle.stdin.close()
	# for line in process_solve_puzzle.stdout.readlines():
	# 	line = str(line.decode("UTF-8").strip())
	# 	solution_lines.append(line)
	for line in process_solve_puzzle.stderr.readlines():
		line = str(line.decode("UTF-8").strip())
		summary_lines.append(line)
	return (solution_lines, summary_lines)

def	print_puzzle(puzzle_lines):
	print("PUZZLE:")
	for line in puzzle_lines:
		print(line)
	print("")

def	print_result(solution_lines, header):
	print(header)
	for line in solution_lines:
		print(line)

def	get_python_command():
	python = "python2"
	if platform.system() == "Darwin":
		python = "python"
	return (python)

if __name__ == "__main__":
	algorithm_list = ["a_star_t", "ida*", "toop_1", "greedy"]
	current_path = os.path.dirname(sys.argv[0])
	command_path = os.path.join(current_path, "../bin")
	python = get_python_command()
	puzzle_lines = generate_puzzle(command_path, python)
	print_puzzle(puzzle_lines)
	for algorithm in algorithm_list:
		(solution_lines, summary_lines) = solve_puzzle(command_path, puzzle_lines, algorithm)
		# print_result(solution_lines, "SOLUTION:")
		print_result(summary_lines, "")
	time.sleep(2)
