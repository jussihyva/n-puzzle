/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/15 22:18:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos,
				t_puzzle_status *prev_puzzle_status, t_list **puzzle_status_lst)
{
	int						is_puzzle_ready;
	int						i;
	t_puzzle_status			*puzzle_status;
	unsigned int			saved_right_pos_status;
	unsigned long			saved_tiles_pos_map;

	is_puzzle_ready = 0;
	add_visited_puzzle_status(prev_puzzle_status, puzzle_status_lst);
	i = -1;
	while (prev_puzzle_status->depth < puzzle->max_depth && !is_puzzle_ready
		&& ++i < pos->num_of_neighbors)
	{
		saved_right_pos_status = puzzle->curr_status->right_pos_status;
		saved_tiles_pos_map = puzzle->curr_status->tiles_pos_map;
		tile_move(pos, pos->neighbors[i], puzzle);
		if (!is_visited_puzzle_status(puzzle->curr_status->tiles_pos_map,
				puzzle_status_lst, prev_puzzle_status->depth + 1))
		{
			puzzle_status
				= create_puzzle_status(puzzle->curr_status->tiles_pos_map,
					prev_puzzle_status, puzzle->curr_status->empty_pos,
					puzzle->curr_status->right_pos_status);
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], puzzle_status, puzzle_status_lst);
		}
		if (!is_puzzle_ready)
		{
			puzzle->curr_status->right_pos_status = saved_right_pos_status;
			puzzle->curr_status->tiles_pos_map = saved_tiles_pos_map;
			print_puzzle(1, puzzle);
		}
	}
	if (prev_puzzle_status->depth == puzzle->max_depth
		&& puzzle->curr_status->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	return (is_puzzle_ready);
}

void	dfs_deeping_mem(t_puzzle *puzzle)
{
	t_pos				*pos;
	int					depth;
	int					is_puzzle_ready;
	t_puzzle_status		*puzzle_status;

	pos = puzzle->curr_status->empty_pos;
	is_puzzle_ready = 0;
	puzzle->max_depth = -1;
	depth = 0;
	while (!is_puzzle_ready && ++puzzle->max_depth < INT_MAX)
	{
		puzzle_status = create_puzzle_status(puzzle->curr_status->tiles_pos_map,
				NULL, puzzle->curr_status->empty_pos,
				puzzle->curr_status->right_pos_status);
		is_puzzle_ready = depth_limited_dfs_mem(puzzle, pos, puzzle_status,
				puzzle->puzzle_status_lst);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_lstdel(puzzle->puzzle_status_lst, delete_puzzle_status);
	}
	return ;
}
