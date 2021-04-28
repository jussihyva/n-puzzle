/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/28 12:53:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	print_map(t_map *map)
{
	int		i;
	int		j;
	char	line[1000];
	char	string[6];

	FT_LOG_INFO(" %d", map->size);
	i = -1;
	while (++i < map->size)
	{
		ft_bzero(line, sizeof(line));
		j = -1;
		while (++j < map->size)
		{
			ft_sprintf(string, " %4d", map->tile_map[i][j]);
			ft_strcat(line, string);
		}
		FT_LOG_INFO("%s", line);
	}
	return ;
}

static void	send_stat_report(t_puzzle *puzzle)
{
	stat_set_end_time(puzzle->statistics);
	stat_update_cpu_usage(puzzle->statistics);
	puzzle->statistics->puzzle_states = puzzle->status_count;
	puzzle->statistics->order = E_SEND_TO_INFLUXDB;
	FT_LOG_INFO("Execution time : %ld", get_execution_time(puzzle->statistics));
	puzzle->statistics->order = E_NONE;
	FT_LOG_INFO("Total num of moves: %lu", *puzzle->move_cnt);
	return ;
}

int	main(int argc, char **argv)
{
	t_input				*input;
	t_statistics		*statistics;
	t_influxdb			*influxdb;
	t_puzzle			*puzzle;

	statistics = initialize_statistics();
	input = read_input_data(argc, argv, statistics);
	influxdb = setup_influxdb_connection("127.0.0.1", "8086");
	statistics->connection = (t_tls_connection *)influxdb->connection;
	statistics->puzzle_size = input->puzzle_map->size;
	print_map(input->puzzle_map);
	puzzle = initialize_puzzle(input);
	puzzle->move_cnt = &statistics->tile_move_cnt;
	if (!ft_strncmp(input->cmd_args->algorithm, "dfs", 3))
		dfs(puzzle);
	else if (!ft_strncmp(input->cmd_args->algorithm, "bfs", 3))
		bfs(puzzle);
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", input->cmd_args->algorithm,
			"Specify a valid algorithm with the param -A");
	send_stat_report(puzzle);
	if (input->cmd_args->release)
		ft_printf("END\n");
	release_puzzle(puzzle);
	release_influxdb(influxdb);
	stat_update_cpu_usage(statistics);
	release_input(input);
	return (0);
}
