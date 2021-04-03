/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_rand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/03 18:08:32 by jkauppi          ###   ########.fr       */
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

void	dfs_no_mem(t_puzzle *puzzle, unsigned int right_pos_status,
													t_statistics *statistics)
{
	t_tile			*tile;
	t_tile			*next_tile;
	int				i;
	unsigned int	puzzle_ready;

	puzzle_ready = (1 << (puzzle->size * puzzle->size)) - 1;
	FT_LOG_DEBUG("Righ position status: %u", right_pos_status);
	tile = puzzle->root_tile;
	while (1)
	{
		i = ft_mod_int(fast_rand(), tile->num_of_neighbors);
		next_tile = tile->neighbors[i];
		if (next_tile)
		{
			tile_num_swap(tile, next_tile, puzzle->move_cnt);
			update_right_pos_status(tile, &right_pos_status);
			update_right_pos_status(next_tile, &right_pos_status);
			FT_LOG_DEBUG("Righ position status: %u", right_pos_status);
			print_puzzle(1, puzzle);
			if (right_pos_status == puzzle_ready)
				break ;
			tile = next_tile;
		}
	}
	set_end_time();
	statistics->order = E_SEND_TO_INFLUXDB;
	statistics->algorithm_substring = ft_strdup("no_mem_rand");
	FT_LOG_INFO("Execution time : %ld", get_execution_time());
	statistics->order = E_NONE;
	FT_LOG_INFO("Total num of moves: %lu", *puzzle->move_cnt);
	return ;
}
