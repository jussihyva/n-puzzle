/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_rand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 17:51:54 by jkauppi          ###   ########.fr       */
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

void	dfs_no_mem(t_puzzle *puzzle, t_statistics *statistics)
{
	t_pos			*pos;
	t_pos			*next_pos;
	int				i;
	unsigned int	puzzle_ready;

	puzzle_ready = (1 << (puzzle->size * puzzle->size)) - 1;
	FT_LOG_DEBUG("Righ position status: %u", puzzle->right_pos_status);
	pos = puzzle->empty_pos;
	while (1)
	{
		i = ft_mod_int(fast_rand(), pos->num_of_neighbors);
		next_pos = pos->neighbors[i];
		if (next_pos)
		{
			tile_num_swap(pos, next_pos, puzzle->move_cnt);
			update_right_pos_status(pos, next_pos, &puzzle->right_pos_status);
			FT_LOG_DEBUG("Righ position status: %u", puzzle->right_pos_status);
			print_puzzle(1, puzzle);
			if (puzzle->right_pos_status == puzzle_ready)
				break ;
			pos = next_pos;
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
