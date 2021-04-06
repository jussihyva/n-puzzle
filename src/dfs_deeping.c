/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/06 15:42:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs(t_puzzle *puzzle, t_pos *pos, int depth)
{
	t_pos					*next_pos;
	int						is_puzzle_ready;
	int						i;

	is_puzzle_ready = 0;
	i = -1;
	while (depth && !is_puzzle_ready && ++i < pos->num_of_neighbors)
	{
		next_pos = pos->neighbors[i];
		if (next_pos != pos->prev_tile)
		{
			tile_num_swap(pos, next_pos, puzzle);
			next_pos->prev_tile = pos;
			is_puzzle_ready = depth_limited_dfs(puzzle, next_pos, depth - 1);
			if (!is_puzzle_ready)
			{
				tile_num_swap(next_pos, pos, puzzle);
				next_pos->prev_tile = NULL;
			}
		}
	}
	if (!depth && puzzle->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	return (is_puzzle_ready);
}

void	dfs_deeping(t_puzzle *puzzle, t_statistics *statistics)
{
	t_pos			*pos;
	int				depth;
	int				is_puzzle_ready;

	pos = puzzle->tile_array[0]->curr_pos;
	is_puzzle_ready = 0;
	depth = -1;
	while (!is_puzzle_ready && ++depth < INT_MAX)
	{
		pos->prev_tile = NULL;
		is_puzzle_ready = depth_limited_dfs(puzzle, pos, depth);
		FT_LOG_INFO("Depth level %2d done", depth);
	}
	set_end_time();
	statistics->order = E_SEND_TO_INFLUXDB;
	statistics->algorithm_substring = ft_strdup("deeping");
	FT_LOG_INFO("Execution time : %ld", get_execution_time());
	statistics->order = E_NONE;
	FT_LOG_INFO("Total num of moves: %lu", *puzzle->move_cnt);
	return ;
}
