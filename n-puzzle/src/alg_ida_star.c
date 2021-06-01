/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_ida_star.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 12:37:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/01 12:24:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_puzzle_status	*n_puzzle_search_algorithm(t_puzzle *puzzle,
						t_puzzle_status *puzzle_status, int *search_pos_index)
{
	t_move				move;
	t_puzzle_status		*next_puzzle_status;
	t_puzzle_status		*dummy_puzzle_status;

	next_puzzle_status = NULL;
	move.to_pos = puzzle_status->empty_pos;
	while (*search_pos_index < move.to_pos->num_of_neighbors)
	{
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		move.from_pos = move.to_pos->neighbors[*search_pos_index];
		tile_move(move.from_pos, move.to_pos, puzzle);
		if (!is_visited_puzzle_status_b_tree(
				&puzzle->curr_status->tiles_pos_map,
				puzzle, &dummy_puzzle_status))
		{
			puzzle->curr_status->depth++;
			puzzle->curr_status->prev_status = puzzle_status;
			next_puzzle_status
				= save_current_puzzle_status(puzzle->curr_status);
			break ;
		}
		(*search_pos_index)++;
	}
	update_current_puzzle_state(puzzle->curr_status, puzzle_status);
	return (next_puzzle_status);
}

static int	ida_star_search_algorithm(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	t_puzzle_status		*selected_puzzle_state;
	t_puzzle_status		*searched_puzzle_state;
	int					search_pos_index;
	t_puzzle_status		*previous_puzzle_state;

	selected_puzzle_state = NULL;
	searched_puzzle_state = NULL;
	previous_puzzle_state = puzzle_status;
	search_pos_index = 0;
	while (!searched_puzzle_state && previous_puzzle_state)
	{
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		puzzle_status = previous_puzzle_state;
		searched_puzzle_state = n_puzzle_search_algorithm(puzzle, puzzle_status,
				&search_pos_index);
		previous_puzzle_state = puzzle->curr_status->prev_status;
		search_pos_index = 0;
	}
	while (searched_puzzle_state)
	{
		if (puzzle->algorithm == E_IDA_STAR)
			searched_puzzle_state->prio
				= calculate_taxicab_based_prio(searched_puzzle_state,
					puzzle->size, puzzle->tile_right_pos_array);
		if (selected_puzzle_state)
		{
			if (selected_puzzle_state->prio > searched_puzzle_state->prio)
			{
				ft_memdel((void **)&selected_puzzle_state);
				selected_puzzle_state = searched_puzzle_state;
			}
			else
				ft_memdel((void **)&searched_puzzle_state);
		}
		else
			selected_puzzle_state = searched_puzzle_state;
		search_pos_index++;
		searched_puzzle_state = n_puzzle_search_algorithm(puzzle, puzzle_status,
				&search_pos_index);
	}
	is_puzzle_ready = 0;
	if (selected_puzzle_state)
	{
		selected_puzzle_state->prev_status = puzzle_status;
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

static void	print_depth_level(int depth)
{
	static int	printed_depth = -1;

	if (printed_depth < depth)
	{
		FT_LOG_INFO("Depth level %d done", depth);
		printed_depth = depth;
	}
	return ;
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
