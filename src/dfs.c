/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 21:14:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 09:14:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	dfs(t_puzzle *puzzle, t_statistics *statistics, t_cmd_args *cmd_args)
{
	set_start_time();
	print_puzzle(1, puzzle);
	print_puzzle(2, puzzle);
	if (!ft_strcmp(cmd_args->algorithm, "dfs_1"))
		dfs_no_mem(puzzle, statistics);
	else if (!ft_strcmp(cmd_args->algorithm, "dfs_2"))
		dfs_deeping(puzzle, statistics);
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", cmd_args->algorithm,
			"Specify a valid algorithm with the param -A");
	ft_printf("END\n");
	release_puzzle(puzzle);
	return ;
}
