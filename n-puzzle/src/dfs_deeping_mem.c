/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_deeping_mem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 20:12:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 13:08:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	check_is_puzzle_ready(int *is_puzzle_ready, t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	if (puzzle_status->depth == puzzle->max_depth
		&& puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
		*is_puzzle_ready
			= print_solution(puzzle->curr_status->prev_status, puzzle);
	return ;
}

static void	update_puzzle_state(int is_visited, t_puzzle *puzzle,
												t_puzzle_status **puzzle_status)
{
	if (is_visited)
	{
		(*puzzle_status)->depth = puzzle->curr_status->depth;
		(*puzzle_status)->prev_status = puzzle->curr_status->prev_status;
	}
	else
	{
		*puzzle_status = save_current_puzzle_status(puzzle->curr_status);
		store_visited_puzzle_status_b_tree(*puzzle_status, puzzle);
	}
	return ;
}

static int	depth_limited_dfs_mem(t_puzzle *puzzle, t_pos *pos,
					t_list **puzzle_status_lst, t_puzzle_status *puzzle_status)
{
	int						is_puzzle_ready;
	int						i;
	int						is_visited;

	is_puzzle_ready = 0;
	i = -1;
	while (puzzle->curr_status->depth < puzzle->max_depth && !is_puzzle_ready
		&& ++i < pos->num_of_neighbors
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		tile_move(pos, pos->neighbors[i], puzzle);
		puzzle->curr_status->depth++;
		is_visited = is_visited_puzzle_status_b_tree(
				&puzzle->curr_status->tiles_pos_map, puzzle, &puzzle_status);
		if (!is_visited || puzzle_status->depth > puzzle->curr_status->depth)
		{
			update_puzzle_state(is_visited, puzzle, &puzzle_status);
			is_puzzle_ready = depth_limited_dfs_mem(puzzle,
					pos->neighbors[i], puzzle_status_lst, puzzle_status);
		}
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
	}
	check_is_puzzle_ready(&is_puzzle_ready, puzzle, puzzle_status);
	return (is_puzzle_ready);
}

void	dfs_deeping_mem(t_puzzle *puzzle)
{
	int					depth;
	int					is_puzzle_ready;
	t_puzzle_status		*puzzle_status;

	is_puzzle_ready = 0;
	puzzle->max_depth = -1;
	depth = 0;
	while (!is_puzzle_ready && ++puzzle->max_depth < INT_MAX
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		puzzle_status = save_current_puzzle_status(puzzle->curr_status);
		store_visited_puzzle_status_list(puzzle_status, puzzle);
		puzzle->curr_status->prev_status = puzzle_status;
		is_puzzle_ready = depth_limited_dfs_mem(puzzle,
				puzzle->curr_status->empty_pos,
				puzzle->puzzle_status_lst, puzzle_status);
		FT_LOG_INFO("Depth level %2d done", puzzle->max_depth);
		ft_bt_remove(puzzle->bt_root, NULL, delete_puzzle_status);
		ft_lstdel(puzzle->puzzle_status_lst, delete_puzzle_status);
		puzzle->curr_status->prev_status = NULL;
	}
	*puzzle->solution_move_cnt = puzzle->max_depth;
	puzzle->stat_counters->active_counters[E_NUM_OF_SOLUTION_MOVES] = 1;
	puzzle->stat_counters->counter_values[E_NUM_OF_SOLUTION_MOVES]
		= puzzle->max_depth;
}
