/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_ida_star.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 12:37:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/04 15:20:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_puzzle_status	*select_next_puzzle_state(
					t_puzzle_status *available_puzzle_state, t_puzzle *puzzle,
					t_puzzle_status *puzzle_status)
{
	t_puzzle_status		*selected_puzzle_state;
	int					search_pos_index;

	selected_puzzle_state = NULL;
	search_pos_index = 0;
	while (available_puzzle_state)
	{
		taxicab_based_selection(puzzle, available_puzzle_state,
			&selected_puzzle_state);
		search_pos_index++;
		available_puzzle_state = alg_n_puzzle_search_state(puzzle,
				puzzle_status, &search_pos_index);
	}
	return (selected_puzzle_state);
}

static t_puzzle_status	*search_first_state(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	t_puzzle_status		*searched_puzzle_state;
	int					search_pos_index;

	search_pos_index = 0;
	searched_puzzle_state = NULL;
	searched_puzzle_state = alg_n_puzzle_search_state(puzzle, puzzle_status,
			&search_pos_index);
	while (!searched_puzzle_state)
	{
		puzzle_status = puzzle->curr_status->prev_status;
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		searched_puzzle_state = alg_n_puzzle_search_state(puzzle, puzzle_status,
				&search_pos_index);
		search_pos_index = 0;
	}
	return (searched_puzzle_state);
}

static int	ida_star_search_algorithm(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	t_puzzle_status		*selected_puzzle_state;
	t_puzzle_status		*searched_puzzle_state;
	int					search_pos_index;

	search_pos_index = 0;
	searched_puzzle_state = search_first_state(puzzle, puzzle_status);
	search_pos_index = 0;
	selected_puzzle_state = select_next_puzzle_state(searched_puzzle_state,
			puzzle, puzzle_status);
	is_puzzle_ready = 0;
	if (selected_puzzle_state)
	{
		add_puzzle_state_to_prio_queue_1(selected_puzzle_state,
			puzzle->states_prio_queue);
		store_visited_puzzle_status_b_tree(selected_puzzle_state,
			puzzle->bt_root);
		(*puzzle->states_cnt)++;
		if (selected_puzzle_state->tiles_in_right_pos
			== puzzle->num_of_tile_pos)
			is_puzzle_ready = print_solution(selected_puzzle_state, puzzle);
	}
	return (is_puzzle_ready);
}

void	alg_ida_star(t_puzzle *puzzle)
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
		is_puzzle_ready = ida_star_search_algorithm(puzzle, puzzle_status);
		print_depth_level(puzzle->curr_status->depth);
	}
	return ;
}
