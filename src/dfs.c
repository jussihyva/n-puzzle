/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:58:01 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/30 08:54:57 by jkauppi          ###   ########.fr       */
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

// static unsigned int	update_right_pos_status(t_puzzle *puzzle)
// {
// 	unsigned int	right_pos_status;


// 	return (right_pos_status);
// }

static void	dfs_no_mem(t_puzzle *puzzle, unsigned int right_pos_status)
{
	int				i;
	t_tile_pos		*tile_pos;
	t_tile_pos		*next_tile_pos;

	FT_LOG_INFO("Righ position status: %u", right_pos_status);
	tile_pos = puzzle->root_tile;
	while (1)
	{
		i = tile_pos->next_neighbor++;
		tile_pos->next_neighbor = ft_mod_int(tile_pos->next_neighbor,
				tile_pos->num_of_neighbors);
		next_tile_pos = tile_pos->neighbors[i];
		if (next_tile_pos)
		{
			tile_num_swap(tile_pos, next_tile_pos);
			// right_pos_status = update_right_pos_status(puzzle, &right_pos_status);
			usleep(300000);
			print_puzzle(puzzle);
			tile_pos = next_tile_pos;
		}
	}
	return ;
}

void	dfs(t_map *puzzle_map)
{
	t_puzzle		*puzzle;
	unsigned int	right_pos_status;

	puzzle = initialize_puzzle(puzzle_map, &right_pos_status);
	print_puzzle(puzzle);
	dfs_no_mem(puzzle, right_pos_status);
	release_puzzle(puzzle);
	return ;
}
