/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_puzzle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:19:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 09:56:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

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

static void	release_pos_table(int puzzle_size, t_pos ****pos_table)
{
	t_xy_values			yx;

	yx.y = -1;
	while (++yx.y < puzzle_size)
	{
		yx.x = -1;
		while (++yx.x < puzzle_size)
		{
			ft_memdel((void **)&(*pos_table)[yx.y][yx.x]->neighbors);
			ft_memdel((void **)&(*pos_table)[yx.y][yx.x]);
		}
		ft_memdel((void **)&(*pos_table)[yx.y]);
	}
	return ;
}

static void	release_puzzle(t_puzzle *puzzle)
{
	ft_bt_remove(puzzle->states_prio_queue, NULL, NULL);
	ft_memdel((void **)&puzzle->states_prio_queue);
	ft_bt_remove(puzzle->bt_root, &(*puzzle->bt_root)->bt_elem[0].bt_key,
		delete_puzzle_status);
	ft_memdel((void **)&puzzle->bt_root);
	release_status_queue(puzzle->status_queue);
	ft_lstdel(puzzle->puzzle_status_lst, delete_puzzle_status_from_lst);
	ft_memdel((void **)&puzzle->puzzle_status_lst);
	release_pos_table(puzzle->size, &puzzle->pos_table);
	ft_memdel((void **)&puzzle->pos_table);
	ft_memdel((void **)&puzzle->curr_status->tiles_pos_map.map);
	ft_memdel((void **)&puzzle->curr_status);
	ft_memdel((void *)&puzzle->tile_right_pos_array);
	ft_memdel((void **)&puzzle);
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
