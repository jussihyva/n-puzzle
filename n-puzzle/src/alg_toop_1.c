/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_toop_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:55:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/27 14:40:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_puzzle_status	*add_state_to_prio_queue_1(t_puzzle *puzzle)
{
	t_puzzle_status		*puzzle_status;

	if (is_visited_puzzle_status_b_tree(&puzzle->curr_status->tiles_pos_map,
			puzzle, &puzzle_status))
		puzzle_status = NULL;
	else
	{
		puzzle_status = save_current_puzzle_status(puzzle->curr_status);
		ft_prio_enqueue(puzzle->states_prio_queue, &puzzle_status->prio,
			(void *)puzzle_status);
		puzzle_status->is_in_queue = 1;
		store_visited_puzzle_status_b_tree(puzzle_status, puzzle->bt_root);
		(*puzzle->states_cnt)++;
	}
	return (puzzle_status);
}

static int	breadth_first_search(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	int					i;
	t_move				move;
	unsigned int		tmp_pos_status;

	is_puzzle_ready = 0;
	i = -1;
	move.to_pos = puzzle->curr_status->empty_pos;
	while (!is_puzzle_ready && ++i < move.to_pos->num_of_neighbors)
	{
		move.from_pos = move.to_pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		puzzle->curr_status->tiles_out_of_place = puzzle->size * puzzle->size;
		tmp_pos_status = puzzle->curr_status->right_pos_status;
		while (tmp_pos_status)
		{
			if (tmp_pos_status % 2)
				puzzle->curr_status->tiles_out_of_place--;
			tmp_pos_status = tmp_pos_status >> 1;
		}
		puzzle->curr_status->depth++;
		puzzle->curr_status->prio = puzzle->curr_status->tiles_out_of_place
			+ puzzle->curr_status->depth;
		add_state_to_prio_queue_1(puzzle);
		if (puzzle->curr_status->right_pos_status
			== puzzle->puzzle_ready_status)
			is_puzzle_ready = print_solution(puzzle->curr_status, puzzle);
		puzzle->curr_status->right_pos_status = puzzle_status->right_pos_status;
		puzzle->curr_status->tiles_pos_map = puzzle_status->tiles_pos_map;
		puzzle->curr_status->depth--;
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

void	alg_toop_1(t_puzzle *puzzle)
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
		puzzle->curr_status->prev_status = puzzle_status;
		is_puzzle_ready = breadth_first_search(puzzle, puzzle_status);
		print_depth_level(puzzle->curr_status->depth);
	}
	return ;
}
