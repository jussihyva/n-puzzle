/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/11 19:15:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos, int depth,
											t_list **puzzle_status_lst)
{
	int						is_puzzle_ready;
	unsigned long			tiles_status_map;
	int						i;
	t_puzzle_status			*puzzle_status;

	is_puzzle_ready = 0;
	tiles_status_map = create_tiles_status_map(puzzle->curr_status->pos_table,
			puzzle->size);
	if (!is_visited_puzzle_status(tiles_status_map, puzzle_status_lst,
			depth))
	{
		puzzle_status = create_puzzle_status(puzzle->curr_status->pos_table,
				tiles_status_map, depth);
		add_visited_puzzle_status(puzzle_status, puzzle_status_lst);
		i = -1;
		while (depth < puzzle->max_depth && !is_puzzle_ready
			&& ++i < pos->num_of_neighbors)
		{
			tile_move(pos, pos->neighbors[i], puzzle);
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], depth + 1, puzzle_status_lst);
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
	t_list			**puzzle_status_lst;

	puzzle_status_lst
		= (t_list **)ft_memalloc(sizeof(*puzzle_status_lst));
	pos = puzzle->empty_pos;
	is_puzzle_ready = 0;
	puzzle->max_depth = -1;
	depth = 0;
	while (!is_puzzle_ready && ++puzzle->max_depth < INT_MAX)
	{
		is_puzzle_ready = depth_limited_dfs_mem(puzzle, pos, depth,
				puzzle_status_lst);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_lstdel(puzzle_status_lst, delete_puzzle_status);
	}
	return ;
}
