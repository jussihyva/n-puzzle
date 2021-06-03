/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:52:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 10:17:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	search_key_position(t_bt_node *bt_node, t_bt_key *bt_key,
															t_bt_data *bt_data)
{
	int			min;
	int			mid;
	int			max;
	int			cmp_result;

	min = -1;
	max = bt_node->num_of_elems;
	bt_data->data = NULL;
	while (min + 1 < max && !bt_data->data)
	{
		mid = (min + max) / 2;
		cmp_result = ft_memcmp(bt_key->key, bt_node->bt_elem[mid].bt_key.key,
				bt_key->key_size);
		if (cmp_result > 0)
			min = mid;
		else if (cmp_result < 0)
			max = mid;
		else
		{
			max = mid;
			ft_memcpy(bt_data, &bt_node->bt_elem[mid].bt_data,
				sizeof(*bt_data));
		}
	}
	return (max);
}

int	find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node, t_bt_data *bt_data)
{
	int			i;
	t_bt_node	*bt_child_node;
	t_bt_node	*parent;

	i = search_key_position(*bt_node, bt_key, bt_data);
	if (!bt_data->data)
	{
		if (!(*bt_node)->num_of_elems)
			bt_child_node = NULL;
		else if (i == (*bt_node)->num_of_elems)
			bt_child_node = (*bt_node)->bt_elem[i - 1].right_child;
		else
			bt_child_node = (*bt_node)->bt_elem[i].left_child;
		if (bt_child_node)
		{
			parent = *bt_node;
			if (bt_child_node->num_of_elems >= MAX_NUM_OF_B_TREE_ELEMS)
				split_node(&bt_child_node, bt_node, bt_key);
			i = find_elem_index(bt_key, &bt_child_node, bt_data);
			*bt_node = bt_child_node;
		}
	}
	return (i);
}

static int	find_elem_index_2(t_bt_key *bt_key, t_bt_node **bt_node,
															t_bt_data *bt_data)
{
	int			i;
	t_bt_node	*bt_child_node;

	i = search_key_position(*bt_node, bt_key, bt_data);
	if (!bt_data->data)
	{
		if (!(*bt_node)->num_of_elems)
			bt_child_node = NULL;
		else if (i == (*bt_node)->num_of_elems)
			bt_child_node = (*bt_node)->bt_elem[i - 1].right_child;
		else
			bt_child_node = (*bt_node)->bt_elem[i].left_child;
		if (bt_child_node)
		{
			i = find_elem_index_2(bt_key, &bt_child_node, bt_data);
			*bt_node = bt_child_node;
		}
	}
	return (i);
}

void	ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root,
													t_bt_data *return_bt_data)
{
	return_bt_data->data = NULL;
	if (bt_root)
		find_elem_index_2(bt_key, &bt_root, return_bt_data);
	return ;
}
