/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/08 10:08:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

t_statistics	*initialize_statistics(void)
{
	t_statistics	*statistics;

	statistics = (t_statistics *)ft_memalloc(sizeof(*statistics));
	return (statistics);
}

void	influxdb_plugin(t_log_event *event)
{
	t_statistics	*statistics;
	char			*influxdb_query_string;

	statistics = (t_statistics *)event->additional_event_data;
	if (statistics->order == E_SEND_TO_INFLUXDB)
	{
		influxdb_query_string
			= (char *)ft_memalloc(sizeof(*influxdb_query_string) * 100000);
		ft_sprintf(influxdb_query_string,
			"project=%s,algorithm=%s,algorithm_substring=%s,puzzle_size=%d \
			execution_time=%di,tile_moves=%di,max_mem_usage=%di %d\n",
			"n-puzzle", "dfs", statistics->algorithm_substring,
			statistics->puzzle_size,
			(int)get_execution_time(statistics), statistics->tile_move_cnt,
			statistics->max_mem_usage, statistics->end_time);
		ft_dprintf(2, "Execution end time: %ld\n", statistics->end_time);
		write_influxdb(statistics->connection, influxdb_query_string, "Hive");
		ft_dprintf(2, "%s\n", influxdb_query_string);
		ft_strdel(&influxdb_query_string);
	}
	return ;
}

void	stat_update_mem_usage(t_statistics *statistics)
{
	static long		usage_prev;
	struct rusage	rusage;

	usage_prev = 0;
	getrusage(RUSAGE_SELF, &rusage);
	FT_LOG_TRACE("Mem usage: %ld (+%5ld)", rusage.ru_maxrss, rusage.ru_maxrss
		- usage_prev);
	statistics->max_mem_usage = ft_max_int(statistics->max_mem_usage,
			(int)rusage.ru_maxrss);
	usage_prev = rusage.ru_maxrss;
	return ;
}
