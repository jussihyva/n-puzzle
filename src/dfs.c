/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 15:00:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	print_puzzle(t_puzzle *puzzle)
{
	int		i;
	int		j;

	ft_printf(" %d\n", puzzle->size);
	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
			ft_printf(" %4d", puzzle->tile_pos_table[i][j]->order_num);
		ft_printf("\n");
	}
	return ;
}

void	dfs(t_map *puzzle_map)
{
	t_puzzle		*puzzle;

	puzzle = initialize_puzzle(puzzle_map);
	print_puzzle(puzzle);
	release_puzzle(puzzle);
	return ;
}
