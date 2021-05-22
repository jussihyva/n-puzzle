/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_taxicab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:09:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/22 10:42:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_xy_values	*create_tile_right_pos_array(t_pos ***pos_table,
																int puzzle_size)
{
	t_xy_values		xy;
	t_xy_values		*tile_right_pos_array;

	tile_right_pos_array
		= (t_xy_values *)ft_memalloc(sizeof(*tile_right_pos_array)
			* puzzle_size * puzzle_size);
	xy.y = -1;
	while (++xy.y < puzzle_size)
	{
		xy.x = -1;
		while (++xy.x < puzzle_size)
			tile_right_pos_array[pos_table[xy.y][xy.x]->right_tile_number] = xy;
	}
	return (tile_right_pos_array);
}

static int	calculate_taxicab_distance(unsigned long tiles_pos_map,
											t_pos ***pos_table, int puzzle_size)
{
	int				taxicab_distance;
	t_xy_values		xy;
	t_xy_values		*tile_right_pos_array;
	t_xy_values		tile_pos;
	int				tile_number;

	tile_right_pos_array = create_tile_right_pos_array(pos_table,
			puzzle_size);
	taxicab_distance = 0;
	xy.y = -1;
	while (++xy.y < puzzle_size)
	{
		xy.x = -1;
		while (++xy.x < puzzle_size)
		{
			tile_number = (int)(tiles_pos_map
					>> (4 * (xy.y * puzzle_size + xy.x))) & 0xF;
			tile_pos = tile_right_pos_array[tile_number];
			if (tile_number)
				taxicab_distance += ft_abs(tile_pos.y - xy.y)
					+ ft_abs(tile_pos.x - xy.x);
		}
	}
	ft_memdel((void *)&tile_right_pos_array);
	return (taxicab_distance);
}

int	calculate_taxicab_based_prio(t_puzzle_status *puzzle_status,
											t_pos ***pos_table, int puzzle_size)
{
	int				prio;
	int				taxicab_distance;

	taxicab_distance = calculate_taxicab_distance(puzzle_status->tiles_pos_map,
			pos_table, puzzle_size);
	prio = taxicab_distance + puzzle_status->depth;
	return (prio);
}
