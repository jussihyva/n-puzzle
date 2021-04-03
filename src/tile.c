/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:04:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/02 21:09:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	tile_num_swap(t_tile_pos *tile_pos_1, t_tile_pos *tile_pos_2,
														unsigned long *move_cnt)
{
	int		tmp;

	tmp = tile_pos_1->num;
	tile_pos_1->num = tile_pos_2->num;
	tile_pos_2->num = tmp;
	(*move_cnt)++;
	return ;
}

void	update_right_pos_status(t_tile_pos *tile_pos,
												unsigned int *right_pos_status)
{
	if (*right_pos_status & 1 << tile_pos->order_num)
		*right_pos_status -= 1 << tile_pos->order_num;
	else if (tile_pos->num == tile_pos->order_num)
		*right_pos_status += 1 << tile_pos->order_num;
	return ;
}
