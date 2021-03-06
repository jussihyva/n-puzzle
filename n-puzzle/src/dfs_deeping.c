/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 10:06:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	check_is_puzzle_ready(int depth, t_puzzle *puzzle)
{
	int			is_puzzle_ready;

	if (!depth && puzzle->curr_status->tiles_in_right_pos
		== puzzle->num_of_tile_pos)
		is_puzzle_ready = 1;
	else
		is_puzzle_ready = 0;
	return (is_puzzle_ready);
}

static int	depth_limited_dfs(t_puzzle *puzzle, t_pos *pos, int depth,
																t_pos *prev_pos)
{
	t_pos					*next_pos;
	int						is_puzzle_ready;
	int						i;

	i = -1;
	while (depth && !is_puzzle_ready && ++i < pos->num_of_neighbors
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		next_pos = pos->neighbors[i];
		if (next_pos != prev_pos)
		{
			tile_move(pos, next_pos, puzzle);
			print_puzzle(1, &puzzle->curr_status->tiles_pos_map, puzzle->size);
			is_puzzle_ready = depth_limited_dfs(puzzle, next_pos, depth - 1,
					pos);
			if (!is_puzzle_ready)
			{
				tile_move(next_pos, pos, puzzle);
				print_puzzle(1, &puzzle->curr_status->tiles_pos_map,
					puzzle->size);
			}
		}
	}
	is_puzzle_ready = check_is_puzzle_ready(depth, puzzle);
	return (is_puzzle_ready);
}

void	dfs_deeping(t_puzzle *puzzle)
{
	t_pos			*pos;
	int				depth;
	int				is_puzzle_ready;

	pos = puzzle->curr_status->empty_pos;
	is_puzzle_ready = 0;
	depth = -1;
	while (!is_puzzle_ready && ++depth < INT_MAX
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		is_puzzle_ready = depth_limited_dfs(puzzle, pos, depth, NULL);
		FT_LOG_INFO("Depth level %2d done", depth);
	}
	*puzzle->solution_move_cnt = depth;
	puzzle->stat_counters->active_counters[E_NUM_OF_SOLUTION_MOVES] = 1;
	puzzle->stat_counters->counter_values[E_NUM_OF_SOLUTION_MOVES] = depth;
	return ;
}
