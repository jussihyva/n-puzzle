/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:19:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/11 03:02:05 by jkauppi          ###   ########.fr       */
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
											t_list **visited_puzzle_statuses)
{
	int					is_puzzle_ready;
	// unsigned long		tiles_status_map;
	int					i;

	(void)visited_puzzle_statuses;
	is_puzzle_ready = 0;
	i = -1;
	while (!is_puzzle_ready && ++i < pos->num_of_neighbors)
	{
		tile_move(pos, pos->neighbors[i], puzzle);
		if (puzzle->right_pos_status == puzzle->puzzle_ready_status)
			is_puzzle_ready = save_solution(puzzle, pos, pos->neighbors[i]);
		// else
		// {
		// 	tiles_status_map = create_tiles_status_map(puzzle);
		// 	if (!is_visited_puzzle_status(tiles_status_map, visited_puzzle_statuses,
		// 			INT_MAX))
		// 	{
		// 		put_puzzle_status_to_queue();
		// 	}
		// }
	}
	return (is_puzzle_ready);
}

void	bfs_1(t_puzzle *puzzle)
{
	t_pos			*pos;
	int				depth;
	int				is_puzzle_ready;
	t_list			**visited_puzzle_statuses;

	visited_puzzle_statuses
		= (t_list **)ft_memalloc(sizeof(*visited_puzzle_statuses));
	pos = puzzle->tile_array[0]->curr_pos;
	is_puzzle_ready = 0;
	puzzle->max_depth = -1;
	depth = 0;
	while (!is_puzzle_ready && ++puzzle->max_depth < INT_MAX)
	{
		is_puzzle_ready = breadth_first_search(puzzle, pos,
				visited_puzzle_statuses);
	}
	ft_lstdel(visited_puzzle_statuses, delete_puzzle_status);
	return ;
}
