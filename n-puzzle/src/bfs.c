/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:14:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/04 07:24:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	bfs(t_puzzle *puzzle)
{
	stat_set_start_time(puzzle->statistics);
	print_puzzle(1, puzzle->curr_status->tiles_pos_map, puzzle->size);
	print_puzzle(2, puzzle->curr_status->tiles_pos_map, puzzle->size);
	if (puzzle->algorithm == E_BFS_1)
		bfs_1(puzzle);
	else if (puzzle->algorithm == E_BFS_2)
		bfs_1(puzzle);
	else
		FT_LOG_ERROR("Functionality is not implemented for the algorithm. %s",
			"Specify an other algorithm with the param -A");
	return ;
}
