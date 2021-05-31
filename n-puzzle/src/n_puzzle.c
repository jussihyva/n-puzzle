/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/31 11:23:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	initialize_print_strings(int map_size, char **string, char **line)
{
	int				len_of_tile_number;
	char			*size_string;

	size_string = ft_itoa(map_size * map_size);
	len_of_tile_number = ft_max_int(4, ft_strlen(size_string));
	*string = ft_strnew(sizeof(**string) * (len_of_tile_number + 1));
	*line = ft_strnew(sizeof(**line) * ((len_of_tile_number + 1) * map_size
				* map_size));
	ft_strdel(&size_string);
	return ;
}

static void	print_map(t_map *map)
{
	t_xy_values		yx_pos;
	char			*line;
	char			*string;

	initialize_print_strings(map->size, &string, &line);
	FT_LOG_INFO("Puzzle size: %d", map->size);
	yx_pos.y = -1;
	while (++yx_pos.y < map->size)
	{
		ft_bzero(line, sizeof(line));
		yx_pos.x = -1;
		while (++yx_pos.x < map->size)
		{
			ft_sprintf(string, " %4d", map->tile_map[yx_pos.y][yx_pos.x]);
			ft_strcat(line, string);
		}
		FT_LOG_INFO("%s", line);
	}
	ft_memdel((void **)&line);
	ft_memdel((void **)&string);
	return ;
}

static void	send_stat_report(t_puzzle *puzzle)
{
	t_statistics	*statistics;

	statistics = puzzle->statistics;
	stat_set_end_time(puzzle->statistics);
	stat_update_cpu_usage(puzzle->statistics);
	puzzle->statistics->order = E_SEND_TO_INFLUXDB;
	FT_LOG_INFO("%-20s %ld", "Execution time:",
		get_execution_time(puzzle->statistics));
	puzzle->statistics->order = E_NONE;
	FT_LOG_INFO("%-20s %d", "Total num of moves:", *puzzle->tile_move_cnt);
	ft_dprintf(2, "\n\033[0;32mSUMMARY\n");
	ft_dprintf(2, "%-26s %d\n", "Puzzle size:", statistics->puzzle_size);
	ft_dprintf(2, "%-26s %s %s\n", "Used algorithm:", statistics->algorithm,
		statistics->algorithm_substring);
	ft_dprintf(2, "%-26s %ld ms\n", "Execution time:",
		get_execution_time(statistics));
	ft_dprintf(2, "%-26s %ld ms\n", "CPU usage time:",
		statistics->cpu_usage_ms);
	ft_dprintf(2, "%-26s %d Mb\n", "Memory usage:",
		statistics->max_mem_usage / 1000);
	ft_dprintf(2, "%-26s %d\n", "Number of solution moves:",
		statistics->solution_move_cnt);
	ft_dprintf(2, "======================================\033[0m\n\n");
	return ;
}

static void	puzzle_solver(char *algorithm, t_puzzle *puzzle)
{
	if (!ft_strncmp(algorithm, "dfs", 3))
		dfs(puzzle);
	else if (!ft_strncmp(algorithm, "bfs", 3))
		bfs(puzzle);
	else if (!ft_strncmp(algorithm, "toop", 3))
		alg_toop(puzzle);
	else if (!ft_strncmp(algorithm, "a_star", 3))
		alg_a_star(puzzle);
	else if (!ft_strncmp(algorithm, "ida*", 3))
		alg_ida_star(puzzle);
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", algorithm,
			"Specify a valid algorithm with the param -A");
	return ;
}

int	main(int argc, char **argv)
{
	t_input					*input;
	t_statistics			*statistics;
	t_influxdb				*influxdb;
	t_puzzle				*puzzle;

	statistics = initialize_statistics();
	input = read_input_data(argc, argv, statistics);
	stat_set_start_time(input->statistics);
	influxdb = setup_influxdb_connection("127.0.0.1", "8086");
	statistics->connection = (t_tls_connection *)influxdb->connection;
	statistics->puzzle_size = input->puzzle_map->size;
	print_map(input->puzzle_map);
	puzzle = initialize_puzzle(input);
	puzzle->tile_move_cnt = &statistics->tile_move_cnt;
	puzzle->states_cnt = &statistics->puzzle_states_cnt;
	puzzle->solution_move_cnt = &statistics->solution_move_cnt;
	puzzle->stat_counters = &statistics->stat_counters;
	puzzle->state_collision_cnt = &statistics->puzzle_state_collision_cnt;
	puzzle_solver(input->cmd_args->algorithm, puzzle);
	send_stat_report(puzzle);
	release(input, influxdb, puzzle);
	return (0);
}
