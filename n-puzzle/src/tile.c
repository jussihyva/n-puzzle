/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/22 11:01:03 by jkauppi          ###   ########.fr       */
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

static unsigned long	set_position_match(unsigned long tiles_pos_map,
													t_pos *pos, int puzzle_size)
{
	int					tile_number;
	unsigned long		match;

	tile_number = get_tile_number(tiles_pos_map, pos, puzzle_size);
	if (tile_number == pos->right_tile_number)
		match = (unsigned int)1 << pos->right_tile_number;
	else
		match = 0;
	return (match);
}

static void	update_right_pos_status(t_puzzle *puzzle, t_pos *pos1, t_pos *pos2,
												unsigned int *right_pos_status)
{
	unsigned long	tiles_pos_map;

	tiles_pos_map = puzzle->curr_status->tiles_pos_map;
	if (*right_pos_status & (unsigned int)1 << pos1->right_tile_number)
	{
		*right_pos_status &= ~((unsigned int)1 << pos1->right_tile_number);
		*right_pos_status &= ~((unsigned int)1 << pos2->right_tile_number);
	}
	else
	{
		if (*right_pos_status & (unsigned int)1 << pos2->right_tile_number)
		{
			*right_pos_status &= ~((unsigned int)1 << pos1->right_tile_number);
			*right_pos_status &= ~((unsigned int)1 << pos2->right_tile_number);
		}
		else
		{
			*right_pos_status |= set_position_match(tiles_pos_map, pos1,
					puzzle->size);
			*right_pos_status |= set_position_match(tiles_pos_map, pos2,
					puzzle->size);
		}
	}
	FT_LOG_TRACE("Right position status: %u", *right_pos_status);
	return ;
}

void	tile_move(t_pos *from_pos, t_pos *to_pos, t_puzzle *puzzle)
{
	puzzle->curr_status->empty_pos = from_pos;
	stat_update_mem_usage(puzzle->statistics);
	update_tiles_pos_map(from_pos, to_pos, puzzle->size,
		&puzzle->curr_status->tiles_pos_map);
	update_right_pos_status(puzzle, from_pos, to_pos,
		&puzzle->curr_status->right_pos_status);
	return ;
}

int	is_puzzle_solvable(t_map *puzzle_map, t_pos ***pos_table)
{
	int				*order_num_array;
	t_xy_values		xy_pos;
	int				num_of_positions;
	int				is_solvable;
	int				order_num;
	int				i;
	int				j;
	int				num_of_inversions;
	int				current_tile_number;
	int				tile_number;
	int				add_value;
	int				add_inversion;
	int				empty_tile_row_nbr;

	num_of_positions = (puzzle_map->size * puzzle_map->size);
	is_solvable = 1;
	order_num_array = (int *)ft_memalloc(sizeof(*order_num_array)
			* num_of_positions);
	add_value = 1;
	xy_pos.y = -1;
	while (++xy_pos.y < puzzle_map->size)
	{
		xy_pos.x = -1;
		while (++xy_pos.x < puzzle_map->size)
		{
			tile_number = pos_table[xy_pos.y][xy_pos.x]->right_tile_number;
			if (!tile_number)
				add_value = 0;
			order_num = xy_pos.y * puzzle_map->size + xy_pos.x + add_value;
			order_num_array[tile_number] = order_num;
		}
	}
	num_of_inversions = 0;
	i = -1;
	while (++i < num_of_positions)
	{
		xy_pos.y = i / puzzle_map->size;
		xy_pos.x = i % puzzle_map->size;
		current_tile_number = puzzle_map->tile_map[xy_pos.y][xy_pos.x];
		if (current_tile_number)
		{
			order_num = order_num_array[current_tile_number];
			add_inversion = order_num - 1;
			j = -1;
			while (++j < i)
			{
				xy_pos.y = j / puzzle_map->size;
				xy_pos.x = j % puzzle_map->size;
				tile_number = puzzle_map->tile_map[xy_pos.y][xy_pos.x];
				if (!tile_number)
					empty_tile_row_nbr = xy_pos.y;
				else if (order_num_array[tile_number] < order_num)
					add_inversion--;
			}
			num_of_inversions += add_inversion;
		}
	}
	if (num_of_positions % 2)
	{
		if (num_of_inversions % 2)
			FT_LOG_FATAL("Puzzle is NOT solvable!");
	}
	else
	{
		if (empty_tile_row_nbr % 2)
		{
			if (!(num_of_inversions % 2))
				FT_LOG_FATAL("Puzzle is NOT solvable!");
		}
		else
		{
			if (num_of_inversions % 2)
				FT_LOG_FATAL("Puzzle is NOT solvable!");
		}
	}
	ft_memdel((void **)&order_num_array);
	if (puzzle_map->size == 4)
		FT_LOG_FATAL("4-Puzzle");
	return (is_solvable);
}
