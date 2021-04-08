/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_rand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/08 10:22:47 by jkauppi          ###   ########.fr       */
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

	pos = puzzle->tile_array[0]->curr_pos;
	while (1)
	{
		i = ft_mod_int(fast_rand(), pos->num_of_neighbors);
		next_pos = pos->neighbors[i];
		if (next_pos)
		{
			tile_move(pos, next_pos, puzzle);
			if (puzzle->right_pos_status == puzzle->puzzle_ready_status)
				break ;
			pos = next_pos;
		}
	}
	return ;
}
