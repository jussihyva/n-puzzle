/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prio_dequeue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:24:29 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/23 11:36:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	remove_node(t_bt_node *bt_node, t_bt_node *parent,
												t_bt_node **states_prio_queue)
{
	if (bt_node->bt_elem[0].right_child)
	{
		if (parent)
			parent->bt_elem[0].left_child = bt_node->bt_elem[0].right_child;
		else
			*states_prio_queue = bt_node->bt_elem[0].right_child;
	}
	else
	{
		if (parent)
			parent->bt_elem[0].left_child = NULL;
		else
			*states_prio_queue = NULL;
	}
	ft_memdel((void **)&bt_node);
	return ;
}

static void	remove_first_element(t_bt_elem *bt_elem, int *num_of_elems)
{
	(*num_of_elems)--;
	if (*num_of_elems > 0)
		ft_memmove(bt_elem, &bt_elem[1], sizeof(*bt_elem) * *num_of_elems);
	return ;
}

static void	*get_data_from_queue(t_bt_node *bt_node)
{
	void		*data;
	t_queue		*queue;

	queue = (t_queue *)bt_node->bt_elem[0].bt_data.data;
	data = ft_dequeue(queue);
	if (ft_is_queue_empty(queue))
	{
		ft_memdel((void **)&queue->in_stack);
		ft_memdel((void **)&queue->out_stack);
		ft_memdel((void **)&queue);
		remove_first_element(&bt_node->bt_elem[0], &bt_node->num_of_elems);
	}
	return (data);
}

void	*ft_prio_dequeue(t_bt_node **states_prio_queue)
{
	void		*data;
	t_bt_node	*bt_node;
	t_bt_node	*parent;
	t_bt_elem	*bt_elem;

	bt_node = *states_prio_queue;
	parent = NULL;
	while (bt_node->bt_elem[0].left_child)
	{
		parent = bt_node;
		bt_node = bt_node->bt_elem[0].left_child;
	}
	bt_elem = &bt_node->bt_elem[0];
	if (bt_elem->is_queue)
		data = get_data_from_queue(bt_node);
	else
	{
		data = bt_elem->bt_data.data;
		remove_first_element(bt_elem, &bt_node->num_of_elems);
	}
	if (!bt_node->num_of_elems)
		remove_node(bt_node, parent, states_prio_queue);
	return (data);
}
