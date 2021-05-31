/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/31 11:25:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos,
													t_list **puzzle_status_lst)
{
	int						is_puzzle_ready;
	int						i;
	t_puzzle_status			*puzzle_status;
	int						is_visited;
	unsigned long			*saved_puzzle_state_map;

	saved_puzzle_state_map = (unsigned long *)
		ft_memalloc(puzzle->curr_status->tiles_pos_map.map_size);
	is_puzzle_ready = 0;
	i = -1;
	while (puzzle->curr_status->depth < puzzle->max_depth && !is_puzzle_ready
		&& ++i < pos->num_of_neighbors)
	{
		ft_memcpy(saved_puzzle_state_map,
			puzzle->curr_status->tiles_pos_map.map,
			puzzle->curr_status->tiles_pos_map.map_size);
		tile_move(pos, pos->neighbors[i], puzzle);
		puzzle->curr_status->depth++;
		is_visited = is_visited_puzzle_status_b_tree(
				&puzzle->curr_status->tiles_pos_map, puzzle, &puzzle_status);
		if (!is_visited || puzzle_status->depth > puzzle->curr_status->depth)
		{
			if (is_visited)
			{
				puzzle_status->depth = puzzle->curr_status->depth;
				puzzle_status->prev_status = puzzle->curr_status->prev_status;
			}
			else
			{
				puzzle_status = save_current_puzzle_status(puzzle->curr_status);
				store_visited_puzzle_status_b_tree(puzzle_status,
					puzzle->bt_root);
				(*puzzle->states_cnt)++;
			}
			puzzle->curr_status->prev_status = puzzle_status;
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], puzzle_status_lst);
			puzzle->curr_status->prev_status = puzzle_status->prev_status;
		}
		ft_memcpy(puzzle->curr_status->tiles_pos_map.map,
			saved_puzzle_state_map,
			puzzle->curr_status->tiles_pos_map.map_size);
		puzzle->curr_status->depth--;
	}
	if (puzzle_status->depth == puzzle->max_depth
		&& puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
		is_puzzle_ready
			= print_solution(puzzle->curr_status->prev_status, puzzle);
	ft_memdel((void **)&saved_puzzle_state_map);
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
		store_visited_puzzle_status_list(puzzle_status, puzzle);
		(*puzzle->states_cnt)++;
		puzzle->curr_status->prev_status = puzzle_status;
		is_puzzle_ready = depth_limited_dfs_mem(puzzle, pos,
				puzzle->puzzle_status_lst);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_bt_remove(puzzle->bt_root, NULL);
		ft_lstdel(puzzle->puzzle_status_lst, delete_puzzle_status);
		puzzle->curr_status->prev_status = NULL;
	}
	*puzzle->solution_move_cnt = puzzle->max_depth;
	puzzle->stat_counters->active_counters[E_NUM_OF_SOLUTION_MOVES] = 1;
	puzzle->stat_counters->counter_values[E_NUM_OF_SOLUTION_MOVES]
		= puzzle->max_depth;
	return ;
}
