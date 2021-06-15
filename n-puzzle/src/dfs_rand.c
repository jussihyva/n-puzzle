/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_rand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/15 12:36:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	fast_rand(void)
{
	static unsigned int		seed;
	static time_t			timer;

	if (!timer)
	{
		time(&timer);
		seed = (unsigned int)timer;
	}
	seed = 214013 * seed + 2531011;
	return ((seed >> 16) & 0x7FFF);
}

static void	set_stat_counters(t_stat_counters *stat_counters,
														int solution_move_cnt)
{
	stat_counters->active_counters[E_NUM_OF_SOLUTION_MOVES] = 1;
	stat_counters->counter_values[E_NUM_OF_SOLUTION_MOVES]
		= solution_move_cnt;
	stat_counters->active_counters[E_TOTAL_NUM_OF_PUZZLE_STATES] = 1;
	stat_counters->counter_values[E_TOTAL_NUM_OF_PUZZLE_STATES]
		= solution_move_cnt;
	return ;
}

void	dfs_no_mem(t_puzzle *puzzle)
{
	t_pos			*pos;
	t_pos			*next_pos;
	int				i;

	pos = puzzle->curr_status->empty_pos;
	while (!check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		i = ft_mod_int(fast_rand(), pos->num_of_neighbors);
		next_pos = pos->neighbors[i];
		if (next_pos)
		{
			tile_move(pos, next_pos, puzzle);
			(*puzzle->solution_move_cnt)++;
			print_puzzle(1, &puzzle->curr_status->tiles_pos_map, puzzle->size);
			if (puzzle->curr_status->tiles_in_right_pos
				== puzzle->num_of_tile_pos)
				break ;
			pos = next_pos;
		}
	}
	set_stat_counters(puzzle->stat_counters, *puzzle->solution_move_cnt);
	return ;
}
