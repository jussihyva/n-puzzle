/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:25:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/04 10:28:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	remove_data_from_queue(t_queue *queue,
									void ((*fn)(void *data, size_t size)))
{
	void	*data;

	while (!ft_is_queue_empty(queue))
	{
		data = ft_dequeue(queue);
		fn(data, 0);
	}
	ft_memdel((void **)&queue->in_stack);
	ft_memdel((void **)&queue->out_stack);
	ft_memdel((void **)&queue);
	return ;
}

void	ft_bt_remove(t_bt_node **bt_node, t_bt_key *bt_key,
										void ((*fn)(void *data, size_t size)))
{
	t_bt_elem	*bt_elem;
	t_bt_node	*bt_child_node;
	int			i;

	i = -1;
	while (*bt_node && ++i < (*bt_node)->num_of_elems)
	{
		bt_elem = &(*bt_node)->bt_elem[i];
		if (bt_elem->is_queue)
			remove_data_from_queue((t_queue *)bt_elem->bt_data.data, fn);
		else if (bt_key)
			fn((void *)&bt_elem->bt_data, 0);
		bt_child_node = bt_elem->left_child;
		if (bt_child_node)
			ft_bt_remove(&bt_child_node, bt_key, fn);
		bt_child_node = bt_elem->right_child;
		if (bt_child_node && i == (*bt_node)->num_of_elems - 1)
			ft_bt_remove(&bt_child_node, bt_key, fn);
	}
	ft_memdel((void **)bt_node);
	return ;
}
