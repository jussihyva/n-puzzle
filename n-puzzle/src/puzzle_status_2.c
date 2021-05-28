/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:12:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/28 17:25:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	delete_puzzle_status(void *content, size_t size)
{
	t_puzzle_status		*puzzle_status;

	(void)size;
	puzzle_status = *(t_puzzle_status **)content;
	ft_memdel((void **)&puzzle_status);
	ft_memdel((void **)&content);
	return ;
}

void	update_current_puzzle_state(t_puzzle_status *curr_state, t_puzzle_status *puzzle_state)
{
	ft_memcpy(curr_state->tiles_pos_map.map, puzzle_state->tiles_pos_map.map, curr_state->tiles_pos_map.map_size);
	ft_memcpy(&curr_state->right_pos_status, &puzzle_state->right_pos_status, sizeof(curr_state->right_pos_status));
	curr_state->empty_pos = puzzle_state->empty_pos;
	curr_state->depth = puzzle_state->depth;
	curr_state->prev_status = puzzle_state->prev_status;
	return ;
}
