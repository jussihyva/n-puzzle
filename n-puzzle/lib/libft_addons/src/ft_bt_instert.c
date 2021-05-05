/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_instert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 13:32:44 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/05 07:45:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	save_bt_elem(t_bt_node *bt_node, int i, t_bt_elem *bt_elem)
{
	size_t		move_size;

	if (i != bt_node->num_of_elems)
	{
		move_size = sizeof(bt_node->bt_elem[i + 1])
			* (bt_node->num_of_elems - i);
		ft_memmove(&bt_node->bt_elem[i + 1], &bt_node->bt_elem[i], move_size);
	}
	if (i)
	{
		if (bt_elem->left_child)
			bt_node->bt_elem[i - 1].right_child = bt_elem->left_child;
		else
			bt_elem->left_child = bt_node->bt_elem[i - 1].right_child;
	}
	if (i < bt_node->num_of_elems)
	{
		if (bt_elem->right_child)
			bt_node->bt_elem[i + 1].left_child = bt_elem->right_child;
		else
			bt_elem->right_child = bt_node->bt_elem[i + 1].left_child;
	}
	ft_memcpy(&bt_node->bt_elem[i], bt_elem, sizeof(bt_node->bt_elem[i]));
	bt_node->num_of_elems++;
	return ;
}

/**
 * @brief 
 * 
 * @param bt_node 
 * @param bt_key 
 * @param bt_data 
 * @return int 
 */
static int	search_key_position(t_bt_node *bt_node, t_bt_key *bt_key,
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

static t_bt_node	*initialize_new_node(t_bt_node *bt_node, int i)
{
	t_bt_node	*new_node;
	size_t		move_size;

	new_node = (t_bt_node *)ft_memalloc(sizeof(*new_node));
	move_size = sizeof(new_node->bt_elem[0]) * (bt_node->num_of_elems - i - 1);
	ft_memcpy(&new_node->bt_elem[0], &bt_node->bt_elem[i + 1], move_size);
	new_node->num_of_elems = bt_node->num_of_elems - i - 1;
	return (new_node);
}

static void	split_node(t_bt_node **bt_node, t_bt_node **parent,
															t_bt_key *bt_key)
{
	int			i;
	t_bt_node	*new_node;
	t_bt_elem	*new_bt_elem;
	t_bt_data	bt_data;
	int			cmp_result;

	i = (*bt_node)->num_of_elems / 2;
	if (!*parent)
		*parent = (t_bt_node *)ft_memalloc(sizeof(**parent));
	new_node = initialize_new_node(*bt_node, i);
	(*bt_node)->num_of_elems = i;
	new_bt_elem = &(*bt_node)->bt_elem[i];
	new_bt_elem->left_child = *bt_node;
	new_bt_elem->right_child = new_node;
	i = search_key_position(*parent, &new_bt_elem->bt_key, &bt_data);
	save_bt_elem(*parent, i, new_bt_elem);
	cmp_result = ft_memcmp(bt_key->key, new_bt_elem->bt_key.key,
			bt_key->key_size);
	if (cmp_result > 0)
		*bt_node = new_bt_elem->right_child;
	return ;
}

int	find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node, t_bt_data *bt_data)
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
			if (bt_child_node->num_of_elems >= MAX_NUM_OF_B_TREE_ELEMS)
				split_node(&bt_child_node, bt_node, bt_key);
			i = find_elem_index(bt_key, &bt_child_node, bt_data);
			*bt_node = bt_child_node;
		}
	}
	return (i);
}

static void	instert_elem(t_bt_node *bt_node, t_bt_node **parent,
															t_bt_elem *bt_elem)
{
	int				i;
	t_bt_data		bt_data;

	if (bt_node->num_of_elems >= MAX_NUM_OF_B_TREE_ELEMS)
		split_node(&bt_node, parent, &bt_elem->bt_key);
	i = find_elem_index(&bt_elem->bt_key, &bt_node, &bt_data);
	if (bt_data.data)
		return ;
	save_bt_elem(bt_node, i, bt_elem);
	return ;
}

void	ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data, t_bt_node **bt_root)
{
	t_bt_node		*bt_node;
	t_bt_elem		bt_elem;
	t_bt_node		*parent;

	FT_LOG_DEBUG("New key: %#lx", *(unsigned long *)bt_key->key);
	ft_bzero(&bt_elem, sizeof(bt_elem));
	if (!(*bt_root))
	{
		bt_node = (t_bt_node *)ft_memalloc(sizeof(*bt_node));
		*bt_root = bt_node;
	}
	ft_memcpy(&bt_elem.bt_data, bt_data, sizeof(bt_elem.bt_data));
	ft_memcpy(&bt_elem.bt_key, bt_key, sizeof(bt_elem.bt_key));
	parent = NULL;
	instert_elem(*bt_root, &parent, &bt_elem);
	if (parent)
		*bt_root = parent;
	return ;
}
