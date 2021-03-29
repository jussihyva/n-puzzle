/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 14:28:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_tile_pos	***initialize_tile_pos_table(int size, int **tile_table)
{
	t_tile_pos	***tile_pos_table;
	t_tile_pos	*tile_pos;
	int			i;
	int			j;

	tile_pos_table = (t_tile_pos ***)ft_memalloc(sizeof(*tile_pos_table)
			* size);
	i = -1;
	while (++i < size)
	{
		tile_pos_table[i]
			= (t_tile_pos **)ft_memalloc(sizeof(*tile_pos_table[i]) * size);
		j = -1;
		while (++j < size)
		{
			tile_pos
				= (t_tile_pos *)ft_memalloc(sizeof(*tile_pos_table[i][j]));
			tile_pos->xy_pos.x = j;
			tile_pos->xy_pos.y = i;
			tile_pos->num = tile_table[i][j];
			tile_pos_table[i][j] = tile_pos;
		}
	}
	return (tile_pos_table);
}

t_puzzle	*initialize_puzzle(t_map *puzzle_map)
{
	t_puzzle		*puzzle;
	t_xy_values		xy_pos;

	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->size = puzzle_map->size;
	puzzle->tile_pos_table = initialize_tile_pos_table(puzzle_map->size,
			puzzle_map->tile_table);
	xy_pos = puzzle->tile_pos_table[0][0]->xy_pos;
	set_order_number(puzzle, 1, xy_pos, E_RIGHT);
	return (puzzle);
}
