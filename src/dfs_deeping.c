/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 17:51:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs(t_puzzle *puzzle, t_pos *pos,
									unsigned int right_pos_status, int depth)
{
	static unsigned int		puzzle_ready = 0;
	t_pos					*next_pos;
	int						is_puzzle_ready;
	int						i;

	if (!puzzle_ready)
		puzzle_ready = (1 << (puzzle->size * puzzle->size)) - 1;
	is_puzzle_ready = 0;
	if (depth)
	{
		i = -1;
		while (!is_puzzle_ready && ++i < pos->num_of_neighbors)
		{
			next_pos = pos->neighbors[i];
			if (next_pos != pos->prev_tile)
			{
				tile_num_swap(pos, next_pos, puzzle->move_cnt);
				print_puzzle(1, puzzle);
				update_right_pos_status(pos, next_pos, &right_pos_status);
				FT_LOG_DEBUG("Right position status: %u", right_pos_status);
				next_pos->prev_tile = pos;
				is_puzzle_ready = depth_limited_dfs(puzzle, next_pos,
						right_pos_status, depth - 1);
				if (!is_puzzle_ready)
				{
					tile_num_swap(next_pos, pos, puzzle->move_cnt);
					print_puzzle(1, puzzle);
					update_right_pos_status(pos, next_pos, &right_pos_status);
					FT_LOG_DEBUG("Right position status: %u", right_pos_status);
				}
			}
		}
	}
	else
	{
		if (right_pos_status == puzzle_ready)
			is_puzzle_ready = 1;
	}
	return (is_puzzle_ready);
}

void	dfs_deeping(t_puzzle *puzzle, t_statistics *statistics)
{
	t_pos			*pos;
	int				depth;
	unsigned int	puzzle_ready;
	int				is_puzzle_ready;

	puzzle_ready = (1 << (puzzle->size * puzzle->size)) - 1;
	FT_LOG_DEBUG("Righ position status: %u", puzzle->right_pos_status);
	pos = puzzle->empty_pos;
	is_puzzle_ready = 0;
	depth = -1;
	while (!is_puzzle_ready && ++depth < INT_MAX)
	{
		FT_LOG_DEBUG("Righ position status: %u", puzzle->right_pos_status);
		pos->prev_tile = NULL;
		is_puzzle_ready = depth_limited_dfs(puzzle, pos,
				puzzle->right_pos_status, depth);
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
