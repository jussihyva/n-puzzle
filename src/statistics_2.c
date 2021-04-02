/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/02 13:24:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_statistics		*g_statistics = NULL;

void	initialize_statistics(t_statistics	**statistics)
{
	if (g_statistics)
		*statistics = g_statistics;
	else if (!*statistics)
	{
		*statistics = (t_statistics *)ft_memalloc(sizeof(**statistics));
		g_statistics = *statistics;
	}
	return ;
}

void	set_connection(t_tls_connection *connection)
{
	initialize_statistics(&g_statistics);
	g_statistics->connection = connection;
	return ;
}

void	set_puzzle_size(int puzzle_size)
{
	initialize_statistics(&g_statistics);
	g_statistics->puzzle_size = puzzle_size;
	return ;
}

void	influxdb_plugin(t_log_event *event)
{
	t_statistics	*statistics;
	char			*influxdb_query_string;

	statistics = (t_statistics *)event->additional_event_data;
	if (statistics->order == E_SEND_TO_INFLUXDB)
	{
		ft_dprintf(2, "Will be sent to influxdb: %lu (%ld)!\n",
			statistics->tile_move_cnt, get_execution_time());
		influxdb_query_string
			= (char *)ft_memalloc(sizeof(*influxdb_query_string) * 100000);
		ft_sprintf(influxdb_query_string,
			"project=%s,algorithm=%s,algorithm_substring=%s,puzzle_size=%d \
			execution_time=%di,tile_moves=%di %d\n",
			"n-puzzle", "dfs", "no_mem_rand", statistics->puzzle_size,
			(int)get_execution_time(), statistics->tile_move_cnt,
			statistics->end_time);
		ft_dprintf(2, "Execution end time: %ld\n", statistics->end_time);
		write_influxdb(statistics->connection, influxdb_query_string, "Hive");
		ft_dprintf(2, "%s\n", influxdb_query_string);
		ft_strdel(&influxdb_query_string);
	}
	return ;
}
