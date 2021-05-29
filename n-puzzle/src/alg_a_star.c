/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_a_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:06:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/29 17:38:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	n_puzzle_search_algorithm(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	int					i;
	t_move				move;

	is_puzzle_ready = 0;
	i = -1;
	move.to_pos = puzzle->curr_status->empty_pos;
	while (!is_puzzle_ready && ++i < move.to_pos->num_of_neighbors)
	{
		move.from_pos = move.to_pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		puzzle->curr_status->depth++;
		if (puzzle->algorithm == E_A_STAR_T)
			puzzle->curr_status->prio
				= calculate_taxicab_based_prio(puzzle->curr_status,
					puzzle->size, puzzle->tile_right_pos_array);
		puzzle->curr_status->prev_status = puzzle_status;
		add_puzzle_state_to_prio_queue(puzzle);
		if (puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
			is_puzzle_ready = print_solution(puzzle->curr_status, puzzle);
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
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

void	alg_a_star(t_puzzle *puzzle)
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
	while (!is_puzzle_ready && *puzzle->states_prio_queue)
	{
		puzzle_status
			= (t_puzzle_status *)ft_prio_dequeue(puzzle->states_prio_queue);
		puzzle_status->is_in_queue = 0;
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		is_puzzle_ready = n_puzzle_search_algorithm(puzzle, puzzle_status);
		print_depth_level(puzzle->curr_status->depth);
	}
	return ;
}
