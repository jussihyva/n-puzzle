/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_rand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/29 17:37:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	fast_rand(void)
{
	static unsigned int		seed;
	static time_t			timer;

	if (!timer)
	{
		time(&timer);
		seed = (unsigned int)timer;
	}
	seed = 214013 * seed + 2531011;
	return ((seed >> 16) & 0x7FFF);
}

void	dfs_no_mem(t_puzzle *puzzle)
{
	t_pos			*pos;
	t_pos			*next_pos;
	int				i;

	pos = puzzle->curr_status->empty_pos;
	while (1)
	{
		i = ft_mod_int(fast_rand(), pos->num_of_neighbors);
		next_pos = pos->neighbors[i];
		if (next_pos)
		{
			tile_move(pos, next_pos, puzzle);
			print_puzzle(1, &puzzle->curr_status->tiles_pos_map, puzzle->size);
			if (puzzle->curr_status->tiles_in_right_pos
				== puzzle->num_of_tile_pos)
				break ;
			pos = next_pos;
		}
	}
	*puzzle->solution_move_cnt = *puzzle->tile_move_cnt;
	return ;
}
