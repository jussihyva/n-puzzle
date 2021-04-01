/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 13:00:29 by jkauppi          ###   ########.fr       */
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
	if (statistics->order == E_SEND_TO_INFLUXDB)
	{
		ft_dprintf(2, "Will be sent to influxdb: %lu (%ld)!\n",
			statistics->tile_move_cnt, get_execution_time());
	}
	return ;
}
