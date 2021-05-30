/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/30 12:57:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	tile_move(t_pos *from_pos, t_pos *to_pos, t_puzzle *puzzle)
{
	puzzle->curr_status->empty_pos = from_pos;
	stat_update_mem_usage(puzzle->statistics);
	puzzle->curr_status->tiles_in_right_pos
		+= update_tiles_pos_map(from_pos, to_pos, puzzle->size,
		&puzzle->curr_status->tiles_pos_map);
	return ;
}

static int	calculate_num_of_inversions(t_xy_values start_pos,
						t_map *puzzle_map, t_xy_values *tile_right_pos_array,
						int *empty_tile_row_nbr)
{
	int				num_of_inversions;
	int				current_tile_number;
	int				tile_number;
	t_xy_values		tile_right_position;

	current_tile_number = puzzle_map->tile_map[start_pos.y][start_pos.x];
	tile_right_position = tile_right_pos_array[current_tile_number];
	num_of_inversions = 0;
	start_pos.y--;
	start_pos.x--;
	while (++start_pos.y < puzzle_map->size)
	{
		while (++start_pos.x < puzzle_map->size)
		{
			tile_number = puzzle_map->tile_map[start_pos.y][start_pos.x];
			if (!tile_number)
				*empty_tile_row_nbr = start_pos.y;
			else if (ft_memcmp(&tile_right_pos_array[tile_number],
					&tile_right_position, sizeof(tile_right_position)) < 0)
				num_of_inversions++;
		}
		start_pos.x = -1;
	}
	return (num_of_inversions);
}

static int	decide_is_puzzle_solvable(int puzzle_size, int num_of_inversions,
														int empty_tile_row_nbr)
{
	int				is_solvable;

	is_solvable = 1;
	if ((puzzle_size * puzzle_size) % 2)
	{
		if (num_of_inversions % 2)
			is_solvable = 0;
	}
	else
	{
		if (empty_tile_row_nbr % 2)
		{
			if (!(num_of_inversions % 2))
				is_solvable = 0;
		}
		else
		{
			if (num_of_inversions % 2)
				is_solvable = 0;
		}
		if (!((puzzle_size - 2) % 4))
			is_solvable = ~is_solvable & 1;
	}
	if (!is_solvable)
		FT_LOG_FATAL("Puzzle is NOT solvable!");
	return (is_solvable);
}

int	is_puzzle_solvable(t_map *puzzle_map, t_xy_values *tile_right_pos_array)
{
	t_xy_values		xy_pos;
	int				is_solvable;
	int				num_of_inversions;
	int				current_tile_number;
	int				empty_tile_row_nbr;

	is_solvable = 1;
	xy_pos.y = -1;
	num_of_inversions = 0;
	xy_pos.y = -1;
	while (++xy_pos.y < puzzle_map->size)
	{
		xy_pos.x = -1;
		while (++xy_pos.x < puzzle_map->size)
		{
			current_tile_number = puzzle_map->tile_map[xy_pos.y][xy_pos.x];
			if (current_tile_number)
				num_of_inversions += calculate_num_of_inversions(xy_pos,
						puzzle_map, tile_right_pos_array, &empty_tile_row_nbr);
		}
	}
	is_solvable = decide_is_puzzle_solvable(puzzle_map->size, num_of_inversions,
			empty_tile_row_nbr);
	return (is_solvable);
}
