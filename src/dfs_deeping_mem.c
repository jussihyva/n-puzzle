/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/09 15:09:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos, int depth,
											t_list **visited_puzzle_statuses)
{
	int						is_puzzle_ready;
	unsigned long			puzzle_status;
	int						i;

	is_puzzle_ready = 0;
	puzzle_status = create_puzzle_status(puzzle);
	if (!is_visited_puzzle_status(puzzle_status, visited_puzzle_statuses,
			depth))
	{
		i = -1;
		while (depth < puzzle->max_depth && !is_puzzle_ready
			&& ++i < pos->num_of_neighbors)
		{
			tile_move(pos, pos->neighbors[i], puzzle);
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], depth + 1, visited_puzzle_statuses);
			if (!is_puzzle_ready)
				tile_move(pos->neighbors[i], pos, puzzle);
		}
		if (depth == puzzle->max_depth && puzzle->right_pos_status
			== puzzle->puzzle_ready_status)
			is_puzzle_ready = 1;
	}
	return (is_puzzle_ready);
}

void	dfs_deeping_mem(t_puzzle *puzzle)
{
	t_pos			*pos;
	int				depth;
	int				is_puzzle_ready;
	t_list			**visited_puzzle_statuses;

	visited_puzzle_statuses
		= (t_list **)ft_memalloc(sizeof(*visited_puzzle_statuses));
	pos = puzzle->tile_array[0]->curr_pos;
	is_puzzle_ready = 0;
	puzzle->max_depth = -1;
	depth = 0;
	while (!is_puzzle_ready && ++puzzle->max_depth < INT_MAX)
	{
		pos->prev_tile = NULL;
		is_puzzle_ready = depth_limited_dfs_mem(puzzle, pos, depth,
				visited_puzzle_statuses);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_lstdel(visited_puzzle_statuses, delete_puzzle_status);
	}
	return ;
}