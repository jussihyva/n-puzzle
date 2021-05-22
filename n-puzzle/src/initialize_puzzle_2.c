/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:26:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/22 10:47:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	go_right(t_pos ***pos_table, t_xy_values *xy_pos, int size,
																	t_dir *dir)
{
	if ((xy_pos->x < size - 1)
		&& (!pos_table[xy_pos->y][xy_pos->x + 1]->right_tile_number))
		xy_pos->x++;
	else if ((xy_pos->y < size - 1)
		&& (!pos_table[xy_pos->y + 1][xy_pos->x]->right_tile_number))
	{
		xy_pos->y++;
		*dir = E_DOWN;
	}
	return ;
}

static void	go_down(t_pos ***pos_table, t_xy_values *xy_pos, int size,
																	t_dir *dir)
{
	if ((xy_pos->y < size - 1)
		&& (!pos_table[xy_pos->y + 1][xy_pos->x]->right_tile_number))
		xy_pos->y++;
	else if ((xy_pos->x > 0)
		&& (!pos_table[xy_pos->y][xy_pos->x - 1]->right_tile_number))
	{
		xy_pos->x--;
		*dir = E_LEFT;
	}
	return ;
}

static void	go_left(t_pos ***pos_table, t_xy_values *xy_pos, t_dir *dir)
{
	if ((xy_pos->x > 0)
		&& (!pos_table[xy_pos->y][xy_pos->x - 1]->right_tile_number))
		xy_pos->x--;
	else if ((xy_pos->y > 0)
		&& (!pos_table[xy_pos->y - 1][xy_pos->x]->right_tile_number))
	{
		xy_pos->y--;
		*dir = E_UP;
	}
	return ;
}

static void	go_up(t_pos ***pos_table, t_xy_values *xy_pos, int size, t_dir *dir)
{
	if ((xy_pos->y > 0)
		&& (!pos_table[xy_pos->y - 1][xy_pos->x]->right_tile_number))
	{
		xy_pos->y--;
	}
	else if ((xy_pos->x < size - 1)
		&& (!pos_table[xy_pos->y][xy_pos->x + 1]->right_tile_number))
	{
		xy_pos->x++;
		*dir = E_RIGHT;
	}
	return ;
}

void	set_tile_numbers_target_positions(t_pos ***pos_table, int size)
{
	int				num_of_tiles;
	t_xy_values		xy_pos;
	int				tile_number;
	t_dir			dir;

	xy_pos.x = 0;
	xy_pos.y = 0;
	dir = E_RIGHT;
	num_of_tiles = size * size;
	tile_number = 0;
	while (++tile_number < num_of_tiles)
	{
		pos_table[xy_pos.y][xy_pos.x]->right_tile_number = tile_number;
		if (dir == E_RIGHT)
			go_right(pos_table, &xy_pos, size, &dir);
		else if (dir == E_DOWN)
			go_down(pos_table, &xy_pos, size, &dir);
		else if (dir == E_LEFT)
			go_left(pos_table, &xy_pos, &dir);
		else if (dir == E_UP)
			go_up(pos_table, &xy_pos, size, &dir);
	}
	pos_table[xy_pos.y][xy_pos.x]->right_tile_number = 0;
	return ;
}
