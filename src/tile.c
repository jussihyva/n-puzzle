/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/03 18:32:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	tile_num_swap(t_tile *tile_1, t_tile *tile_2, unsigned long *move_cnt)
{
	int		tmp;

	tmp = tile_1->num;
	tile_1->num = tile_2->num;
	tile_2->num = tmp;
	(*move_cnt)++;
	return ;
}

void	update_right_pos_status(t_tile *tile, unsigned int *right_pos_status)
{
	if (*right_pos_status & 1 << tile->order_num)
		*right_pos_status -= 1 << tile->order_num;
	else if (tile->num == tile->order_num)
		*right_pos_status += 1 << tile->order_num;
	return ;
}
