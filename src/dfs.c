/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/30 14:59:49 by jkauppi          ###   ########.fr       */
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

static void	tile_num_swap(t_tile_pos *tile_pos_1, t_tile_pos *tile_pos_2)
{
	int		tmp;

	tmp = tile_pos_1->num;
	tile_pos_1->num = tile_pos_2->num;
	tile_pos_2->num = tmp;
	return ;
}

static void	update_right_pos_status(t_tile_pos *tile_pos,
												unsigned int *right_pos_status)
{
	if (*right_pos_status & 1 << tile_pos->order_num)
		*right_pos_status -= 1 << tile_pos->order_num;
	else if (tile_pos->num == tile_pos->order_num)
		*right_pos_status += 1 << tile_pos->order_num;
	return ;
}

static void	dfs_no_mem(t_puzzle *puzzle, unsigned int right_pos_status)
{
	t_tile_pos		*tile_pos;
	t_tile_pos		*next_tile_pos;
	int				i;

	FT_LOG_DEBUG("Righ position status: %u", right_pos_status);
	tile_pos = puzzle->root_tile;
	while (1)
	{
		i = ft_mod_int(fast_rand(), tile_pos->num_of_neighbors);
		next_tile_pos = tile_pos->neighbors[i];
		if (next_tile_pos)
		{
			tile_num_swap(tile_pos, next_tile_pos);
			update_right_pos_status(tile_pos, &right_pos_status);
			update_right_pos_status(next_tile_pos, &right_pos_status);
			FT_LOG_DEBUG("Righ position status: %u", right_pos_status);
			print_puzzle(1, puzzle);
			if (right_pos_status == 0x1FF)
				return ;
			tile_pos = next_tile_pos;
		}
	}
	return ;
}

void	dfs(t_map *puzzle_map)
{
	t_puzzle		*puzzle;
	unsigned int	right_pos_status;
	time_t			start_time;
	time_t			end_time;

	time(&start_time);
	puzzle = initialize_puzzle(puzzle_map, &right_pos_status);
	print_puzzle(1, puzzle);
	print_puzzle(2, puzzle);
	dfs_no_mem(puzzle, right_pos_status);
	release_puzzle(puzzle);
	time(&end_time);
	FT_LOG_INFO("Execution time : %ld", end_time - start_time);
	return ;
}
