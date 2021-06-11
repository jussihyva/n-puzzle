import os
from posixpath import join
import subprocess
import os
import sys
import time
import platform

def	generate_puzzle(command_path, python, puzzle_size):
	puzzle_lines = []
	command = os.path.join(command_path, "PuzzleGenerator.py")
	process_create_puzzle = subprocess.Popen([python, command, "-s", str(puzzle_size), "-i", "50"],
								stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	(stdout_string, stderr_string) = process_create_puzzle.communicate()
	return (stdout_string.decode("UTF-8"))

def	solve_puzzle(command_path, puzzle_string, algorithm):
	solution_lines = []
	summary_lines = []
	string = ""

	command = os.path.join(command_path, "n_puzzle")
	if algorithm == "greedy_1":
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", "greedy", "-H", "t"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	elif algorithm == "greedy_2":
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", "greedy", "-H", "l"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	elif algorithm == "ida_1":
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", "ida", "-H", "t"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	elif algorithm == "ida_2":
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", "ida", "-H", "l"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	elif algorithm == "a_1":
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", "a", "-H", "t"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	elif algorithm == "a_2":
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", "a", "-H", "l"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	else:
		process_solve_puzzle = subprocess.Popen(
			[command, "-L", "3", "-A", algorithm, "-H", "t"],
			stdin =subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	(stdout_string, stderr_string) \
		= process_solve_puzzle.communicate(input=puzzle_string.encode())
	for line in stdout_string.decode("UTF-8").split("\n"):
		line = str(line.strip())
		solution_lines.append(line)
	for line in stderr_string.decode("UTF-8").split("\n"):
		line = str(line.strip())
		summary_lines.append(line)
	return (solution_lines, summary_lines)

def	print_puzzle(puzzle_lines):
	print("PUZZLE:")
	print(puzzle_lines)

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
	algorithm_list = ["a_1", "a_2", "ida_1", "ida_2", "greedy_1", "greedy_2"]
	current_path = os.path.dirname(sys.argv[0])
	command_path = os.path.join(current_path, "../bin")
	python = get_python_command()
	puzzle_string = generate_puzzle(command_path, python, sys.argv[1])
	print_puzzle(puzzle_string)
	for algorithm in algorithm_list:
		(solution_lines, summary_lines) = solve_puzzle(command_path, puzzle_string, algorithm)
		# print_result(solution_lines, "SOLUTION:")
		print_result(summary_lines, "")
	time.sleep(2)
