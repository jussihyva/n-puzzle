/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:19:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/11 03:48:37 by jkauppi          ###   ########.fr       */
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
			ft_memdel((void **)&puzzle->curr_status->pos_table[i][j]->neighbors);
			ft_memdel((void **)&puzzle->curr_status->pos_table[i][j]);
			ft_memdel((void **)&puzzle->tile_array[i * puzzle->size + j]);
		}
		ft_memdel((void **)&puzzle->curr_status->pos_table[i]);
	}
	ft_memdel((void **)&puzzle->curr_status->pos_table);
	ft_memdel((void **)&puzzle->tile_array);
	ft_memdel((void **)&puzzle);
	return ;
}

void	release_input(t_input *input)
{
	int		i;

	release_statistics_params(input->statistics);
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
	return ;
}

void	release_influxdb(t_influxdb *influxdb)
{
	t_tls_connection	*tls_connection;

	tls_connection = (t_tls_connection *)influxdb->connection;
	ft_openssl_rel_conn(&tls_connection);
	ft_memdel((void **)&influxdb);
	return ;
}
