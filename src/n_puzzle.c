/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 10:19:16 by jkauppi          ###   ########.fr       */
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
			ft_sprintf(string, " %4d", map->tile_table[i][j]);
			ft_strcat(line, string);
		}
		FT_LOG_INFO("%s", line);
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_input			*input;
	t_statistics	*statistics;

	statistics = get_statistics();
	input = (t_input *)ft_memalloc(sizeof(*input));
	set_loging_parameters(input, LOG_TRACE, statistics);
	input->cmd_args = arg_parser(save_cmd_arguments, argc, argv);
	ft_log_set_level(input->cmd_args->loging_level);
	input->puzzle_map = read_puzzle_map();
	print_map(input->puzzle_map);
	dfs(input->puzzle_map, statistics);
	release_input(input);
	return (0);
}
