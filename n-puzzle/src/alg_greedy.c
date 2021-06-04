/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_greedy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:42:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/04 17:45:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	select_next_puzzle_state(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	t_puzzle_status		*available_puzzle_state;
	int					search_pos_index;
	int					is_puzzle_ready;

	is_puzzle_ready = 0;
	search_pos_index = 0;
	available_puzzle_state = alg_n_puzzle_search_state(puzzle, puzzle_status,
			&search_pos_index);
	while (available_puzzle_state && !is_puzzle_ready)
	{
		available_puzzle_state->prio = calculate_taxicab_distance(
				&available_puzzle_state->tiles_pos_map, puzzle->size,
				puzzle->tile_right_pos_array);
		add_puzzle_state_to_prio_queue_1(available_puzzle_state,
			puzzle->states_prio_queue);
		store_visited_puzzle_status_b_tree(available_puzzle_state,
			puzzle->bt_root);
		(*puzzle->states_cnt)++;
		if (available_puzzle_state->tiles_in_right_pos
			== puzzle->num_of_tile_pos)
			is_puzzle_ready = print_solution(available_puzzle_state, puzzle);
		search_pos_index++;
		available_puzzle_state = alg_n_puzzle_search_state(puzzle,
				puzzle_status, &search_pos_index);
	}
	return (is_puzzle_ready);
}

static int	greedy_search_algorithm(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;

	(void)puzzle;
	(void)puzzle_status;
	is_puzzle_ready = select_next_puzzle_state(puzzle, puzzle_status);
	return (is_puzzle_ready);
}

void	alg_greedy(t_puzzle *puzzle)
{
	int					is_puzzle_ready;
	t_puzzle_status		*puzzle_status;

	is_puzzle_ready = 0;
	if (puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
		is_puzzle_ready = 1;
	puzzle_status = save_current_puzzle_status(puzzle->curr_status);
	ft_prio_enqueue(puzzle->states_prio_queue, &puzzle_status->prio,
		(void *)puzzle_status);
	puzzle_status->is_in_queue = 1;
	store_visited_puzzle_status_b_tree(puzzle_status, puzzle->bt_root);
	(*puzzle->states_cnt)++;
	while (!is_puzzle_ready && *puzzle->states_prio_queue
		&& !puzzle->stat_counters->counter_values[E_IS_MEM_LIMIT_REACHED]
		&& !puzzle->stat_counters->counter_values[E_IS_TIME_LIMIT_REACHED])
	{
		puzzle_status
			= (t_puzzle_status *)ft_prio_dequeue(puzzle->states_prio_queue);
		puzzle_status->is_in_queue = 0;
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		is_puzzle_ready = greedy_search_algorithm(puzzle, puzzle_status);
		print_depth_level(puzzle->curr_status->depth);
	}
	return ;
}
