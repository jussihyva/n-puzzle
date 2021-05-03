/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:19:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/04 00:17:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	print_solution(t_puzzle_status *puzzle_status, t_puzzle *puzzle)
{
	int		is_puzzle_ready;

	if (puzzle_status->prev_status)
		is_puzzle_ready = print_solution(puzzle_status->prev_status, puzzle);
	print_puzzle(1, puzzle_status->tiles_pos_map, puzzle->size);
	(*puzzle->solution_move_cnt)++;
	sleep(puzzle->print_delay / 10);
	is_puzzle_ready = 1;
	return (is_puzzle_ready);
}

static t_puzzle_status	*add_next_status_to_queue(t_puzzle *puzzle,
								t_move *move, t_puzzle_status *puzzle_status)
{
	t_puzzle_status		*next_status;

	next_status = NULL;
	if (!is_visited_puzzle_status(puzzle->curr_status->tiles_pos_map, puzzle))
	{
		next_status = create_puzzle_status(
				puzzle->curr_status->tiles_pos_map, puzzle_status,
				puzzle->curr_status->empty_pos,
				puzzle->curr_status->right_pos_status);
		ft_memcpy(&next_status->prev_move, &move,
			sizeof(next_status->prev_move));
		ft_enqueue(puzzle->status_queue, (void **)&next_status);
		next_status->is_in_queue = 1;
		add_visited_puzzle_status(next_status, puzzle);
	}
	return (next_status);
}

static int	breadth_first_search(t_puzzle *puzzle,
												t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	int					i;
	t_move				move;
	t_puzzle_status		*next_status;

	is_puzzle_ready = 0;
	i = -1;
	move.to_pos = puzzle->curr_status->empty_pos;
	while (!is_puzzle_ready && ++i < move.to_pos->num_of_neighbors)
	{
		move.from_pos = move.to_pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		next_status = add_next_status_to_queue(puzzle, &move, puzzle_status);
		if (next_status && puzzle->curr_status->right_pos_status
			== puzzle->puzzle_ready_status)
		{
			*puzzle->solution_move_cnt = -1;
			is_puzzle_ready = print_solution(next_status, puzzle);
		}
		puzzle->curr_status->right_pos_status = puzzle_status->right_pos_status;
		puzzle->curr_status->tiles_pos_map = puzzle_status->tiles_pos_map;
	}
	return (is_puzzle_ready);
}

void	bfs_1(t_puzzle *puzzle)
{
	int					is_puzzle_ready;
	int					printed_depth;
	t_puzzle_status		*puzzle_status;

	puzzle->max_depth = -1;
	printed_depth = -1;
	is_puzzle_ready = 0;
	if (puzzle->curr_status->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	puzzle_status = create_puzzle_status(puzzle->curr_status->tiles_pos_map,
			NULL, puzzle->curr_status->empty_pos,
			puzzle->curr_status->right_pos_status);
	ft_enqueue(puzzle->status_queue, (void **)&puzzle_status);
	puzzle_status->is_in_queue = 1;
	while (!is_puzzle_ready && !ft_is_queue_empty(puzzle->status_queue))
	{
		puzzle_status = (t_puzzle_status *)ft_dequeue(puzzle->status_queue);
		puzzle_status->is_in_queue = 0;
		ft_memcpy(puzzle->curr_status, puzzle_status,
			sizeof(*puzzle->curr_status));
		is_puzzle_ready = breadth_first_search(puzzle, puzzle_status);
		if (printed_depth < puzzle->curr_status->depth)
		{
			FT_LOG_INFO("Depth level %d done", puzzle->curr_status->depth);
			printed_depth = puzzle->curr_status->depth;
		}
	}
}
