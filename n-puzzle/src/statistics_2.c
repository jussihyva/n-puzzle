/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/01 08:20:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static char	**create_stat_counter_string_names(void)
{
	char	**stat_counter_string_names;

	stat_counter_string_names = (char **)ft_memalloc(
			sizeof(*stat_counter_string_names) * NUM_OF_STAT_COUNTERS);
	stat_counter_string_names[E_PUZZLE_INITIAL_STATE] = ft_strdup("");
	stat_counter_string_names[E_PUZZLE_FINAL_STATE] = ft_strdup("");
	stat_counter_string_names[E_IS_PUZZLE_SOLVABLE] = ft_strdup("RRRRRR");
	stat_counter_string_names[E_IS_PUZZLE_SOLVED] = ft_strdup("");
	stat_counter_string_names[E_NUM_OF_SOLUTION_MOVES]
		= ft_strdup("solution_moves=%di");
	stat_counter_string_names[E_EXECUTION_TIME]
		= ft_strdup("execution_time=%di");
	stat_counter_string_names[E_TOTAL_CPU_USAGE_TIME]
		= ft_strdup("total_cpu_usage_time=%di");
	stat_counter_string_names[E_SOLVER_CPU_USAGE_TIME]
		= ft_strdup("solver_cpu_usage_time=%di");
	stat_counter_string_names[E_PRINTING_CPU_USAGE_TIME] = ft_strdup("");
	stat_counter_string_names[E_TOTAL_NUM_OF_PUZZLE_STATES]
		= ft_strdup("puzzle_states=%di");
	stat_counter_string_names[E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS]
		= ft_strdup("state_collisions=%di");
	stat_counter_string_names[E_MAX_NUM_OF_SAVED_PUZZLE_STATES] = ft_strdup("");
	stat_counter_string_names[E_MAX_QUEUE_LEN] = ft_strdup("");
	stat_counter_string_names[E_TOTAL_NUM_OF_ELEM_IN_QUEUE] = ft_strdup("");
	stat_counter_string_names[E_MAX_MEM_USAGE] = ft_strdup("max_mem_usage=%di");
	stat_counter_string_names[E_MIN_FREE_MEM] = ft_strdup("");
	return (stat_counter_string_names);
}

t_statistics	*initialize_statistics(void)
{
	t_statistics	*statistics;

	statistics = (t_statistics *)ft_memalloc(sizeof(*statistics));
	statistics->stat_counters.string_names = create_stat_counter_string_names();
	return (statistics);
}

static char	*add_counters_to_string(char *format_string_ptr,
				t_stat_counters *stat_counters, char *influxdb_query_string)
{
	int		i;
	char	*ptr;
	char	counter_string[100000];
	char	format_string[100000];
	int		is_first_counter_added;

	is_first_counter_added = 0;
	i = -1;
	ptr = influxdb_query_string;
	ft_strcat(ptr, format_string_ptr);
	ptr += ft_strlen(format_string_ptr);
	while (++i < NUM_OF_STAT_COUNTERS)
	{
		if (stat_counters->active_counters[i])
		{
			*format_string = '\0';
			if (is_first_counter_added)
				ft_strcat(format_string, ",");
			else
				ft_strcat(format_string, " ");
			ft_strcat(format_string, stat_counters->string_names[i]);
			ft_sprintf(counter_string, format_string,
				stat_counters->counter_values[i]);
			ft_strcat(ptr, counter_string);
			ptr += ft_strlen(counter_string);
			is_first_counter_added = 1;
		}
	}
	return (ptr);
}

static char	*create_format_string(t_statistics *statistics,
												char *new_influxdb_query_string)
{
	char	*string;
	char	*tag_format_string;
	char	*tag_string;
	char	*offset_ptr;

	string = (char *)ft_memalloc(sizeof(*string) * 100000);
	tag_string = (char *)ft_memalloc(sizeof(*tag_string) * 100000);
	tag_format_string = (char *)ft_memalloc(sizeof(*tag_format_string)
			* 100000);
	ft_strcat(string, "project=%s,algorithm=%s,algorithm_substring=%s");
	ft_strcat(string, ",puzzle_size=%d");
	ft_strcat(tag_format_string, string);
	ft_sprintf(tag_string, tag_format_string,
		"n-puzzle", statistics->algorithm, statistics->algorithm_substring,
		statistics->puzzle_size);
	ft_strcat(string, " execution_time=%di,total_cpu_usage_time=%di");
	ft_strcat(string, ",tile_moves=%di,max_mem_usage=%di");
	ft_strcat(string, ",solution_moves=%di");
	ft_strcat(string, ",puzzle_states=%di");
	ft_strcat(string, ",state_collisions=%di");
	ft_strcat(string, " %d\n");
	offset_ptr = add_counters_to_string(tag_string, &statistics->stat_counters,
			new_influxdb_query_string);
	ft_sprintf(offset_ptr, " %d\n", statistics->end_time);
	return (string);
}

