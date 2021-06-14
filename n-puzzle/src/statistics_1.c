/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 23:44:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/14 14:34:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

#if DARWIN
static void	get_time(struct timespec *time)
{
	clock_gettime(CLOCK_REALTIME, time);
	return ;
}
#else

static void	get_time(struct timespec *time)
{
	clock_gettime(_POSIX_MONOTONIC_CLOCK, time);
	return ;
}
#endif

void	stat_set_start_time(t_statistics *statistics)
{
	double		ms;

	get_time(&statistics->start_time);
	statistics->start_time_ms = statistics->start_time.tv_sec * 1000;
	ms = round(statistics->start_time.tv_nsec / 1.0e6);
	if (ms > 999)
	{
		statistics->start_time_ms++;
		ms = 0;
	}
	statistics->start_time_ms += ms;
	return ;
}

void	stat_set_end_time(t_statistics *statistics)
{
	double		ms;

	get_time(&statistics->end_time);
	statistics->end_time_ms = statistics->end_time.tv_sec * 1000;
	ms = round(statistics->end_time.tv_nsec / 1.0e6);
	if (ms > 999)
	{
		statistics->end_time_ms++;
		ms = 0;
	}
	statistics->end_time_ms += ms;
	return ;
}

time_t	get_execution_time(t_statistics *statistics)
{
	time_t	execution_time;

	execution_time = (time_t)(statistics->end_time_ms
			- statistics->start_time_ms);
	return (execution_time);
}
