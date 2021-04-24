/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_instert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/24 11:13:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	instert_elem(t_bt_node *bt_node, t_bt_elem *bt_elem, int recursive);

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
	ft_memcpy(bt_elem, new_bt_elem, sizeof(*bt_elem));
	if (i && new_bt_elem->left_child)
		bt_node->bt_elem[i - 1].right_child = new_bt_elem->left_child;
	if (i < (bt_node->num_of_elems) && new_bt_elem->right_child)
		bt_node->bt_elem[i + 1].left_child = new_bt_elem->right_child;
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

static int	update_min_max_values(t_bt_node *bt_node, t_bt_key *bt_key,
															int *min, int *max)
{
	int		cmp_result;
	void	*saved_key;
	int		is_found;
	int		mid;

	is_found = 0;
	mid = (*min + *max) / 2;
	saved_key = bt_node->bt_elem[mid].bt_key.key;
	cmp_result = ft_memcmp(bt_key->key, saved_key, bt_key->key_size);
	if (cmp_result > 0)
		*min = mid;
	else if (cmp_result < 0)
		*max = mid;
	else
		is_found = 1;
	return (is_found);
}

static void	split_node(t_bt_node **bt_node, int *i, t_bt_elem *parent_elem)
{
	int			mid;
	t_bt_node	*new_node;
	size_t		move_size;

	mid = get_mid_elem_pos(*bt_node);
	if (!((*bt_node)->num_of_elems % 2) && mid >= *i + 1)
		mid--;
	new_node = (t_bt_node *)ft_memalloc(sizeof(*new_node));
	new_node->parent = (*bt_node)->parent;
	move_size = sizeof(new_node->bt_elem[0])
		* ((*bt_node)->num_of_elems - mid - 1);
	ft_memcpy(&new_node->bt_elem[0], &(*bt_node)->bt_elem[mid + 1], move_size);
	new_node->num_of_elems = (*bt_node)->num_of_elems - mid - 1;
	(*bt_node)->num_of_elems = mid;
	parent_elem->left_child = *bt_node;
	parent_elem->right_child = new_node;
	if (*i >= mid)
	{
		*i = new_node->num_of_elems;
		*bt_node = new_node;
	}
	return ;
}

static int	find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node,
												int recursive, int *is_found)
{
	int			min;
	int			mid;
	int			max;
	t_bt_node	*bt_child_node;
	t_bt_elem	*parent_new_bt_elem;

	if ((*bt_node)->num_of_elems >= MAX_NUM_OF_B_TREE_ELEMS)
	{
		mid = get_mid_elem_pos(*bt_node);
		if (!(*bt_node)->parent)
			(*bt_node)->parent
				= (t_bt_node *)ft_memalloc(sizeof(*(*bt_node)->parent));
		parent_new_bt_elem = &(*bt_node)->bt_elem[mid];
		split_node(bt_node, &mid, parent_new_bt_elem);
		instert_elem((*bt_node)->parent, parent_new_bt_elem, 0);
		*bt_node = (*bt_node)->parent;
	}
	*is_found = 0;
	min = -1;
	max = (*bt_node)->num_of_elems;
	while (min + 1 < max && !*is_found)
		*is_found = update_min_max_values(*bt_node, bt_key, &min, &max);
	if (!(*bt_node)->num_of_elems || max == MAX_NUM_OF_B_TREE_ELEMS)
		bt_child_node = NULL;
	else if (max == (*bt_node)->num_of_elems)
		bt_child_node = (*bt_node)->bt_elem[max - 1].right_child;
	else
		bt_child_node = (*bt_node)->bt_elem[max].left_child;
	if (recursive && bt_child_node)
	{
		*bt_node = bt_child_node;
		max = find_elem_index(bt_key, bt_node, recursive, is_found);
	}
	return (max);
}

static void	instert_elem(t_bt_node *bt_node, t_bt_elem *bt_elem, int recursive)
{
	int				i;
	int				is_found;

	i = find_elem_index(&bt_elem->bt_key, &bt_node, recursive, &is_found);
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
	instert_elem(*bt_root, &bt_elem, recursive);
	if ((*bt_root)->parent)
		*bt_root = (*bt_root)->parent;
	count = 0;
	ft_bt_print(*bt_root, &count);
	return ;
}
