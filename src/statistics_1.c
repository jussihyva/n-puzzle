/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 23:44:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/05 09:36:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_statistics		*g_statistics = NULL;

t_statistics	*get_statistics(void)
{
	initialize_statistics(&g_statistics);
	return (g_statistics);
}

void	set_start_time(void)
{
	double		ms;

	initialize_statistics(&g_statistics);
	clock_gettime(_POSIX_MONOTONIC_CLOCK, &g_statistics->start_time);
	g_statistics->start_time_ms = g_statistics->start_time.tv_sec * 1000;
	ms = round(g_statistics->start_time.tv_nsec / 1.0e6);
	if (ms > 999)
	{
		g_statistics->start_time_ms++;
		ms = 0;
	}
	g_statistics->start_time_ms += ms;
	return ;
}

void	set_end_time(void)
{
	double		ms;

	initialize_statistics(&g_statistics);
	clock_gettime(_POSIX_MONOTONIC_CLOCK, &g_statistics->end_time);
	g_statistics->end_time_ms = g_statistics->end_time.tv_sec * 1000;
	ms = round(g_statistics->end_time.tv_nsec / 1.0e6);
	if (ms > 999)
	{
		g_statistics->end_time_ms++;
		ms = 0;
	}
	g_statistics->end_time_ms += ms;




	return ;
}

time_t	get_execution_time(void)
{
	time_t	execution_time;

	initialize_statistics(&g_statistics);
	execution_time = (int)(g_statistics->end_time_ms
			- g_statistics->start_time_ms);
	return (execution_time);
}

void	ft_release_statistics_params(void)
{
	initialize_statistics(&g_statistics);
	if (g_statistics)
		ft_memdel((void **)&g_statistics);
	return ;
}
