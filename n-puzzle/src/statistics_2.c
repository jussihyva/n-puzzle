/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/01 15:08:50 by jkauppi          ###   ########.fr       */
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
	stat_counter_string_names[E_IS_TIME_LIMIT_REACHED]
		= ft_strdup("time_limit=%di");
	stat_counter_string_names[E_IS_MEM_LIMIT_REACHED]
		= ft_strdup("mem_limit=%di");
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

static char	*create_influxdb_query_string(t_statistics *statistics)
{
	char	*influxdb_query_string;
	char	*string;
	char	*tag_format_string;
	char	*tag_string;
	char	*offset_ptr;

	influxdb_query_string
		= (char *)ft_memalloc(sizeof(*influxdb_query_string) * 100000);
	string = (char *)ft_memalloc(sizeof(*string) * 100000);
	tag_string = (char *)ft_memalloc(sizeof(*tag_string) * 100000);
	tag_format_string = (char *)ft_memalloc(sizeof(*tag_format_string)
			* 100000);
	ft_strcat(string, "project=%s,algorithm=%s,algorithm_substring=%s");
	ft_strcat(string, ",puzzle_size=%d");
	ft_strcat(tag_format_string, string);
	ft_sprintf(tag_string, tag_format_string, "n-puzzle", statistics->algorithm,
		statistics->algorithm_substring, statistics->puzzle_size);
	offset_ptr = add_counters_to_string(tag_string, &statistics->stat_counters,
			influxdb_query_string);
	ft_sprintf(offset_ptr, " %d\n", statistics->end_time);
	ft_memdel((void **)&string);
	return (influxdb_query_string);
}

void	influxdb_plugin(t_log_event *event)
{
	t_statistics	*statistics;
	char			*influxdb_query_string;
	int				*counter_values;

	statistics = (t_statistics *)event->additional_event_data;
	counter_values = statistics->stat_counters.counter_values;
	if (statistics->order == E_SEND_TO_INFLUXDB)
	{
		statistics->stat_counters.active_counters[E_EXECUTION_TIME] = 1;
		counter_values[E_EXECUTION_TIME] = (int)get_execution_time(statistics);
		influxdb_query_string = create_influxdb_query_string(statistics);
		write_influxdb(statistics->connection, influxdb_query_string, "Hive");
	}
	return ;
}

static void	check_mac_mem_usage(void)
{
	// int mib[5], val;
	// size_t len;

	// mib[0] = CTL_NET;
	// mib[1] = AF_INET;
	// mib[2] = CTL_VM;
	// mib[3] = UDPCTL_CHECKSUM;
	// len = sizeof(val);
	// sysctl(mib, 4, &val, &len, NULL, 0);
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
	int				mem_usage;

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

	usage_prev = 0;
	getrusage(RUSAGE_SELF, &rusage);
	getrlimit(RLIMIT_MEMLOCK, &rlim);
# if DARWIN
	check_mac_mem_usage();
	av_phys_pages = 0;
	tot_phys_pages = 0;
	mem_usage = (int)rusage.ru_maxrss / 1000;
# else
	struct sysinfo info;
	sysinfo(&info);
	av_phys_pages = get_avphys_pages();
	tot_phys_pages = get_phys_pages();
	mem_usage = (int)rusage.ru_maxrss;
	statistics->stat_counters.active_counters[E_IS_MEM_LIMIT_REACHED] = 1;
	if (av_phys_pages < 50000)
		statistics->stat_counters.counter_values[E_IS_MEM_LIMIT_REACHED] = 1;
# endif
	statistics->stat_counters.active_counters[E_IS_TIME_LIMIT_REACHED] = 1;
	if (300000 < (clock() / (CLOCKS_PER_SEC / 1000)))
		statistics->stat_counters.counter_values[E_IS_TIME_LIMIT_REACHED] = 1;
	if (mem_usage > free_mem_limit)
	{
		FT_LOG_WARN("Free Mem: CUR=%llx, MAX=%llx)", rlim.rlim_cur,
			rlim.rlim_max);
		FT_LOG_WARN("Mem usage: %ld (+%5ld)", mem_usage, mem_usage
			- usage_prev);
		FT_LOG_WARN("Available phys pages: %ld(%ld)", av_phys_pages,
			tot_phys_pages);
		free_mem_limit += 100000;
	}
	statistics->max_mem_usage = ft_max_int(statistics->max_mem_usage,
			mem_usage);
	statistics->stat_counters.active_counters[E_MAX_MEM_USAGE] = 1;
	statistics->stat_counters.counter_values[E_MAX_MEM_USAGE]
		= statistics->max_mem_usage;
	usage_prev = mem_usage;
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
