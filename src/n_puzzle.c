/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/05 12:30:23 by jkauppi          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_input				*input;
	t_statistics		*statistics;
	t_influxdb			*influxdb;
	t_puzzle			*puzzle;

	statistics = get_statistics();
	input = read_input_data(argc, argv, statistics);
	influxdb = setup_influxdb_connection("127.0.0.1", "8086");
	set_connection(influxdb->connection);
	set_puzzle_size(input->puzzle_map->size);
	print_map(input->puzzle_map);
	puzzle = initialize_puzzle(input->puzzle_map);
	puzzle->move_cnt = &statistics->tile_move_cnt;
	if (!ft_strncmp(input->cmd_args->algorithm, "dfs", 3))
		dfs(puzzle, statistics, input->cmd_args);
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", input->cmd_args->algorithm,
			"Specify a valid algorithm with the param -A");
	release_influxdb(influxdb);
	release_input(input);
	return (0);
}
