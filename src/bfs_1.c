/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:19:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/13 22:59:15 by jkauppi          ###   ########.fr       */
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
									t_list **tiles_pos_map_lst, int depth)
{
	int					is_puzzle_ready;
	int					i;
	t_puzzle_status		*next_status;
	t_move				move;

	add_visited_puzzle_status(puzzle->curr_status, tiles_pos_map_lst);
	is_puzzle_ready = 0;
	i = -1;
	move.to_pos = pos;
	while (!is_puzzle_ready && ++i < pos->num_of_neighbors)
	{
		move.from_pos = pos->neighbors[i];
		tile_move(move.from_pos, move.to_pos, puzzle);
		if (puzzle->curr_status->right_pos_status
			== puzzle->puzzle_ready_status)
			is_puzzle_ready = save_solution(puzzle, pos, pos->neighbors[i]);
		else
		{
			next_status = create_puzzle_status(puzzle->curr_status->pos_table,
					puzzle->curr_status->tiles_pos_map, depth + 1,
					puzzle->curr_status->empty_pos,
					puzzle->curr_status->right_pos_status);
			ft_memcpy(&next_status->prev_move, &move,
				sizeof(next_status->prev_move));
			next_status->prev_status = puzzle->curr_status;
			if (!is_visited_puzzle_status(next_status->tiles_pos_map,
					tiles_pos_map_lst, INT_MAX))
				ft_enqueue(puzzle->status_queue, (void **)&next_status);
		}
		tile_move(move.to_pos, move.from_pos, puzzle);
	}
	return (is_puzzle_ready);
}

void	bfs_1(t_puzzle *puzzle)
{
	t_pos				*pos;
	int					depth;
	int					is_puzzle_ready;
	int					printed_depth;

	puzzle->max_depth = -1;
	printed_depth = -1;
	depth = 0;
	is_puzzle_ready = 0;
	if (puzzle->curr_status->right_pos_status == puzzle->puzzle_ready_status)
		is_puzzle_ready = 1;
	ft_enqueue(puzzle->status_queue, (void **)&puzzle->curr_status);
	while (!is_puzzle_ready && !ft_is_queue_empty(puzzle->status_queue))
	{
		puzzle->curr_status
			= *(t_puzzle_status **)ft_dequeue(puzzle->status_queue);
		pos = puzzle->curr_status->empty_pos;
		is_puzzle_ready = breadth_first_search(puzzle, pos,
				puzzle->tiles_status_map_lst, puzzle->curr_status->depth);
		if (printed_depth < puzzle->curr_status->depth)
		{
			FT_LOG_INFO("Depth level %d done", puzzle->curr_status->depth);
			printed_depth = puzzle->curr_status->depth;
		}
	}
	ft_lstdel(puzzle->tiles_status_map_lst, delete_puzzle_status);
	return ;
}
