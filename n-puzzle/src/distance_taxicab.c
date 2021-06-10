/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_taxicab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:09:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/10 18:10:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

int	get_tile_number(int puzzle_size, t_xy_values *xy,
												t_tiles_pos_map *tiles_pos_map)
{
	int			position_number;
	int			i;
	int			shift;
	int			tile_number;

	position_number = xy->y * puzzle_size + xy->x;
	i = position_number / tiles_pos_map->tiles_per_map_index;
	shift = tiles_pos_map->bits_for_tile_number
		* (position_number % tiles_pos_map->tiles_per_map_index);
	tile_number = (int)((tiles_pos_map->map[i]
				>> shift)) & tiles_pos_map->bit_mask;
	return (tile_number);
}

static int	increase_taxicab_distance(int tile_number, t_xy_values *yx,
											t_xy_values *tile_pos)
{
	int				distance;

	distance = 0;
	if (tile_number)
		distance = ft_abs(tile_pos->y - yx->y) + ft_abs(tile_pos->x - yx->x);
	return (distance);
}

static int	increase_taxicab_distance_conflicts(int tile_number,
										t_xy_values *yx, t_xy_values *tile_pos,
											t_linear_conflict *linear_conflict)
{
	int				distance;

	distance = 0;
	if (tile_number)
		distance = ft_abs(tile_pos->y - yx->y) + ft_abs(tile_pos->x - yx->x);
	if (tile_pos->y == yx->y)
	{
		if (linear_conflict->raw > tile_pos->x)
			distance += 2;
		linear_conflict->raw = ft_max_int(linear_conflict->raw,
				tile_pos->x);
	}
	if (tile_pos->x == yx->x)
	{
		if (linear_conflict->column[yx->x] > tile_pos->y)
			distance += 2;
		linear_conflict->column[yx->x]
			= ft_max_int(linear_conflict->column[yx->x], tile_pos->y);
	}
	return (distance);
}

int	calculate_taxicab_distance(t_tiles_pos_map *tiles_pos_map,
							int puzzle_size, t_xy_values *tile_right_pos_array)
{
	int				taxicab_distance;
	t_xy_values		yx;
	int				tile_number;
	t_xy_values		tile_pos;

	taxicab_distance = 0;
	yx.y = -1;
	while (++yx.y < puzzle_size)
	{
		yx.x = -1;
		while (++yx.x < puzzle_size)
		{
			tile_number = get_tile_number(puzzle_size, &yx, tiles_pos_map);
			tile_pos = tile_right_pos_array[tile_number];
			taxicab_distance += increase_taxicab_distance(tile_number, &yx,
					&tile_pos);
		}
	}
	return (taxicab_distance);
}

int	linear_conflict_taxicab_distance(t_tiles_pos_map *tiles_pos_map,
							int puzzle_size, t_xy_values *tile_right_pos_array)
{
	int					taxicab_distance;
	t_xy_values			yx;
	t_xy_values			tile_pos;
	int					tile_number;
	t_linear_conflict	linear_conflict;

	linear_conflict.column = (int *)ft_memalloc(sizeof(*linear_conflict.column)
			* puzzle_size);
	taxicab_distance = 0;
	yx.y = -1;
	while (++yx.y < puzzle_size)
	{
		linear_conflict.raw = 0;
		yx.x = -1;
		while (++yx.x < puzzle_size)
		{
			tile_number = get_tile_number(puzzle_size, &yx, tiles_pos_map);
			tile_pos = tile_right_pos_array[tile_number];
			taxicab_distance += increase_taxicab_distance_conflicts(tile_number,
					&yx, &tile_pos, &linear_conflict);
		}
	}
	ft_memdel((void **)&linear_conflict.column);
	return (taxicab_distance);
}
