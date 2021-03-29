/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:26:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 14:50:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	go_right(t_tile_pos ***tile_pos_table, t_xy_values *xy_pos,
														int size, t_dir *dir)
{
	if ((xy_pos->x < size - 1)
		&& (!tile_pos_table[xy_pos->y][xy_pos->x + 1]->order_num))
		xy_pos->x++;
	else if ((xy_pos->y < size - 1)
		&& (!tile_pos_table[xy_pos->y + 1][xy_pos->x]->order_num))
	{
		xy_pos->y++;
		*dir = E_DOWN;
	}
	return ;
}

static void	go_down(t_tile_pos ***tile_pos_table, t_xy_values *xy_pos,
														int size, t_dir *dir)
{
	if ((xy_pos->y < size - 1)
		&& (!tile_pos_table[xy_pos->y + 1][xy_pos->x]->order_num))
		xy_pos->y++;
	else if ((xy_pos->x > 0)
		&& (!tile_pos_table[xy_pos->y][xy_pos->x - 1]->order_num))
	{
		xy_pos->x--;
		*dir = E_LEFT;
	}
	return ;
}

static void	go_left(t_tile_pos ***tile_pos_table, t_xy_values *xy_pos,
														t_dir *dir)
{
	if ((xy_pos->x > 0)
		&& (!tile_pos_table[xy_pos->y][xy_pos->x - 1]->order_num))
		xy_pos->x--;
	else if ((xy_pos->y > 0)
		&& (!tile_pos_table[xy_pos->y - 1][xy_pos->x]->order_num))
	{
		xy_pos->y--;
		*dir = E_UP;
	}
	return ;
}

static void	go_up(t_tile_pos ***tile_pos_table, t_xy_values *xy_pos,
														int size, t_dir *dir)
{
	if ((xy_pos->y > 0)
		&& (!tile_pos_table[xy_pos->y - 1][xy_pos->x]->order_num))
	{
		xy_pos->y--;
	}
	else if ((xy_pos->x < size - 1)
		&& (!tile_pos_table[xy_pos->y][xy_pos->x + 1]->order_num))
	{
		xy_pos->x++;
		*dir = E_RIGHT;
	}
	return ;
}

void	set_order_number(t_puzzle *puzzle, int order_num,
	t_xy_values xy_pos, t_dir dir)
{
	t_tile_pos		***tile_pos_table;
	int				size;

	tile_pos_table = puzzle->tile_pos_table;
	size = puzzle->size;
	if (size * size == order_num)
	{
		tile_pos_table[xy_pos.y][xy_pos.x]->order_num = 0;
		return ;
	}
	tile_pos_table[xy_pos.y][xy_pos.x]->order_num = order_num;
	order_num++;
	if (dir == E_RIGHT)
		go_right(tile_pos_table, &xy_pos, size, &dir);
	else if (dir == E_DOWN)
		go_down(tile_pos_table, &xy_pos, size, &dir);
	else if (dir == E_LEFT)
		go_left(tile_pos_table, &xy_pos, &dir);
	else if (dir == E_UP)
		go_up(tile_pos_table, &xy_pos, size, &dir);
	else
		return ;
	set_order_number(puzzle, order_num, xy_pos, dir);
	return ;
}
