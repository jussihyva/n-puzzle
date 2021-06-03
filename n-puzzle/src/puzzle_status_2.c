/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:12:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 17:12:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	count_num_of_bits_required(int num_of_tiles,
														unsigned long *bit_mask)
{
	int		num_of_bits;

	num_of_bits = 0;
	while (num_of_tiles)
	{
		num_of_tiles = num_of_tiles >> 1;
		num_of_bits++;
		(*bit_mask) <<= 1;
		(*bit_mask) |= 1;
	}
	return (num_of_bits);
}

static void	initialize_tiles_pos_map(int puzzle_size,
												t_tiles_pos_map *tiles_pos_map)
{
	int					num_of_tile_positions;
	int					num_of_index;

	num_of_tile_positions = puzzle_size * puzzle_size;
	tiles_pos_map->bits_for_tile_number
		= count_num_of_bits_required(num_of_tile_positions - 1,
			&tiles_pos_map->bit_mask);
	tiles_pos_map->tiles_per_map_index = sizeof(tiles_pos_map->map) * 8
		/ tiles_pos_map->bits_for_tile_number;
	num_of_index = num_of_tile_positions / tiles_pos_map->tiles_per_map_index;
	if (num_of_tile_positions % tiles_pos_map->tiles_per_map_index)
		num_of_index++;
	tiles_pos_map->map_size = sizeof(*tiles_pos_map->map) * num_of_index;
	tiles_pos_map->map = (unsigned long *)ft_memalloc(tiles_pos_map->map_size);
	return ;
}

static void	create_tiles_pos_map(int **tile_map, t_puzzle *puzzle,
							t_pos **empty_pos, t_tiles_pos_map *tiles_pos_map)
{
	t_xy_values		yx_pos;
	int				shift;
	int				pos_number;
	int				pos_map_index;

	initialize_tiles_pos_map(puzzle->size, tiles_pos_map);
	yx_pos.y = -1;
	while (++yx_pos.y < puzzle->size)
	{
		yx_pos.x = -1;
		while (++yx_pos.x < puzzle->size)
		{
			pos_number = yx_pos.y * puzzle->size + yx_pos.x;
			pos_map_index = pos_number / tiles_pos_map->tiles_per_map_index;
			shift = tiles_pos_map->bits_for_tile_number
				* (pos_number % tiles_pos_map->tiles_per_map_index);
			tiles_pos_map->map[pos_map_index]
				|= (unsigned long)tile_map[yx_pos.y][yx_pos.x] << shift;
			if (!tile_map[yx_pos.y][yx_pos.x])
				*empty_pos = puzzle->pos_table[yx_pos.y][yx_pos.x];
		}
	}
	return ;
}

static int	count_num_of_tiles_in_right_pos(t_pos ***pos_table,
		int puzzle_size, t_tiles_pos_map *tiles_pos_map)
{
	t_xy_values		yx;
	t_pos			*pos;
	int				tile_number;
	int				tiles_in_right_pos;

	tiles_in_right_pos = 0;
	yx.y = -1;
	while (++yx.y < puzzle_size)
	{
		yx.x = -1;
		while (++yx.x < puzzle_size)
		{
			pos = pos_table[yx.y][yx.x];
			pos->tile_map_index = pos->pos_index
				/ tiles_pos_map->tiles_per_map_index;
			pos->tile_pos_shift = tiles_pos_map->bits_for_tile_number
				* (pos->pos_index % tiles_pos_map->tiles_per_map_index);
			tile_number = get_tile_number(puzzle_size, &yx, tiles_pos_map);
			if (tile_number == pos->right_tile_number)
				tiles_in_right_pos++;
		}
	}
	FT_LOG_TRACE("Number of tiles in the right position: %x",
		tiles_in_right_pos);
	return (tiles_in_right_pos);
}

t_puzzle_status	*create_puzzle_status(int **tile_map, t_puzzle *puzzle)
{
	t_puzzle_status		*puzzle_status;
	t_pos				*empty_pos;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	create_tiles_pos_map(tile_map, puzzle, &empty_pos,
		&puzzle_status->tiles_pos_map);
	puzzle_status->tiles_in_right_pos
		= count_num_of_tiles_in_right_pos(puzzle->pos_table, puzzle->size,
			&puzzle_status->tiles_pos_map);
	puzzle_status->empty_pos = empty_pos;
	return (puzzle_status);
}
