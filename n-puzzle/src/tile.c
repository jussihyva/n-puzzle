/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/13 11:54:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

int	get_tile_number(unsigned long tiles_pos_map, t_pos *pos, int puzzle_size)
{
	int		tile_number;

	tile_number = (tiles_pos_map >> (4 * (pos->xy_pos.y * puzzle_size
					+ pos->xy_pos.x))) & 0xF;
	return (tile_number);
}

static void	update_right_pos_status(t_puzzle *puzzle, t_pos *pos1, t_pos *pos2,
												unsigned int *right_pos_status)
{
	int				tile_number;
	unsigned long	tiles_pos_map;

	tiles_pos_map = puzzle->curr_status->tiles_pos_map;
	if (*right_pos_status & (unsigned int)1 << pos1->order_num)
	{
		*right_pos_status &= ~((unsigned int)1 << pos1->order_num);
		*right_pos_status &= ~((unsigned int)1 << pos2->order_num);
	}
	else
	{
		if (*right_pos_status & (unsigned int)1 << pos2->order_num)
		{
			*right_pos_status &= ~((unsigned int)1 << pos1->order_num);
			*right_pos_status &= ~((unsigned int)1 << pos2->order_num);
		}
		else
		{
			tile_number = get_tile_number(tiles_pos_map, pos1, puzzle->size);
			if (tile_number == pos1->order_num)
				*right_pos_status |= (unsigned int)1 << pos1->order_num;
			tile_number = get_tile_number(tiles_pos_map, pos2, puzzle->size);
			if (tile_number == pos2->order_num)
				*right_pos_status |= (unsigned int)1 << pos2->order_num;
		}
	}
	FT_LOG_DEBUG("Righ position status: %u", *right_pos_status);
	return ;
}

void	tile_move(t_pos *from_pos, t_pos *to_pos, t_puzzle *puzzle)
{
	(*puzzle->move_cnt)++;
	puzzle->curr_status->empty_pos = from_pos;
	stat_update_mem_usage(puzzle->statistics);
	update_tiles_pos_map(from_pos, to_pos, puzzle->size,
		&puzzle->curr_status->tiles_pos_map);
	update_right_pos_status(puzzle, from_pos, to_pos,
		&puzzle->curr_status->right_pos_status);
	print_puzzle(1, puzzle);
	return ;
}

t_tile	**initialize_tile_array(t_map *puzzle_map)
{
	t_tile			**tile_array;
	t_tile			*tile;
	t_xy_values		xy_pos;
	int				size;

	size = puzzle_map->size;
	tile_array = (t_tile **)ft_memalloc(sizeof(*tile_array) * size * size);
	xy_pos.y = -1;
	while (++xy_pos.y < size)
	{
		xy_pos.x = -1;
		while (++xy_pos.x < size)
		{
			tile = (t_tile *)ft_memalloc(sizeof(*tile));
			tile->number = puzzle_map->tile_map[xy_pos.y][xy_pos.x];
			tile_array[tile->number] = tile;
		}
	}
	return (tile_array);
}