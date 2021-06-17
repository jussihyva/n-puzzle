/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 09:55:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	delete_puzzle_status(void *data, size_t size)
{
	t_puzzle_status		*puzzle_status;

	(void)size;
	puzzle_status = (t_puzzle_status *)data;
	ft_memdel((void **)&puzzle_status->tiles_pos_map.map);
	ft_memdel((void **)&puzzle_status);
	return ;
}

void	delete_puzzle_status_from_lst(void *data, size_t size)
{
	t_puzzle_status		*puzzle_status;

	(void)size;
	puzzle_status = *(t_puzzle_status **)data;
	ft_memdel((void **)&puzzle_status->tiles_pos_map.map);
	ft_memdel((void **)&puzzle_status);
	ft_memdel((void **)&data);
	return ;
}

void	update_current_puzzle_state(t_puzzle_status *curr_state,
												t_puzzle_status *puzzle_state)
{
	ft_memcpy(curr_state->tiles_pos_map.map, puzzle_state->tiles_pos_map.map,
		curr_state->tiles_pos_map.map_size);
	curr_state->empty_pos = puzzle_state->empty_pos;
	curr_state->depth = puzzle_state->depth;
	curr_state->prev_status = puzzle_state->prev_status;
	curr_state->tiles_in_right_pos = puzzle_state->tiles_in_right_pos;
	return ;
}

int	update_tiles_pos_map(t_pos *pos1, t_pos *pos2,
												t_tiles_pos_map *tiles_pos_map)
{
	unsigned long		tile_number[2];
	int					change_num_of_tiles_in_right_pos;

	change_num_of_tiles_in_right_pos = 0;
	tile_number[0] = (unsigned long)(tiles_pos_map->map[pos1->tile_map_index]
			>> pos1->tile_pos_shift) & tiles_pos_map->bit_mask;
	if ((int)tile_number[0] == pos1->right_tile_number)
		change_num_of_tiles_in_right_pos--;
	if ((int)tile_number[0] == pos2->right_tile_number)
		change_num_of_tiles_in_right_pos++;
	tile_number[1] = (unsigned long)(tiles_pos_map->map[pos2->tile_map_index]
			>> pos2->tile_pos_shift) & tiles_pos_map->bit_mask;
	if ((int)tile_number[1] == pos2->right_tile_number)
		change_num_of_tiles_in_right_pos--;
	if ((int)tile_number[1] == pos1->right_tile_number)
		change_num_of_tiles_in_right_pos++;
	tiles_pos_map->map[pos1->tile_map_index] &= ~(tiles_pos_map->bit_mask
			<< pos1->tile_pos_shift);
	tiles_pos_map->map[pos2->tile_map_index] &= ~(tiles_pos_map->bit_mask
			<< pos2->tile_pos_shift);
	tiles_pos_map->map[pos1->tile_map_index] |= tile_number[1]
		<< pos1->tile_pos_shift;
	tiles_pos_map->map[pos2->tile_map_index] |= tile_number[0]
		<< pos2->tile_pos_shift;
	return (change_num_of_tiles_in_right_pos);
}

t_puzzle_status	*save_current_puzzle_status(t_puzzle_status *curr_status)
{
	t_puzzle_status		*puzzle_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	ft_memcpy(puzzle_status, curr_status, sizeof(*puzzle_status));
	puzzle_status->tiles_pos_map.map
		= (unsigned long *)ft_memalloc(puzzle_status->tiles_pos_map.map_size);
	ft_memcpy(puzzle_status->tiles_pos_map.map, curr_status->tiles_pos_map.map,
		puzzle_status->tiles_pos_map.map_size);
	return (puzzle_status);
}
