/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_ida_star.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 12:37:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/27 18:43:59 by jkauppi          ###   ########.fr       */
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
		// ft_memcpy(puzzle->curr_status, puzzle_status,
		// 	sizeof(*puzzle->curr_status));
		ft_memcpy(puzzle->curr_status->tiles_pos_map.map, puzzle_status->tiles_pos_map.map, puzzle->curr_status->tiles_pos_map.map_size);
		ft_memcpy(&puzzle->curr_status->right_pos_status, &puzzle_status->right_pos_status, sizeof(puzzle->curr_status->right_pos_status));
		move.from_pos = move.to_pos->neighbors[*search_pos_index];
		tile_move(move.from_pos, move.to_pos, puzzle);
		puzzle->curr_status->depth++;
		if (!is_visited_puzzle_status_b_tree(
				&puzzle->curr_status->tiles_pos_map,
				puzzle, &dummy_puzzle_status))
		{
			next_puzzle_status
				= save_current_puzzle_status(puzzle->curr_status);
			break ;
		}
		(*search_pos_index)++;
	}
	// ft_memcpy(puzzle->curr_status, puzzle_status, sizeof(*puzzle->curr_status));
	ft_memcpy(puzzle->curr_status->tiles_pos_map.map, puzzle_status->tiles_pos_map.map, puzzle->curr_status->tiles_pos_map.map_size);
	ft_memcpy(&puzzle->curr_status->right_pos_status, &puzzle_status->right_pos_status, sizeof(puzzle->curr_status->right_pos_status));
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
		// ft_memcpy(puzzle->curr_status, previous_puzzle_state,
		// 	sizeof(*puzzle->curr_status));
		ft_memcpy(puzzle->curr_status->tiles_pos_map.map, puzzle_status->tiles_pos_map.map, puzzle->curr_status->tiles_pos_map.map_size);
		ft_memcpy(&puzzle->curr_status->right_pos_status, &puzzle_status->right_pos_status, sizeof(puzzle->curr_status->right_pos_status));
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
		if (selected_puzzle_state->right_pos_status
			== puzzle->puzzle_ready_status)
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
	if (puzzle->curr_status->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	puzzle_status = save_current_puzzle_status(puzzle->curr_status);
	ft_prio_enqueue(puzzle->states_prio_queue, &puzzle_status->prio,
		(void *)puzzle_status);
	puzzle_status->is_in_queue = 1;
	store_visited_puzzle_status_b_tree(puzzle_status, puzzle->bt_root);
	(*puzzle->states_cnt)++;
	while (!is_puzzle_ready && *puzzle->states_prio_queue)
	{
		puzzle_status
			= (t_puzzle_status *)ft_prio_dequeue(puzzle->states_prio_queue);
		puzzle_status->is_in_queue = 0;
		ft_memcpy(puzzle->curr_status, puzzle_status,
			sizeof(*puzzle->curr_status));
		puzzle->curr_status->tiles_pos_map.map
			= (unsigned long *)ft_memalloc(puzzle->curr_status->tiles_pos_map.map_size);
		ft_memcpy(puzzle->curr_status->tiles_pos_map.map, puzzle_status->tiles_pos_map.map,
			puzzle->curr_status->tiles_pos_map.map_size);
		puzzle->curr_status->prev_status = puzzle_status;
		// print_puzzle(1, puzzle_status->tiles_pos_map, puzzle->size);
		is_puzzle_ready = ida_star_search_algorithm(puzzle, puzzle_status);
		print_depth_level(puzzle->curr_status->depth);
	}
	return ;
}
