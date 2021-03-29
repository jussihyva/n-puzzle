/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 16:56:08 by jkauppi          ###   ########.fr       */
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

static void	print_neighbors(t_puzzle *puzzle)
{
	int		i;
	int		j;
	int		k;

	ft_printf(" %d\n", puzzle->size);
	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
		{
			k = -1;
			while (++k < MAX_NUM_OF_NEIGHBOR)
				if (puzzle->tile_pos_table[i][j]->neighbors[k])
					ft_printf(" %4d", ((t_tile_pos *)
							puzzle->tile_pos_table[i][j]->neighbors[k])->num);
		}
		ft_printf("\n");
	}
	return ;
}

void	dfs(t_map *puzzle_map)
{
	t_puzzle		*puzzle;

	puzzle = initialize_puzzle(puzzle_map);
	print_puzzle(puzzle);
	print_neighbors(puzzle);
	release_puzzle(puzzle);
	return ;
}
