/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:14:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/03 15:55:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	dfs(t_map *puzzle_map, t_statistics *statistics, t_cmd_args *cmd_args)
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
	if (!ft_strcmp(cmd_args->algorithm, "dfs_1"))
		dfs_no_mem(puzzle, right_pos_status, statistics);
	else if (!ft_strcmp(cmd_args->algorithm, "dfs_2"))
		dfs_deeping(puzzle, right_pos_status, statistics);
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", cmd_args->algorithm,
			"Specify a valid algorithm with the param -A");
	ft_printf("END\n");
	release_puzzle(puzzle);
	return ;
}
