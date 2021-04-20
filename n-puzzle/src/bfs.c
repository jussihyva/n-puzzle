/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:14:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/15 14:15:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	bfs(t_puzzle *puzzle, t_statistics *statistics)
{
	stat_set_start_time(puzzle->statistics);
	print_puzzle(1, puzzle);
	print_puzzle(2, puzzle);
	if (puzzle->algorithm == E_BFS)
		bfs_1(puzzle);
	else
		FT_LOG_ERROR("Functionality is not implemented for the algorithm. %s",
			"Specify an other algorithm with the param -A");
	stat_set_end_time(puzzle->statistics);
	stat_update_cpu_usage(statistics);
	statistics->order = E_SEND_TO_INFLUXDB;
	FT_LOG_INFO("Execution time : %ld", get_execution_time(puzzle->statistics));
	statistics->order = E_NONE;
	FT_LOG_INFO("Total num of moves: %lu", *puzzle->move_cnt);
	return ;
}