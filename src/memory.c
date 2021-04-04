/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:19:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 17:13:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	release_puzzle(t_puzzle *puzzle)
{
	int		i;
	int		j;

	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
		{
			ft_memdel((void **)&puzzle->pos_table[i][j]->neighbors);
			ft_memdel((void **)&puzzle->pos_table[i][j]);
		}
		ft_memdel((void **)&puzzle->pos_table[i]);
	}
	ft_memdel((void **)&puzzle->pos_table);
	ft_memdel((void **)&puzzle);
	return ;
}

void	release_input(t_input *input)
{
	int		i;

	i = -1;
	while (++i < LOGING_LEVELS)
	{
		ft_memdel((void **)&input->level_colors[i]);
		ft_memdel((void **)&input->level_strings[i]);
	}
	ft_memdel((void **)&input->level_colors);
	ft_memdel((void **)&input->level_strings);
	i = -1;
	while (++i < input->puzzle_map->size)
		ft_memdel((void **)&input->puzzle_map->tile_map[i]);
	ft_memdel((void **)&input->cmd_args);
	ft_memdel((void **)&input->puzzle_map->tile_map);
	ft_memdel((void **)&input->puzzle_map);
	ft_memdel((void **)&input);
	ft_release_loging_params();
	ft_release_statistics_params();
	return ;
}
