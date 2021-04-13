/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/13 09:00:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos, int depth,
											t_list **tiles_status_map_lst)
{
	int						is_puzzle_ready;
	int						i;
	t_puzzle_status			*puzzle_status;

	is_puzzle_ready = 0;
	if (!is_visited_puzzle_status(puzzle->curr_status->tiles_status_map,
			tiles_status_map_lst, depth))
	{
		puzzle_status = create_puzzle_status(puzzle->curr_status->pos_table,
				puzzle->curr_status->tiles_status_map, depth,
				puzzle->curr_status->empty_pos);
		add_visited_puzzle_status(puzzle_status, tiles_status_map_lst);
		i = -1;
		while (depth < puzzle->max_depth && !is_puzzle_ready
			&& ++i < pos->num_of_neighbors)
		{
			tile_move(pos, pos->neighbors[i], puzzle);
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], depth + 1, tiles_status_map_lst);
			if (!is_puzzle_ready)
				tile_move(pos->neighbors[i], pos, puzzle);
		}
		if (depth == puzzle->max_depth && puzzle->curr_status->right_pos_status
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

	pos = puzzle->curr_status->empty_pos;
	is_puzzle_ready = 0;
	puzzle->max_depth = -1;
	depth = 0;
	while (!is_puzzle_ready && ++puzzle->max_depth < INT_MAX)
	{
		is_puzzle_ready = depth_limited_dfs_mem(puzzle, pos, depth,
				puzzle->tiles_status_map_lst);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_lstdel(puzzle->tiles_status_map_lst, delete_puzzle_status);
	}
	return ;
}
