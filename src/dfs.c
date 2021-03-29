/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 23:37:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	print_puzzle(t_puzzle *puzzle)
{
	int		i;
	int		j;
	char	line[1000];
	char	string[6];

	ft_printf(" %d\n", puzzle->size);
	i = -1;
	while (++i < puzzle->size)
	{
		ft_bzero(line, sizeof(line));
		j = -1;
		while (++j < puzzle->size)
		{
			ft_sprintf(string, " %4d", puzzle->tile_pos_table[i][j]->num);
			ft_strcat(line, string);
		}
		ft_printf("%s\n", line);
	}
	return ;
}

static void	tile_num_swap(t_tile_pos *tile_pos_1, t_tile_pos *tile_pos_2)
{
	int		tmp;

	tmp = tile_pos_1->num;
	tile_pos_1->num = tile_pos_2->num;
	tile_pos_2->num = tmp;
	return ;
}

static void	dfs_no_mem(t_puzzle *puzzle)
{
	int				i;
	t_tile_pos		*tile_pos;
	t_tile_pos		*next_tile_pos;

	tile_pos = puzzle->root_tile;
	tile_pos->is_visited = 1;
	while (1)
	{
		i = ft_mod_int(rand(), 4) - 1;
		while (++i < MAX_NUM_OF_NEIGHBOR)
		{
			next_tile_pos = tile_pos->neighbors[i];
			if (next_tile_pos && !next_tile_pos->is_visited)
			{
				tile_num_swap(tile_pos, next_tile_pos);
				usleep(300000);
				print_puzzle(puzzle);
				tile_pos = next_tile_pos;
				tile_pos->is_visited = 1;
				break ;
			}
		}
	}
	return ;
}

void	dfs(t_map *puzzle_map)
{
	t_puzzle		*puzzle;

	puzzle = initialize_puzzle(puzzle_map);
	print_puzzle(puzzle);
	dfs_no_mem(puzzle);
	release_puzzle(puzzle);
	return ;
}
