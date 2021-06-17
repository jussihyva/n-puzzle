/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:14:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 13:24:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

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

int	check_is_limit_reached(int *counter_values)
{
	int		is_limit_reached;

	is_limit_reached = 0;
	if (counter_values[E_IS_MEM_LIMIT_REACHED]
		|| counter_values[E_IS_TIME_LIMIT_REACHED])
		is_limit_reached = 1;
	return (is_limit_reached);
}
