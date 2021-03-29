/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 12:48:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	set_order_number(t_tile_pos ***tile_pos_table, int order_num,
	t_xy_values xy_pos, int size)
{
	tile_pos_table[xy_pos.y][xy_pos.x]->order_num = order_num;
	order_num++;
	if (xy_pos.x < size - 1 && xy_pos.y < size - 1)
	{
		if (!tile_pos_table[xy_pos.y][xy_pos.x + 1]->order_num)
		{
			xy_pos.x++;
			set_order_number(tile_pos_table, order_num, xy_pos, size);
		}
		else if (!tile_pos_table[xy_pos.y + 1][xy_pos.x]->order_num)
		{
			xy_pos.y++;
			set_order_number(tile_pos_table, order_num, xy_pos, size);
		}
		// else if (!tile_pos_table[xy_pos.y][xy_pos.x - 1]->order_num)
		// {
		// 	xy_pos.x--;
		// 	set_order_number(tile_pos_table, order_num, xy_pos, size);
		// }
		else if (!tile_pos_table[xy_pos.y - 1][xy_pos.x]->order_num)
		{
			xy_pos.y--;
			set_order_number(tile_pos_table, order_num, xy_pos, size);
		}
	}
	else if (xy_pos.y < size - 1)
	{
		if (!tile_pos_table[xy_pos.y + 1][xy_pos.x]->order_num)
		{
			xy_pos.y++;
			set_order_number(tile_pos_table, order_num, xy_pos, size);
		}
		// else if (!tile_pos_table[xy_pos.y][xy_pos.x - 1]->order_num)
		// {
		// 	xy_pos.x--;
		// 	set_order_number(tile_pos_table, order_num, xy_pos, size);
		// }
	}
	else if (xy_pos.x > 0)
	{
		if (!tile_pos_table[xy_pos.y][xy_pos.x - 1]->order_num)
		{
			xy_pos.x--;
			set_order_number(tile_pos_table, order_num, xy_pos, size);
		}
	}
	else if (xy_pos.y > 0)
	{
		if (!tile_pos_table[xy_pos.y - 1][xy_pos.x]->order_num)
		{
			xy_pos.y--;
			set_order_number(tile_pos_table, order_num, xy_pos, size);
		}
	}
	return ;
}

static void	set_order_numbers(t_tile_pos ***tile_pos_table, int size)
{
	t_tile_pos		*tile_pos;
	t_xy_values		xy_pos;
	int				order_num;

	order_num = 1;
	tile_pos = tile_pos_table[0][0];
	xy_pos = tile_pos->xy_pos;
	set_order_number(tile_pos_table, order_num, xy_pos, size);
	return ;
}

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
	set_order_numbers(tile_pos_table, size);
	return (tile_pos_table);
}

static void	print_puzzle(t_puzzle *puzzle)
{
	int		i;
	int		j;

	ft_printf(" %d\n", puzzle->size);
	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
			ft_printf(" %4d", puzzle->tile_pos_table[i][j]->order_num);
		ft_printf("\n");
	}
	return ;
}

void	dfs(t_map *puzzle_map)
{
	t_puzzle		*puzzle;

	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->size = puzzle_map->size;
	puzzle->tile_pos_table = initialize_tile_pos_table(puzzle_map->size,
			puzzle_map->tile_table);
	print_puzzle(puzzle);
	ft_memdel((void **)&puzzle);
	return ;
}
