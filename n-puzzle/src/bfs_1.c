/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:19:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/28 12:27:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	save_solution(t_puzzle *puzzle, t_pos *pos1, t_pos *pos2)
{
	int		is_puzzle_ready;

	(void)puzzle;
	(void)pos1;
	(void)pos2;
	is_puzzle_ready = 1;
	return (is_puzzle_ready);
}

static int	breadth_first_search(t_puzzle *puzzle, t_pos *pos,
					t_list **puzzle_status_lst, t_puzzle_status *puzzle_status)
{
	int					is_puzzle_ready;
	int					i;
	t_puzzle_status		*next_status;
	t_move				move;
	unsigned int		saved_right_pos_status;
	unsigned long		saved_tiles_pos_map;

	add_visited_puzzle_status(puzzle_status, puzzle);
	is_puzzle_ready = 0;
	i = -1;
	move.to_pos = pos;
	while (!is_puzzle_ready && ++i < pos->num_of_neighbors)
	{
		saved_right_pos_status = puzzle->curr_status->right_pos_status;
		saved_tiles_pos_map = puzzle->curr_status->tiles_pos_map;
		move.from_pos = pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		if (puzzle->curr_status->right_pos_status
			== puzzle->puzzle_ready_status)
			is_puzzle_ready = save_solution(puzzle, pos, pos->neighbors[i]);
		else
		{
			if (!is_visited_puzzle_status(puzzle->curr_status->tiles_pos_map,
					puzzle_status_lst, INT_MAX))
			{
				next_status = create_puzzle_status(
						puzzle->curr_status->tiles_pos_map, puzzle_status,
						puzzle->curr_status->empty_pos,
						puzzle->curr_status->right_pos_status);
				ft_memcpy(&next_status->prev_move, &move,
					sizeof(next_status->prev_move));
				ft_enqueue(puzzle->status_queue, (void **)&next_status);
			}
		}
		puzzle->curr_status->right_pos_status = saved_right_pos_status;
		puzzle->curr_status->tiles_pos_map = saved_tiles_pos_map;
	}
	return (is_puzzle_ready);
}

void	bfs_1(t_puzzle *puzzle)
{
	t_pos				*pos;
	int					depth;
	int					is_puzzle_ready;
	int					printed_depth;
	t_puzzle_status		*puzzle_status;

	puzzle->max_depth = -1;
	printed_depth = -1;
	depth = 0;
	is_puzzle_ready = 0;
	if (puzzle->curr_status->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	puzzle_status = create_puzzle_status(puzzle->curr_status->tiles_pos_map,
			NULL, puzzle->curr_status->empty_pos,
			puzzle->curr_status->right_pos_status);
	ft_enqueue(puzzle->status_queue, (void **)&puzzle_status);
	while (!is_puzzle_ready && !ft_is_queue_empty(puzzle->status_queue))
	{
		puzzle_status = (t_puzzle_status *)ft_dequeue(puzzle->status_queue);
		puzzle->curr_status->right_pos_status = puzzle_status->right_pos_status;
		puzzle->curr_status->tiles_pos_map = puzzle_status->tiles_pos_map;
		puzzle->curr_status->empty_pos = puzzle_status->empty_pos;
		puzzle->curr_status->depth = puzzle_status->depth;
		pos = puzzle->curr_status->empty_pos;
		is_puzzle_ready = breadth_first_search(puzzle, pos,
				puzzle->puzzle_status_lst, puzzle_status);
		if (printed_depth < puzzle->curr_status->depth)
		{
			FT_LOG_INFO("Depth level %d done", puzzle->curr_status->depth);
			printed_depth = puzzle->curr_status->depth;
		}
	}
	return ;
}
