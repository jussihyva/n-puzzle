/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:14:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/28 12:51:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	dfs(t_puzzle *puzzle)
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
	return ;
}
