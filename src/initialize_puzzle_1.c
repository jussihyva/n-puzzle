/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/30 08:55:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	set_tile_neighbors(t_tile_pos ***tile_pos_table, int size)
{
	t_tile_pos		*tile_pos;
	int				i;
	int				j;
	int				k;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			k = 0;
			tile_pos = tile_pos_table[i][j];
			if (i > 0)
				tile_pos->neighbors[k++] = (void *)tile_pos_table[i - 1][j];
			if (j > 0)
				tile_pos->neighbors[k++] = (void *)tile_pos_table[i][j - 1];
			if (i < size - 1)
				tile_pos->neighbors[k++] = (void *)tile_pos_table[i + 1][j];
			if (j < size - 1)
				tile_pos->neighbors[k++] = (void *)tile_pos_table[i][j + 1];
			tile_pos->num_of_neighbors = k;
		}
	}
	return ;
}

static t_tile_pos	*initialize_tile_pos(t_tile_pos ***tile_pos_table,
				int **tile_table, t_tile_pos **root_tile, t_xy_values *xy_pos)
{
	t_tile_pos		*tile_pos;

	tile_pos = (t_tile_pos *)
		ft_memalloc(sizeof(*tile_pos_table[xy_pos->y][xy_pos->x]));
	ft_memcpy(&tile_pos->xy_pos, xy_pos, sizeof(tile_pos->xy_pos));
	tile_pos->num = tile_table[xy_pos->y][xy_pos->x];
	tile_pos->neighbors = (void **)ft_memalloc(
			sizeof(*tile_pos->neighbors) * MAX_NUM_OF_NEIGHBOR);
	if (!tile_pos->num)
		*root_tile = tile_pos;
	return (tile_pos);
}

static t_tile_pos	***initialize_tile_pos_table(int size, int **tile_table,
										t_tile_pos **root_tile)
{
	t_tile_pos		***tile_pos_table;
	t_xy_values		xy_pos;

	tile_pos_table = (t_tile_pos ***)ft_memalloc(sizeof(*tile_pos_table)
			* size);
	xy_pos.y = -1;
	while (++xy_pos.y < size)
	{
		tile_pos_table[xy_pos.y] = (t_tile_pos **)
			ft_memalloc(sizeof(*tile_pos_table[xy_pos.y]) * size);
		xy_pos.x = -1;
		while (++xy_pos.x < size)
			tile_pos_table[xy_pos.y][xy_pos.x]
				= initialize_tile_pos(tile_pos_table, tile_table, root_tile,
					&xy_pos);
	}
	set_tile_neighbors(tile_pos_table, size);
	return (tile_pos_table);
}

static unsigned int	set_right_pos_status(t_puzzle *puzzle)
{
	unsigned int	right_pos_status;
	int				i;
	int				j;

	right_pos_status = 0;
	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
		{
			if (puzzle->tile_pos_table[i][j]->num
				== puzzle->tile_pos_table[i][j]->order_num)
				right_pos_status |= 1 << puzzle->tile_pos_table[i][j]->num;
		}
	}
	return (right_pos_status);
}

t_puzzle	*initialize_puzzle(t_map *puzzle_map,
												unsigned int *right_pos_status)
{
	t_puzzle		*puzzle;
	t_xy_values		xy_pos;

	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->size = puzzle_map->size;
	puzzle->tile_pos_table = initialize_tile_pos_table(puzzle_map->size,
			puzzle_map->tile_table, &puzzle->root_tile);
	xy_pos = puzzle->tile_pos_table[0][0]->xy_pos;
	set_order_number(puzzle, 1, xy_pos, E_RIGHT);
	*right_pos_status = set_right_pos_status(puzzle);
	return (puzzle);
}
