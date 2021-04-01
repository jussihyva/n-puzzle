/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 11:23:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	initialize_statistics(t_statistics	**g_statistics)
{
	if (!*g_statistics)
		*g_statistics = (t_statistics *)ft_memalloc(sizeof(**g_statistics));
	return ;
}

void	influxdb_plugin(t_log_event *event)
{
	t_statistics	*statistics;

	statistics = (t_statistics *)event->additional_event_data;
	ft_dprintf(2, "Will be sent to influxdb: %lu!\n", statistics->tile_move_cnt);
	return ;
}