void	influxdb_plugin(t_log_event *event)
{
	t_statistics	*statistics;
	char			*influxdb_query_string;
	char			*new_influxdb_query_string;
	char			*format_string;
	int				*counter_values;

	statistics = (t_statistics *)event->additional_event_data;
	counter_values = statistics->stat_counters.counter_values;
	if (statistics->order == E_SEND_TO_INFLUXDB)
	{
		influxdb_query_string
			= (char *)ft_memalloc(sizeof(*influxdb_query_string) * 100000);
		new_influxdb_query_string
			= (char *)ft_memalloc(sizeof(*new_influxdb_query_string) * 100000);
		statistics->stat_counters.active_counters[E_EXECUTION_TIME] = 1;
		counter_values[E_EXECUTION_TIME] = (int)get_execution_time(statistics);
		format_string = create_format_string(statistics,
				new_influxdb_query_string);
		ft_sprintf(influxdb_query_string, format_string,
			"n-puzzle", statistics->algorithm, statistics->algorithm_substring,
			statistics->puzzle_size,
			counter_values[E_EXECUTION_TIME],
			(int)statistics->cpu_usage_ms,
			statistics->tile_move_cnt, statistics->max_mem_usage,
			statistics->solution_move_cnt,
			counter_values[E_TOTAL_NUM_OF_PUZZLE_STATES],
			counter_values[E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS],
			statistics->end_time);
		write_influxdb(statistics->connection, new_influxdb_query_string,
			"Hive");
		ft_dprintf(2, influxdb_query_string);
		ft_dprintf(2, new_influxdb_query_string);
		ft_strdel(&influxdb_query_string);
		ft_strdel(&format_string);
	}
	return ;
}

void	stat_update_mem_usage(t_statistics *statistics)
{
	static int		free_mem_limit = 100000;
	static long		usage_prev;
	struct rusage	rusage;
	struct rlimit	rlim;
	long			av_phys_pages;
	long			tot_phys_pages;

	struct t_sysinfo
	{
		long uptime;             /* Seconds since boot */
		unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
		unsigned long totalram;  /* Total usable main memory size */
		unsigned long freeram;   /* Available memory size */
		unsigned long sharedram; /* Amount of shared memory */
		unsigned long bufferram; /* Memory used by buffers */
		unsigned long totalswap; /* Total swap space size */
		unsigned long freeswap;  /* swap space still available */
		unsigned short procs;    /* Number of current processes */
		unsigned long totalhigh; /* Total high memory size */
		unsigned long freehigh;  /* Available high memory size */
		unsigned int mem_unit;   /* Memory unit size in bytes */
		char _f[20-2*sizeof(long)-sizeof(int)]; /* Padding to 64 bytes */
	};

	struct sysinfo info;
	sysinfo(&info);
	usage_prev = 0;
	getrusage(RUSAGE_SELF, &rusage);
	getrlimit(RLIMIT_MEMLOCK, &rlim);
	av_phys_pages = get_avphys_pages();
	tot_phys_pages = get_phys_pages();
	if (rusage.ru_maxrss > free_mem_limit)
	{
		FT_LOG_WARN("Free Mem: CUR=%llx, MAX=%llx)", rlim.rlim_cur,
			rlim.rlim_max);
		FT_LOG_WARN("Mem usage: %ld (+%5ld)", rusage.ru_maxrss, rusage.ru_maxrss
			- usage_prev);
		FT_LOG_WARN("Free Mem: %lld", info.freehigh);
		FT_LOG_WARN("Available phys pages: %ld(%ld)", av_phys_pages,
			tot_phys_pages);
		free_mem_limit += 100000;
	}
	statistics->max_mem_usage = ft_max_int(statistics->max_mem_usage,
			(int)rusage.ru_maxrss);
	statistics->stat_counters.active_counters[E_MAX_MEM_USAGE] = 1;
	statistics->stat_counters.counter_values[E_MAX_MEM_USAGE]
		= statistics->max_mem_usage;
	usage_prev = rusage.ru_maxrss;
	return ;
}

void	set_total_cpu_usage_time(t_statistics *statistics)
{
	statistics->cpu_usage_ms = clock() / (CLOCKS_PER_SEC / 1000);
	statistics->stat_counters.active_counters[E_TOTAL_CPU_USAGE_TIME] = 1;
	statistics->stat_counters.counter_values[E_TOTAL_CPU_USAGE_TIME]
		= (int)statistics->cpu_usage_ms;
	FT_LOG_INFO("Used CPU time (ms): %ld", statistics->cpu_usage_ms);
	return ;
}

void	set_solver_start_time(t_statistics *statistics)
{
	statistics->solver_start_time_ms = clock() / (CLOCKS_PER_SEC / 1000);
	return ;
}

void	set_solver_end_time(t_statistics *statistics)
{
	statistics->solver_end_time_ms = clock() / (CLOCKS_PER_SEC / 1000);
	statistics->stat_counters.active_counters[E_SOLVER_CPU_USAGE_TIME] = 1;
	statistics->stat_counters.counter_values[E_SOLVER_CPU_USAGE_TIME]
		= statistics->solver_end_time_ms - statistics->solver_start_time_ms;
	FT_LOG_INFO("Solver CPU time (ms): %ld",
		statistics->stat_counters.counter_values[E_SOLVER_CPU_USAGE_TIME]);
	return ;
}
