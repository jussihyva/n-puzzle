/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_taxicab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 19:09:48 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/04 16:29:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

int	get_tile_number(int puzzle_size, t_xy_values *xy,
												t_tiles_pos_map *tiles_pos_map)
{
	int			tile_number;
	int			position_number;
	int			i;
	int			shift;

	position_number = xy->y * puzzle_size + xy->x;
	i = position_number / tiles_pos_map->tiles_per_map_index;
	shift = tiles_pos_map->bits_for_tile_number
		* (position_number % tiles_pos_map->tiles_per_map_index);
	tile_number = (int)((tiles_pos_map->map[i]
				>> shift)) & tiles_pos_map->bit_mask;
	return (tile_number);
}

int	calculate_taxicab_distance(t_tiles_pos_map *tiles_pos_map,
							int puzzle_size, t_xy_values *tile_right_pos_array)
{
	int				taxicab_distance;
	t_xy_values		xy;
	t_xy_values		tile_pos;
	int				tile_number;

	taxicab_distance = 0;
	xy.y = -1;
	while (++xy.y < puzzle_size)
	{
		xy.x = -1;
		while (++xy.x < puzzle_size)
		{
			tile_number = get_tile_number(puzzle_size, &xy, tiles_pos_map);
			tile_pos = tile_right_pos_array[tile_number];
			if (tile_number)
				taxicab_distance += ft_abs(tile_pos.y - xy.y)
					+ ft_abs(tile_pos.x - xy.x);
		}
	}
	return (taxicab_distance);
}

int	calculate_taxicab_based_prio(t_puzzle_status *puzzle_status,
							int puzzle_size, t_xy_values *tile_right_pos_array)
{
	int				prio;
	int				taxicab_distance;

	taxicab_distance = calculate_taxicab_distance(&puzzle_status->tiles_pos_map,
			puzzle_size, tile_right_pos_array);
	prio = taxicab_distance + puzzle_status->depth;
	return (prio);
}

void	prio_based_selection(t_puzzle_status *searched_puzzle_state,
										t_puzzle_status **selected_puzzle_state)
{
	if ((*selected_puzzle_state)->prio > searched_puzzle_state->prio)
	{
		ft_memdel((void **)selected_puzzle_state);
		*selected_puzzle_state = searched_puzzle_state;
	}
	else
		ft_memdel((void **)&searched_puzzle_state);
	return ;
}

void	taxicab_based_selection(t_puzzle *puzzle,
										t_puzzle_status *available_puzzle_state,
										t_puzzle_status **selected_puzzle_state)
{
	available_puzzle_state->prio = calculate_taxicab_based_prio(
			available_puzzle_state, puzzle->size,
			puzzle->tile_right_pos_array);
	if (*selected_puzzle_state)
		prio_based_selection(available_puzzle_state, selected_puzzle_state);
	else
		*selected_puzzle_state = available_puzzle_state;
	return ;
}
