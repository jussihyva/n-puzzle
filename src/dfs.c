/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:14:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/08 10:23:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	dfs(t_puzzle *puzzle, t_statistics *statistics, t_cmd_args *cmd_args)
{
	stat_set_start_time(puzzle->statistics);
	print_puzzle(1, puzzle);
	print_puzzle(2, puzzle);
	if (!ft_strcmp(cmd_args->algorithm, "dfs_1"))
	{
		statistics->algorithm_substring = ft_strdup("no_mem_rand");
		dfs_no_mem(puzzle);
	}
	else if (!ft_strcmp(cmd_args->algorithm, "dfs_2"))
	{
		statistics->algorithm_substring = ft_strdup("deeping");
		dfs_deeping(puzzle);
	}
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", cmd_args->algorithm,
			"Specify a valid algorithm with the param -A");
	stat_set_end_time(puzzle->statistics);
	statistics->order = E_SEND_TO_INFLUXDB;
	FT_LOG_INFO("Execution time : %ld", get_execution_time(puzzle->statistics));
	statistics->order = E_NONE;
	FT_LOG_INFO("Total num of moves: %lu", *puzzle->move_cnt);
	release_puzzle(puzzle);
	return ;
}
