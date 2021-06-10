/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:32:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/10 12:52:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	conv_str_to_int(const char opt, const char *s)
{
	char		*remainings;
	int			value;

	value = ft_strtoi(s, &remainings, 10);
	if (*remainings || errno != 0)
	{
		FT_LOG_ERROR("Not valid parameter value -%c %s", opt, s);
		exit(42);
	}
	if (value < 0)
	{
		FT_LOG_ERROR("Negative value is not allowed -%c %s", opt, s);
		exit(42);
	}
	return (value);
}

void	save_cmd_arguments(t_cmd_args *cmd_args, char opt, char *next_arg)
{
	if (opt == 'L')
		cmd_args->loging_level = conv_str_to_int(opt, next_arg);
	else if (opt == 'D')
		cmd_args->print_delay = conv_str_to_int(opt, next_arg);
	else if (opt == 'A')
	{
		ft_strdel(&cmd_args->algorithm);
		cmd_args->algorithm = ft_strdup(next_arg);
	}
	else if (opt == 'H')
	{
		ft_strdel(&cmd_args->heuristic_algorithm);
		cmd_args->heuristic_algorithm = ft_strdup(next_arg);
	}
	else if (opt == 'f')
		cmd_args->input_file = ft_strdup(next_arg);
	else if (opt == 'r')
		cmd_args->release = 1;
	return ;
}

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

void	release_input(t_input *input)
{
	int		i;

	release_statistics_params(input->statistics);
	i = -1;
	while (++i < LOGING_LEVELS)
	{
		ft_memdel((void **)&input->level_colors[i]);
		ft_memdel((void **)&input->level_strings[i]);
	}
	ft_memdel((void **)&input->level_colors);
	ft_memdel((void **)&input->level_strings);
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
