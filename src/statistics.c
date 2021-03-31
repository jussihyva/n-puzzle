/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 23:44:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/31 11:23:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static unsigned long	*g_tile_move_cnt = NULL;
static time_t			g_start_time;
static time_t			g_end_time;

unsigned long	*get_move_cnt(void)
{
	if (!g_tile_move_cnt)
		g_tile_move_cnt
			= (unsigned long *)ft_memalloc(sizeof(*g_tile_move_cnt));
	return (g_tile_move_cnt);
}

void	set_start_time(void)
{
	g_start_time = time(NULL);
	return ;
}

void	set_end_time(void)
{
	g_end_time = time(NULL);
	return ;
}

time_t	get_execution_time(void)
{
	time_t	execution_time;

	execution_time = g_end_time - g_start_time;
	return (execution_time);
}
