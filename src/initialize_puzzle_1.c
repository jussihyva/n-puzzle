/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/08 09:42:49 by jkauppi          ###   ########.fr       */
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

static t_pos	*initialize_tile_pos(t_puzzle *puzzle, t_xy_values *xy_pos,
																t_tile *tile)
{
	t_pos		*pos;
	t_tile		**tile_array;
	int			size;

	size = puzzle->size;
	tile_array = puzzle->tile_array;
	pos = (t_pos *)ft_memalloc(sizeof(*pos));
	ft_memcpy(&pos->xy_pos, xy_pos, sizeof(pos->xy_pos));
	pos->tile = (void *)tile;
	tile->curr_pos = pos;
	pos->neighbors = (t_pos **)ft_memalloc(sizeof(*pos->neighbors)
			* MAX_NUM_OF_NEIGHBORS);
	return (pos);
}

static void	initialize_pos_table(t_puzzle *puzzle, int **tile_map)
{
	t_pos			***pos_table;
	t_xy_values		xy_pos;
	t_tile			*tile;
	int				size;
	int				tile_number;

	size = puzzle->size;
	pos_table = (t_pos ***)ft_memalloc(sizeof(*pos_table) * size);
	xy_pos.y = -1;
	while (++xy_pos.y < size)
	{
		pos_table[xy_pos.y] = (t_pos **)
			ft_memalloc(sizeof(*pos_table[xy_pos.y]) * size);
		xy_pos.x = -1;
		while (++xy_pos.x < size)
		{
			tile_number = tile_map[xy_pos.y][xy_pos.x];
			tile = puzzle->tile_array[tile_number];
			pos_table[xy_pos.y][xy_pos.x]
				= initialize_tile_pos(puzzle, &xy_pos, tile);
		}
	}
	set_tile_neighbors(pos_table, size);
	puzzle->pos_table = pos_table;
	return ;
}

static unsigned int	set_right_pos_status(t_puzzle *puzzle)
{
	unsigned int	right_pos_status;
	int				i;
	int				j;
	t_pos			*pos;

	right_pos_status = 0;
	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
		{
			pos = puzzle->pos_table[i][j];
			if (((t_tile *)pos->tile)->number == pos->order_num)
				right_pos_status |= 1 << pos->order_num;
		}
	}
	FT_LOG_DEBUG("Righ position status: %u", right_pos_status);
	return (right_pos_status);
}

t_puzzle	*initialize_puzzle(t_input *input)
{
	t_puzzle		*puzzle;
	t_xy_values		xy_pos;
	t_map			*puzzle_map;

	puzzle_map = input->puzzle_map;
	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->statistics = input->statistics;
	puzzle->size = puzzle_map->size;
	puzzle->puzzle_ready_status = (1 << (puzzle->size * puzzle->size)) - 1;
	puzzle->tile_array = initialize_tile_array(puzzle_map);
	initialize_pos_table(puzzle, puzzle_map->tile_map);
	xy_pos = puzzle->pos_table[0][0]->xy_pos;
	set_order_number(puzzle, 1, xy_pos, E_RIGHT);
	puzzle->right_pos_status = set_right_pos_status(puzzle);
	return (puzzle);
}
