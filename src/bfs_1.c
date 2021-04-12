/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:19:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/12 12:34:24 by jkauppi          ###   ########.fr       */
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
									t_list **tiles_status_map_lst, int depth)
{
	int					is_puzzle_ready;
	unsigned long		tiles_status_map;
	int					i;
	t_puzzle_status		*next_status;
	t_move				move;

	is_puzzle_ready = 0;
	i = -1;
	move.to_pos = pos;
	while (!is_puzzle_ready && ++i < pos->num_of_neighbors)
	{
		move.from_pos = pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		if (puzzle->right_pos_status == puzzle->puzzle_ready_status)
			is_puzzle_ready = save_solution(puzzle, pos, pos->neighbors[i]);
		else
		{
			tiles_status_map = create_tiles_status_map(
					puzzle->curr_status->pos_table, puzzle->size);
			next_status = create_puzzle_status(puzzle->curr_status->pos_table,
					tiles_status_map, depth + 1);
			ft_memcpy(&next_status->prev_move, &move,
				sizeof(next_status->prev_move));
			next_status->prev_status = puzzle->curr_status;
			if (!is_visited_puzzle_status(tiles_status_map,
					tiles_status_map_lst, INT_MAX))
				ft_enqueue(puzzle->status_queue, &puzzle->empty_pos);
		}
		tile_move(move.to_pos, move.from_pos, puzzle);
	}
	return (is_puzzle_ready);
}

void	bfs_1(t_puzzle *puzzle)
{
	t_pos			*pos;
	int				depth;
	int				is_puzzle_ready;

	puzzle->max_depth = -1;
	depth = 0;
	is_puzzle_ready = 0;
	if (puzzle->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	ft_enqueue(puzzle->status_queue, &puzzle->empty_pos);
	while (!is_puzzle_ready && !ft_is_queue_empty(puzzle->status_queue))
	{
		pos = *(t_pos **)ft_dequeue(puzzle->status_queue);
		is_puzzle_ready = breadth_first_search(puzzle, pos,
				puzzle->tiles_status_map_lst, depth);
	}
	ft_lstdel(puzzle->tiles_status_map_lst, delete_puzzle_status);
	return ;
}
