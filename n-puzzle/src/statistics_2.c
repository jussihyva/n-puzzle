/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:00:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/10 12:58:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static char	**create_stat_counter_string_names(void)
{
	char	**string;

	string = (char **)ft_memalloc(sizeof(*string) * NUM_OF_STAT_COUNTERS);
	string[E_PUZZLE_INITIAL_STATE] = ft_strdup("");
	string[E_PUZZLE_FINAL_STATE] = ft_strdup("");
	string[E_IS_PUZZLE_SOLVABLE] = ft_strdup("RRRRRR");
	string[E_IS_PUZZLE_SOLVED] = ft_strdup("");
	string[E_IS_TIME_LIMIT_REACHED] = ft_strdup("time_limit=%di");
	string[E_IS_MEM_LIMIT_REACHED] = ft_strdup("mem_limit=%di");
	string[E_NUM_OF_SOLUTION_MOVES] = ft_strdup("solution_moves=%di");
	string[E_EXECUTION_TIME] = ft_strdup("execution_time=%di");
	string[E_TOTAL_CPU_USAGE_TIME] = ft_strdup("total_cpu_usage_time=%di");
	string[E_SOLVER_CPU_USAGE_TIME] = ft_strdup("solver_cpu_usage_time=%di");
	string[E_PRINTING_CPU_USAGE_TIME] = ft_strdup("");
	string[E_TOTAL_NUM_OF_PUZZLE_STATES] = ft_strdup("puzzle_states=%di");
	string[E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS]
		= ft_strdup("state_collisions=%di");
	string[E_MAX_NUM_OF_SAVED_PUZZLE_STATES] = ft_strdup("");
	string[E_MAX_QUEUE_LEN] = ft_strdup("");
	string[E_TOTAL_NUM_OF_ELEM_IN_QUEUE] = ft_strdup("");
	string[E_MAX_MEM_USAGE] = ft_strdup("max_mem_usage=%di");
	string[E_MIN_FREE_MEM] = ft_strdup("");
	return (string);
}

t_statistics	*initialize_statistics(void)
{
	t_statistics	*statistics;

	statistics = (t_statistics *)ft_memalloc(sizeof(*statistics));
	statistics->stat_counters.counter_names
		= create_stat_counter_string_names();
	statistics->stat_counters.active_counters[E_TOTAL_NUM_OF_PUZZLE_STATES] = 1;
	statistics->stat_counters.active_counters[
		E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS] = 1;
	return (statistics);
}

#if DARWIN

void	check_mem_usage(t_memory_info *memory_info, t_statistics *statistics)
{
	(void)statistics;
	memory_info->av_phys_pages = 0;
	memory_info->tot_phys_pages = 0;
	memory_info->mem_usage = (int)memory_info->rusage.ru_maxrss / 1000;
	return ;
}
#else

void	check_mem_usage(t_memory_info *memory_info, t_statistics *statistics)
{
	struct sysinfo		info;

	sysinfo(&info);
	memory_info->av_phys_pages = get_avphys_pages();
	memory_info->tot_phys_pages = get_phys_pages();
	statistics->stat_counters.active_counters[E_IS_MEM_LIMIT_REACHED] = 1;
	if (memory_info->av_phys_pages < 50000)
		statistics->stat_counters.counter_values[E_IS_MEM_LIMIT_REACHED] = 1;
	memory_info->mem_usage = (int)memory_info->rusage.ru_maxrss;
	return ;
}

#endif

void	stat_update_mem_usage(t_statistics *statistics)
{
	static t_memory_info	memory_info;

	if (!memory_info.mem_limit)
		memory_info.mem_limit = 1000000;
	getrusage(RUSAGE_SELF, &memory_info.rusage);
	getrlimit(RLIMIT_MEMLOCK, &memory_info.rlim);
	check_mem_usage(&memory_info, statistics);
	statistics->stat_counters.active_counters[E_IS_TIME_LIMIT_REACHED] = 1;
	if ((PUZZLE_SOLVING_TIME_LIMIT * MINUTE * MILLI_SECONDS)
		< (clock() / (CLOCKS_PER_SEC / 1000)))
		statistics->stat_counters.counter_values[E_IS_TIME_LIMIT_REACHED] = 1;
	if (memory_info.mem_usage > memory_info.mem_limit)
	{
		FT_LOG_WARN("Mem usage: %ld (+%5ld)", memory_info.mem_usage,
			memory_info.mem_usage - memory_info.usage_prev);
		FT_LOG_WARN("Available phys pages: %ld(%ld)", memory_info.av_phys_pages,
			memory_info.tot_phys_pages);
		memory_info.mem_limit += 200000;
		memory_info.usage_prev = memory_info.mem_usage;
	}
	statistics->stat_counters.active_counters[E_MAX_MEM_USAGE] = 1;
	statistics->stat_counters.counter_values[E_MAX_MEM_USAGE]
		= ft_max_int(statistics->stat_counters.counter_values[E_MAX_MEM_USAGE],
			memory_info.mem_usage);
	return ;
}
