/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:19:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 13:08:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_puzzle_status	*add_next_status_to_queue_1(t_puzzle *puzzle)
{
	t_puzzle_status		*next_status;

	if (is_visited_puzzle_status_list(&puzzle->curr_status->tiles_pos_map,
			puzzle, &next_status))
		next_status = NULL;
	else
	{
		next_status = save_current_puzzle_status(puzzle->curr_status);
		ft_enqueue(puzzle->status_queue, (void *)next_status);
		next_status->is_in_queue = 1;
		store_visited_puzzle_status_list(next_status, puzzle);
	}
	return (next_status);
}

static t_puzzle_status	*add_next_status_to_queue_2(t_puzzle *puzzle)
{
	t_puzzle_status		*next_status;

	if (is_visited_puzzle_status_b_tree(&puzzle->curr_status->tiles_pos_map,
			puzzle, &next_status))
		next_status = NULL;
	else
	{
		next_status = save_current_puzzle_status(puzzle->curr_status);
		ft_enqueue(puzzle->status_queue, (void *)next_status);
		next_status->is_in_queue = 1;
		store_visited_puzzle_status_b_tree(next_status, puzzle);
	}
	return (next_status);
}

static int	breadth_first_search(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	int					i;
	t_move				move;
	t_puzzle_status		*curr_status;

	is_puzzle_ready = 0;
	i = -1;
	curr_status = puzzle->curr_status;
	move.to_pos = curr_status->empty_pos;
	while (!is_puzzle_ready && ++i < move.to_pos->num_of_neighbors)
	{
		move.from_pos = move.to_pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		curr_status->depth++;
		puzzle->curr_status->prev_status = puzzle_status;
		if (puzzle->algorithm == E_BFS_1)
			add_next_status_to_queue_1(puzzle);
		else
			add_next_status_to_queue_2(puzzle);
		if (puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
			is_puzzle_ready = print_solution(curr_status, puzzle);
		update_current_puzzle_state(curr_status, puzzle_status);
	}
	return (is_puzzle_ready);
}

void	bfs_1(t_puzzle *puzzle)
{
	int					is_puzzle_ready;
	t_puzzle_status		*puzzle_status;

	puzzle->max_depth = -1;
	is_puzzle_ready = 0;
	if (puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
		is_puzzle_ready = 1;
	if (puzzle->algorithm == E_BFS_1)
		add_next_status_to_queue_1(puzzle);
	else
		add_next_status_to_queue_2(puzzle);
	while (!is_puzzle_ready && !ft_is_queue_empty(puzzle->status_queue)
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		puzzle_status = (t_puzzle_status *)ft_dequeue(puzzle->status_queue);
		puzzle_status->is_in_queue = 0;
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		is_puzzle_ready = breadth_first_search(puzzle, puzzle_status);
		print_depth_level(puzzle->curr_status->depth);
	}
	*puzzle->solution_move_cnt = puzzle->curr_status->depth + 1;
	puzzle->stat_counters->active_counters[E_NUM_OF_SOLUTION_MOVES] = 1;
	puzzle->stat_counters->counter_values[E_NUM_OF_SOLUTION_MOVES]
		= puzzle->curr_status->depth + 1;
}
