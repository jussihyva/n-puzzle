/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/30 10:58:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs(t_puzzle *puzzle, t_pos *pos, int depth,
																t_pos *prev_pos)
{
	t_pos					*next_pos;
	int						is_puzzle_ready;
	int						i;

	is_puzzle_ready = 0;
	i = -1;
	while (depth && !is_puzzle_ready && ++i < pos->num_of_neighbors)
	{
		next_pos = pos->neighbors[i];
		if (next_pos != prev_pos)
		{
			tile_move(pos, next_pos, puzzle);
			print_puzzle(1, puzzle->curr_status->tiles_pos_map, puzzle->size);
			is_puzzle_ready = depth_limited_dfs(puzzle, next_pos, depth - 1,
					pos);
			if (!is_puzzle_ready)
			{
				tile_move(next_pos, pos, puzzle);
				print_puzzle(1, puzzle->curr_status->tiles_pos_map,
					puzzle->size);
			}
		}
	}
	if (!depth && puzzle->curr_status->right_pos_status
		== puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
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
	while (!is_puzzle_ready && ++depth < INT_MAX)
	{
		is_puzzle_ready = depth_limited_dfs(puzzle, pos, depth, NULL);
		FT_LOG_INFO("Depth level %2d done", depth);
	}
	*puzzle->solution_move_cnt = depth + 1;
	return ;
}
