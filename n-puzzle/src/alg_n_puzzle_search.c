/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_n_puzzle_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:32:41 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 14:33:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

t_puzzle_status	*alg_n_puzzle_search_state(t_puzzle *puzzle,
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
