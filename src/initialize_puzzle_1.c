/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 17:51:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	set_tile_neighbors(t_pos ***pos_table, int size)
{
	t_pos			*pos;
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
			pos = pos_table[i][j];
			if (i > 0)
				pos->neighbors[k++] = pos_table[i - 1][j];
			if (j > 0)
				pos->neighbors[k++] = pos_table[i][j - 1];
			if (i < size - 1)
				pos->neighbors[k++] = pos_table[i + 1][j];
			if (j < size - 1)
				pos->neighbors[k++] = pos_table[i][j + 1];
			pos->num_of_neighbors = k;
		}
	}
	return ;
}

static t_pos	*initialize_tile_pos(t_pos ***pos_table,
				int **tile_map, t_pos **empty_pos, t_xy_values *xy_pos)
{
	t_pos		*pos;

	pos = (t_pos *)ft_memalloc(sizeof(*pos_table[xy_pos->y][xy_pos->x]));
	ft_memcpy(&pos->xy_pos, xy_pos, sizeof(pos->xy_pos));
	pos->num = tile_map[xy_pos->y][xy_pos->x];
	pos->neighbors = (t_pos **)ft_memalloc(
			sizeof(*pos->neighbors) * MAX_NUM_OF_NEIGHBORS);
	if (!pos->num)
		*empty_pos = pos;
	return (pos);
}

static t_pos	***initialize_pos_table(int size, int **tile_map,
										t_pos **empty_pos)
{
	t_pos			***pos_table;
	t_xy_values		xy_pos;

	pos_table = (t_pos ***)ft_memalloc(sizeof(*pos_table) * size);
	xy_pos.y = -1;
	while (++xy_pos.y < size)
	{
		pos_table[xy_pos.y] = (t_pos **)
			ft_memalloc(sizeof(*pos_table[xy_pos.y]) * size);
		xy_pos.x = -1;
		while (++xy_pos.x < size)
			pos_table[xy_pos.y][xy_pos.x]
				= initialize_tile_pos(pos_table, tile_map, empty_pos, &xy_pos);
	}
	set_tile_neighbors(pos_table, size);
	return (pos_table);
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
			if (puzzle->pos_table[i][j]->num
				== puzzle->pos_table[i][j]->order_num)
				right_pos_status |= 1 << puzzle->pos_table[i][j]->num;
		}
	}
	return (right_pos_status);
}

t_puzzle	*initialize_puzzle(t_map *puzzle_map)
{
	t_puzzle		*puzzle;
	t_xy_values		xy_pos;

	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->size = puzzle_map->size;
	puzzle->pos_table = initialize_pos_table(puzzle_map->size,
			puzzle_map->tile_map, &puzzle->empty_pos);
	xy_pos = puzzle->pos_table[0][0]->xy_pos;
	set_order_number(puzzle, 1, xy_pos, E_RIGHT);
	puzzle->right_pos_status = set_right_pos_status(puzzle);
	return (puzzle);
}
