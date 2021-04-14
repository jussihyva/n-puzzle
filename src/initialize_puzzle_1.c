/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/14 09:03:13 by jkauppi          ###   ########.fr       */
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

static t_pos	*initialize_tile_pos(t_xy_values *xy_pos)
{
	t_pos		*pos;

	pos = (t_pos *)ft_memalloc(sizeof(*pos));
	ft_memcpy(&pos->xy_pos, xy_pos, sizeof(pos->xy_pos));
	pos->neighbors = (t_pos **)ft_memalloc(sizeof(*pos->neighbors)
			* MAX_NUM_OF_NEIGHBORS);
	return (pos);
}

static t_pos	***initialize_pos_table(int puzzle_size)
{
	t_pos			***pos_table;
	t_xy_values		xy_pos;

	pos_table = (t_pos ***)ft_memalloc(sizeof(*pos_table) * puzzle_size);
	xy_pos.y = -1;
	while (++xy_pos.y < puzzle_size)
	{
		pos_table[xy_pos.y] = (t_pos **)
			ft_memalloc(sizeof(*pos_table[xy_pos.y]) * puzzle_size);
		xy_pos.x = -1;
		while (++xy_pos.x < puzzle_size)
			pos_table[xy_pos.y][xy_pos.x] = initialize_tile_pos(&xy_pos);
	}
	set_tile_neighbors(pos_table, puzzle_size);
	return (pos_table);
}

static unsigned int	set_right_pos_status(t_pos ***pos_table, int puzzle_size,
													unsigned long tiles_pos_map)
{
	unsigned int	right_pos_status;
	int				i;
	int				j;
	t_pos			*pos;
	int				tile_number;

	right_pos_status = 0;
	i = -1;
	while (++i < puzzle_size)
	{
		j = -1;
		while (++j < puzzle_size)
		{
			pos = pos_table[i][j];
			tile_number = (tiles_pos_map >> (4 * (i * puzzle_size + j))) & 0xF;
			if (tile_number == pos->order_num)
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
	unsigned long	tiles_pos_map;
	t_pos			*empty_pos;
	unsigned int	right_pos_status;

	puzzle_map = input->puzzle_map;
	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->statistics = input->statistics;
	puzzle->algorithm = input->algorithm;
	puzzle->size = puzzle_map->size;
	puzzle->puzzle_ready_status = (1 << (puzzle->size * puzzle->size)) - 1;
	puzzle->tiles_status_map_lst
		= (t_list **)ft_memalloc(sizeof(*puzzle->tiles_status_map_lst));
	puzzle->tile_array = initialize_tile_array(puzzle_map);
	puzzle->status_queue
		= (t_queue *)ft_memalloc(sizeof(*puzzle->status_queue));
	puzzle->status_queue->in_stack
		= (t_list **)ft_memalloc(sizeof(*puzzle->status_queue->in_stack));
	puzzle->status_queue->out_stack
		= (t_list **)ft_memalloc(sizeof(*puzzle->status_queue->out_stack));
	puzzle->pos_table = initialize_pos_table(puzzle->size);
	xy_pos = puzzle->pos_table[0][0]->xy_pos;
	set_order_number(puzzle, puzzle->pos_table, 1, xy_pos, E_RIGHT);
	tiles_pos_map = create_tiles_pos_map(puzzle_map->tile_map,
			puzzle->pos_table, puzzle->size, &empty_pos);
	right_pos_status = set_right_pos_status(puzzle->pos_table,
			puzzle->size, tiles_pos_map);
	puzzle->curr_status = create_puzzle_status(tiles_pos_map, 0, empty_pos,
			right_pos_status);
	return (puzzle);
}
