/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/30 22:05:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static char	*get_stat_counter_string_name(t_stat_counter_name stat_counter_name)
{
	static char	**stat_counter_string_names = NULL;

	if (!stat_counter_string_names)
	{
		stat_counter_string_names
			= (char **)ft_memalloc(sizeof(*stat_counter_string_names) * 15);
		stat_counter_string_names[E_PUZZLE_INITIAL_STATE] = ft_strdup("sss");
		stat_counter_string_names[E_PUZZLE_FINAL_STATE] = ft_strdup("");
		stat_counter_string_names[E_IS_PUZZLE_SOLVABLE] = ft_strdup("RRRRRR");
		stat_counter_string_names[E_IS_PUZZLE_SOLVED] = ft_strdup("");
		stat_counter_string_names[E_EXECUTION_TIME] = ft_strdup("");
		stat_counter_string_names[E_TOTAL_CPU_USAGE_TIME] = ft_strdup("");
		stat_counter_string_names[E_SOLVING_CPU_USAGE_TIME] = ft_strdup("");
		stat_counter_string_names[E_PRINTING_CPU_USAGE_TIME] = ft_strdup("");
		stat_counter_string_names[E_TOTAL_NUM_OF_PUZZLE_STATES] = ft_strdup("");
		stat_counter_string_names[E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS]
			= ft_strdup("");
		stat_counter_string_names[E_MAX_NUM_OF_SAVED_PUZZLE_STATES]
			= ft_strdup("");
		stat_counter_string_names[E_MAX_QUEUE_LEN] = ft_strdup("");
		stat_counter_string_names[E_TOTAL_NUM_OF_ELEM_IN_QUEUE] = ft_strdup("");
		stat_counter_string_names[E_MAX_MEM_USAGE] = ft_strdup("");
		stat_counter_string_names[E_MIN_FREE_MEM] = ft_strdup("");
	}
	return (stat_counter_string_names[stat_counter_name]);
}

t_statistics	*initialize_statistics(void)
{
	t_statistics	*statistics;

	statistics = (t_statistics *)ft_memalloc(sizeof(*statistics));
	return (statistics);
}

static char	*create_format_string(void)
{
	char	*string;

	string = (char *)ft_memalloc(sizeof(*string) * 100000);
	ft_strcat(string, "project=%s,algorithm=%s,algorithm_substring=%s");
	ft_strcat(string, ",puzzle_size=%d");
	ft_strcat(string, " execution_time=%di,total_cpu_usage_time=%di");
	ft_strcat(string, ",tile_moves=%di,max_mem_usage=%di");
	ft_strcat(string, ",solution_moves=%di");
	ft_strcat(string, ",puzzle_states=%di");
	ft_strcat(string, ",state_collisions=%di");
	ft_strcat(string, " %d\n");
	return (string);
}

void	influxdb_plugin(t_log_event *event)
{
	t_statistics	*statistics;
	char			*influxdb_query_string;
	char			*format_string;

	get_stat_counter_string_name(0);
	statistics = (t_statistics *)event->additional_event_data;
	if (statistics->order == E_SEND_TO_INFLUXDB)
	{
		influxdb_query_string
			= (char *)ft_memalloc(sizeof(*influxdb_query_string) * 100000);
		format_string = create_format_string();
		ft_sprintf(influxdb_query_string, format_string,
			"n-puzzle", statistics->algorithm, statistics->algorithm_substring,
			statistics->puzzle_size,
			(int)get_execution_time(statistics), (int)statistics->cpu_usage_ms,
			statistics->tile_move_cnt, statistics->max_mem_usage,
			statistics->solution_move_cnt, statistics->puzzle_states_cnt,
			statistics->puzzle_state_collision_cnt,
			statistics->end_time);
		write_influxdb(statistics->connection, influxdb_query_string, "Hive");
		ft_strdel(&influxdb_query_string);
		ft_strdel(&format_string);
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

void	stat_update_cpu_usage(t_statistics *statistics)
{
	statistics->cpu_usage_ms = clock() / (CLOCKS_PER_SEC / 1000);
	FT_LOG_INFO("Used CPU time (ms): %ld", statistics->cpu_usage_ms);
	return ;
}
