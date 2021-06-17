/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:10:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 10:14:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	print_result_summary(t_statistics *statistics)
{
	int		*counter_values;

	counter_values = statistics->stat_counters.counter_values;
	ft_dprintf(2, "%-28s %d\n", "Puzzle size:", statistics->puzzle_size);
	ft_dprintf(2, "%-28s %s %s\n", "Used algorithm:", statistics->algorithm,
		statistics->algorithm_substring);
	ft_dprintf(2, "%-28s %ld ms\n", "Execution time:",
		get_execution_time(statistics));
	ft_dprintf(2, "%-28s %ld ms\n", "CPU usage time:",
		statistics->cpu_usage_ms);
	ft_dprintf(2, "%-28s %d Mb\n", "Memory usage:",
		counter_values[E_MAX_MEM_USAGE] / 1000);
	ft_dprintf(2, "%-28s %d\n", "Total number of tile moves:",
		counter_values[E_TOTAL_NUM_OF_PUZZLE_STATES]
		+ counter_values[E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS]);
	ft_dprintf(2, "%-28s %d\n", "Number of solution moves:",
		statistics->solution_move_cnt);
	return ;
}

static void	release_logging_strings(t_input *input)
{
	int		i;

	i = -1;
	while (++i < LOGING_LEVELS)
	{
		ft_memdel((void **)&input->level_colors[i]);
		ft_memdel((void **)&input->level_strings[i]);
	}
	ft_memdel((void **)&input->level_colors);
	ft_memdel((void **)&input->level_strings);
	return ;
}

void	release_input(t_input *input)
{
	int		i;

	release_statistics_params(input->statistics);
	release_logging_strings(input);
	i = -1;
	while (++i < input->puzzle_map->size)
		ft_memdel((void **)&input->puzzle_map->tile_map[i]);
	ft_memdel((void **)&input->cmd_args->algorithm);
	ft_memdel((void **)&input->cmd_args->heuristic_algorithm);
	ft_memdel((void **)&input->cmd_args);
	ft_memdel((void **)&input->puzzle_map->tile_map);
	ft_memdel((void **)&input->puzzle_map);
	ft_memdel((void **)&input);
	ft_release_loging_params();
	return ;
}
