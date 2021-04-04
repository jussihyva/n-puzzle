/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 20:25:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	tile_num_swap(t_pos *pos1, t_pos *pos2, unsigned long *move_cnt)
{
	int		tmp;

	tmp = pos1->num;
	pos1->num = pos2->num;
	pos2->num = tmp;
	(*move_cnt)++;
	return ;
}

void	update_right_pos_status(t_pos *pos1, t_pos *pos2,
												unsigned int *right_pos_status)
{
	if (*right_pos_status & 1 << pos1->order_num)
	{
		*right_pos_status &= ~(1 << pos1->order_num);
		*right_pos_status &= ~(1 << pos2->order_num);
	}
	else
	{
		if (*right_pos_status & 1 << pos2->order_num)
		{
			*right_pos_status &= ~(1 << pos1->order_num);
			*right_pos_status &= ~(1 << pos2->order_num);
		}
		if (pos1->num == pos1->order_num)
			*right_pos_status |= 1 << pos1->order_num;
		if (pos2->num == pos2->order_num)
			*right_pos_status |= 1 << pos2->order_num;
	}
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
