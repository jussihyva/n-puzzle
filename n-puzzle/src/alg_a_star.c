/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_a_star.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:06:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/14 10:10:50 by jkauppi          ###   ########.fr       */
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
			tile_right_pos_array[pos_table[xy.y][xy.x]->order_num] = xy;
	}
	return (tile_right_pos_array);
}

static int	calculate_taxicab_distance(t_puzzle *puzzle)
{
	int				taxicab_distance;
	t_xy_values		xy;
	t_xy_values		*tile_right_pos_array;
	t_xy_values		tile_pos;
	int				tile_number;

	tile_right_pos_array = create_tile_right_pos_array(puzzle->pos_table,
			puzzle->size);
	taxicab_distance = 0;
	xy.y = -1;
	while (++xy.y < puzzle->size)
	{
		xy.x = -1;
		while (++xy.x < puzzle->size)
		{
			tile_number = (int)(puzzle->curr_status->tiles_pos_map
					>> (4 * (xy.y * puzzle->size + xy.x))) & 0xF;
			tile_pos = tile_right_pos_array[tile_number];
			taxicab_distance = ft_abs(tile_pos.y - xy.y)
				+ ft_abs(tile_pos.x - xy.x);
		}
	}
	ft_memdel((void *)tile_right_pos_array);
	return (taxicab_distance);
}

void	alg_a_star(t_puzzle *puzzle)
{
	calculate_taxicab_distance(puzzle);
	return ;
}
