/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 08:00:47 by jkauppi          ###   ########.fr       */
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

void	update_right_pos_status(t_tile *tile1, t_tile *tile2,
												unsigned int *right_pos_status)
{
	if (*right_pos_status & 1 << tile1->order_num)
	{
		*right_pos_status &= ~(1 << tile1->order_num);
		*right_pos_status &= ~(1 << tile2->order_num);
	}
	else
	{
		if (*right_pos_status & 1 << tile2->order_num)
		{
			*right_pos_status &= ~(1 << tile1->order_num);
			*right_pos_status &= ~(1 << tile2->order_num);
		}
		if (tile1->num == tile1->order_num)
			*right_pos_status |= 1 << tile1->order_num;
		if (tile2->num == tile2->order_num)
			*right_pos_status |= 1 << tile2->order_num;
	}
	return ;
}
