/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/05 10:10:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos,
													t_list **puzzle_status_lst)
{
	int						is_puzzle_ready;
	int						i;
	unsigned int			saved_right_pos_status;
	unsigned long			saved_tiles_pos_map;
	t_puzzle_status			*puzzle_status;

	is_puzzle_ready = 0;
	i = -1;
	while (puzzle->curr_status->depth < puzzle->max_depth && !is_puzzle_ready
		&& ++i < pos->num_of_neighbors)
	{
		saved_right_pos_status = puzzle->curr_status->right_pos_status;
		saved_tiles_pos_map = puzzle->curr_status->tiles_pos_map;
		tile_move(pos, pos->neighbors[i], puzzle);
		puzzle->curr_status->depth++;
		print_puzzle(1, puzzle->curr_status->tiles_pos_map, puzzle->size);
		if (!is_visited_puzzle_status_b_tree(puzzle->curr_status->tiles_pos_map,
				puzzle, puzzle->curr_status->depth))
		{
			puzzle_status = save_current_puzzle_status(puzzle->curr_status);
			add_visited_puzzle_status(puzzle_status, puzzle);
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], puzzle_status_lst);
		}
		puzzle->curr_status->right_pos_status = saved_right_pos_status;
		puzzle->curr_status->tiles_pos_map = saved_tiles_pos_map;
		if (!is_puzzle_ready)
			print_puzzle(1, puzzle->curr_status->tiles_pos_map, puzzle->size);
		puzzle->curr_status->depth--;
	}
	if (puzzle_status->depth == puzzle->max_depth
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
		puzzle_status = save_current_puzzle_status(puzzle->curr_status);
		add_visited_puzzle_status(puzzle_status, puzzle);
		is_puzzle_ready = depth_limited_dfs_mem(puzzle, pos,
				puzzle->puzzle_status_lst);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_bt_remove(puzzle->bt_root, NULL);
		ft_lstdel(puzzle->puzzle_status_lst, delete_puzzle_status);
	}
	*puzzle->solution_move_cnt = puzzle->max_depth + 1;
	return ;
}
