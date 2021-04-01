/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 23:44:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 10:55:55 by jkauppi          ###   ########.fr       */
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
	initialize_statistics(&g_statistics);
	g_statistics->start_time = time(NULL);
	return ;
}

void	set_end_time(void)
{
	initialize_statistics(&g_statistics);
	g_statistics->end_time = time(NULL);
	return ;
}

time_t	get_execution_time(void)
{
	time_t	execution_time;

	initialize_statistics(&g_statistics);
	execution_time = g_statistics->end_time - g_statistics->start_time;
	return (execution_time);
}

void	ft_release_statistics_params(void)
{
	initialize_statistics(&g_statistics);
	if (g_statistics)
		ft_memdel((void **)&g_statistics);
	return ;
}
