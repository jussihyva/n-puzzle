/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:14:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/15 14:15:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	dfs(t_puzzle *puzzle, t_statistics *statistics)
{
	stat_set_start_time(puzzle->statistics);
	print_puzzle(1, puzzle);
	print_puzzle(2, puzzle);
	if (puzzle->algorithm == E_DFS_NO_MEM)
		dfs_no_mem(puzzle);
	else if (puzzle->algorithm == E_DFS_DEEPING)
		dfs_deeping(puzzle);
	else if (puzzle->algorithm == E_DFS_DEEPING_MEM)
		dfs_deeping_mem(puzzle);
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
