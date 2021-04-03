/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:14:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/02 23:53:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	dfs(t_map *puzzle_map, t_statistics *statistics)
{
	t_puzzle		*puzzle;
	unsigned int	right_pos_status;
	unsigned long	*move_cnt;

	set_start_time();
	move_cnt = &statistics->tile_move_cnt;
	puzzle = initialize_puzzle(puzzle_map, &right_pos_status);
	puzzle->move_cnt = &statistics->tile_move_cnt;
	print_puzzle(1, puzzle);
	print_puzzle(2, puzzle);
	// dfs_no_mem(puzzle, right_pos_status, statistics);
	dfs_deeping(puzzle, right_pos_status, statistics);
	ft_printf("END\n");
	release_puzzle(puzzle);
	return ;
}
