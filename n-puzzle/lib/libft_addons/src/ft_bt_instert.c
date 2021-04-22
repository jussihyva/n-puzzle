/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_instert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/22 20:12:35 by jkauppi          ###   ########.fr       */
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
	bt_node->num_of_elems++;
	ft_memcpy(bt_elem, new_bt_elem, sizeof(*bt_elem));
	return ;
}

static int	get_mid_elem_pos(t_bt_node *bt_node, int i)
{
	int		mid;

	mid = bt_node->num_of_elems / 2 - 1;
	if (i > mid && mid * 2 < bt_node->num_of_elems)
		mid++;
	return (mid);
}

static int	update_min_max_values(t_bt_node *bt_node, t_bt_key *bt_key,
															int *min, int *max)
{
	int		cmp_result;
	void	*saved_key;
	int		mid;

	mid = (*min + *max) / 2;
	saved_key = bt_node->bt_elem[mid].bt_key.key;
	cmp_result = ft_memcmp(saved_key, bt_key->key, bt_key->key_size);
	if (cmp_result > 0)
	{
		*max = mid;
	}
	else if (cmp_result < 0)
	{
		*min = mid;
	}
	return (cmp_result);
}

static int	find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node,
																int *is_found)
{
	int		min;
	int		mid;
	int		max;
	int		cmp_result;

	*is_found = 0;
	min = -1;
	max = (*bt_node)->num_of_elems;
	mid = max;
	while (min + 1 < max && !*is_found)
	{
		cmp_result = update_min_max_values(*bt_node, bt_key, &min, &max);
		if (!cmp_result)
			*is_found = 1;
	}
	mid = (min + max) / 2;
	if ((*bt_node)->bt_elem[mid].left_child)
	{
		*bt_node = (*bt_node)->bt_elem[mid].left_child;
		mid = find_elem_index(bt_key, bt_node, is_found);
	}
	return (mid);
}

static void	split_node(t_bt_node **bt_node, int *i, t_bt_elem *parent_elem)
{
	int			mid;
	t_bt_node	*new_node;

	mid = get_mid_elem_pos(*bt_node, *i);
	new_node = (t_bt_node *)ft_memalloc(sizeof(*new_node));
	new_node->parent = (*bt_node)->parent;
	ft_memcpy(new_node->bt_elem, &(*bt_node)->bt_elem[mid],
		sizeof(new_node->bt_elem[0]) * ((*bt_node)->num_of_elems - mid - 1));
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

static void	instert_elem(t_bt_node *bt_node, t_bt_elem *bt_elem)
{
	int				i;
	int				is_found;
	int				mid;
	t_bt_elem		*parent_new_bt_elem;

	i = find_elem_index(&bt_elem->bt_key, &bt_node, &is_found);
	if (is_found)
		return ;
	if (bt_node->num_of_elems >= MAX_NUM_OF_B_TREE_ELEMS)
	{
		mid = get_mid_elem_pos(bt_node, i);
		if (!bt_node->parent)
			bt_node->parent = (t_bt_node *)ft_memalloc(sizeof(*bt_node->parent));
		parent_new_bt_elem = &bt_node->bt_elem[mid];
		split_node(&bt_node, &i, parent_new_bt_elem);
		instert_elem(bt_node->parent, parent_new_bt_elem);
	}
	save_new_elem(bt_node, i, bt_elem);
	return ;
}

void	ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data, t_bt_node **bt_root)
{
	t_bt_node		*bt_node;
	t_bt_node		*parent;
	t_bt_elem		bt_elem;

	ft_bzero(&bt_elem, sizeof(bt_elem));
	if (!(*bt_root))
	{
		bt_node = (t_bt_node *)ft_memalloc(sizeof(*bt_node));
		*bt_root = bt_node;
	}
	parent = NULL;
	ft_memcpy(&bt_elem.bt_data, bt_data, sizeof(bt_elem.bt_data));
	ft_memcpy(&bt_elem.bt_key, bt_key, sizeof(bt_elem.bt_key));
	instert_elem(*bt_root, &bt_elem);
	if (parent)
		*bt_root = parent;
	return ;
}
