/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_puzzle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:19:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/21 17:07:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

// static void	release_prio_queue(t_queue *states_prio_queue)
// {
// 	while (states_prio_queue)
// 	{

// 	}
// 	return ;
// }

static void	release_status_queue(t_queue *status_queue)
{
	t_puzzle_status		*puzzle_status;

	while (!ft_is_queue_empty(status_queue))
		puzzle_status = (t_puzzle_status *)ft_dequeue(status_queue);
	ft_memdel((void **)&status_queue->in_stack);
	ft_memdel((void **)&status_queue->out_stack);
	ft_memdel((void **)&status_queue);
	return ;
}

static void	release_puzzle(t_puzzle *puzzle)
{
	int					i;
	int					j;

	ft_bt_remove(puzzle->states_prio_queue, NULL);
	ft_memdel((void **)&puzzle->states_prio_queue);
	ft_bt_remove(puzzle->bt_root, NULL);
	ft_memdel((void **)&puzzle->bt_root);
	release_status_queue(puzzle->status_queue);
	ft_lstdel(puzzle->puzzle_status_lst, delete_puzzle_status);
	ft_memdel((void **)&puzzle->puzzle_status_lst);
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
	ft_memdel((void **)&puzzle->curr_status);
	ft_memdel((void **)&puzzle);
	return ;
}

static void	release_input(t_input *input)
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
	ft_memdel((void **)&input->cmd_args->heurestic_algorithm);
	ft_memdel((void **)&input->cmd_args);
	ft_memdel((void **)&input->puzzle_map->tile_map);
	ft_memdel((void **)&input->puzzle_map);
	ft_memdel((void **)&input);
	ft_release_loging_params();
	return ;
}

static void	release_influxdb(t_influxdb *influxdb)
{
	t_tls_connection	*tls_connection;

	tls_connection = (t_tls_connection *)influxdb->connection;
	ft_openssl_rel_conn(&tls_connection);
	ft_memdel((void **)&influxdb);
	return ;
}

void	release(t_input *input, t_influxdb *influxdb, t_puzzle *puzzle)
{
	if (input->cmd_args->release)
		ft_printf("END\n");
	release_puzzle(puzzle);
	release_influxdb(influxdb);
	release_input(input);
	return ;
}
