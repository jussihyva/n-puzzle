/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_instert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/02 12:18:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	save_new_elem(t_bt_node *bt_node, int i, t_bt_elem *new_bt_elem)
{
	t_bt_elem	*bt_elem;
	size_t		move_size;

	bt_elem = &bt_node->bt_elem[i];
	if (i != bt_node->num_of_elems)
	{
		move_size = sizeof(bt_node->bt_elem[i + 1])
			* (bt_node->num_of_elems - i);
		ft_memmove(&bt_node->bt_elem[i + 1], &bt_node->bt_elem[i], move_size);
	}
	if (i)
	{
		if (new_bt_elem->left_child)
			bt_node->bt_elem[i - 1].right_child = new_bt_elem->left_child;
		else
			new_bt_elem->left_child = bt_node->bt_elem[i - 1].right_child;
	}
	if (i < bt_node->num_of_elems)
	{
		if (new_bt_elem->right_child)
			bt_node->bt_elem[i + 1].left_child = new_bt_elem->right_child;
		else
			new_bt_elem->right_child = bt_node->bt_elem[i + 1].left_child;
	}
	ft_memcpy(bt_elem, new_bt_elem, sizeof(*bt_elem));
	if (bt_elem->left_child)
		bt_elem->left_child->parent = bt_node;
	if (bt_elem->right_child)
		bt_elem->right_child->parent = bt_node;
	bt_node->num_of_elems++;
	return ;
}

static int	get_mid_elem_pos(t_bt_node *bt_node)
{
	int		mid;

	mid = bt_node->num_of_elems / 2;
	// if (!(bt_node->num_of_elems % 2) && mid >= i + 1)
	// 	mid--;
	return (mid);
}

static int	search_key_position(t_bt_node *bt_node, t_bt_key *bt_key,
																int *is_found)
{
	int			min;
	int			mid;
	int			max;
	int			cmp_result;
	void		*saved_key;

	*is_found = 0;
	min = -1;
	max = bt_node->num_of_elems;
	while (min + 1 < max && !*is_found)
	{
		mid = (min + max) / 2;
		saved_key = bt_node->bt_elem[mid].bt_key.key;
		cmp_result = ft_memcmp(bt_key->key, saved_key, bt_key->key_size);
		if (cmp_result > 0)
			min = mid;
		else if (cmp_result < 0)
			max = mid;
		else
		{
			max = mid;
			*is_found = 1;
		}
	}
	return (max);
}

static void	split_node(t_bt_node **bt_node, t_bt_node **parent,
															t_bt_key *bt_key)
{
	int			i;
	t_bt_node	*new_node;
	size_t		move_size;
	t_bt_elem	*new_bt_elem;
	int			is_found;
	int			cmp_result;

	i = get_mid_elem_pos(*bt_node);
	if (!*parent)
		*parent = (t_bt_node *)ft_memalloc(sizeof(**parent));
	new_bt_elem = &(*bt_node)->bt_elem[i];
	new_node = (t_bt_node *)ft_memalloc(sizeof(*new_node));
	new_node->parent = (*bt_node)->parent;
	move_size = sizeof(new_node->bt_elem[0])
		* ((*bt_node)->num_of_elems - i - 1);
	ft_memcpy(&new_node->bt_elem[0], &(*bt_node)->bt_elem[i + 1], move_size);
	if (new_node->bt_elem[0].left_child)
		new_node->bt_elem[0].left_child->parent = new_node;
	if (new_node->bt_elem[0].right_child)
		new_node->bt_elem[0].right_child->parent = new_node;
	new_node->num_of_elems = (*bt_node)->num_of_elems - i - 1;
	(*bt_node)->num_of_elems = i;
	new_bt_elem->left_child = *bt_node;
	new_bt_elem->right_child = new_node;
	i = search_key_position(*parent, &new_bt_elem->bt_key,
			&is_found);
	save_new_elem(*parent, i, new_bt_elem);
	cmp_result = ft_memcmp(bt_key->key,
			new_bt_elem->bt_key.key, bt_key->key_size);
	if (cmp_result > 0)
		*bt_node = new_bt_elem->right_child;
	return ;
}

int	find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node, t_bt_node **parent, int recursive,
																int *is_found)
{
	int			i;
	t_bt_node	*bt_child_node;

	if ((*bt_node)->num_of_elems >= MAX_NUM_OF_B_TREE_ELEMS && recursive != 2)
	{
		split_node(bt_node, parent, bt_key);
	}
	i = search_key_position(*bt_node, bt_key, is_found);
	if (!*is_found)
	{
		if (!(*bt_node)->num_of_elems)
			bt_child_node = NULL;
		else if (i == (*bt_node)->num_of_elems)
			bt_child_node = (*bt_node)->bt_elem[i - 1].right_child;
		else
			bt_child_node = (*bt_node)->bt_elem[i].left_child;
		if (bt_child_node)
		{
			i = find_elem_index(bt_key, &bt_child_node, bt_node, recursive,
					is_found);
			*bt_node = bt_child_node;
		}
	}
	return (i);
}

static void	instert_elem(t_bt_node *bt_node, t_bt_node **parent, t_bt_elem *bt_elem, int recursive)
{
	int				i;
	int				is_found;

	i = find_elem_index(&bt_elem->bt_key, &bt_node, parent, recursive, &is_found);
	if (is_found)
		return ;
	save_new_elem(bt_node, i, bt_elem);
	return ;
}

void	ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data, t_bt_node **bt_root)
{
	t_bt_node		*bt_node;
	t_bt_elem		bt_elem;
	int				recursive;
	int				count;
	t_bt_node		*parent;

	FT_LOG_DEBUG("New key: %#lx", *(unsigned long *)bt_key->key);
	recursive = 1;
	ft_bzero(&bt_elem, sizeof(bt_elem));
	if (!(*bt_root))
	{
		bt_node = (t_bt_node *)ft_memalloc(sizeof(*bt_node));
		*bt_root = bt_node;
	}
	ft_memcpy(&bt_elem.bt_data, bt_data, sizeof(bt_elem.bt_data));
	ft_memcpy(&bt_elem.bt_key, bt_key, sizeof(bt_elem.bt_key));
	parent = NULL;
	instert_elem(*bt_root, &parent, &bt_elem, recursive);
	if (parent)
		*bt_root = parent;
	count = 0;
	ft_bt_print(*bt_root, &count);
	return ;
}
