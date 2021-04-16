/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_instert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/16 15:03:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

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

static int	find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node)
{
	int		min;
	int		mid;
	int		max;
	int		cmp_result;

	min = -1;
	max = (*bt_node)->num_of_elems;
	mid = max;
	while (min + 1 < max)
	{
		cmp_result = update_min_max_values(*bt_node, bt_key, &min, &max);
		if (!cmp_result)
			FT_LOG_ERROR("New key value is already saved into B-tree!");
	}
	mid = (min + max) / 2;
	return (mid);
}

static void	instert_elem(t_bt_node **bt_node, t_bt_key *bt_key,
															t_bt_data *bt_data)
{
	int				i;
	t_bt_elem		*bt_elem;
	size_t			move_size;

	i = find_elem_index(bt_key, bt_node);
	if (i != (*bt_node)->num_of_elems)
	{
		move_size = sizeof((*bt_node)->bt_elem[i + 1])
			* ((*bt_node)->num_of_elems - i);
		ft_memmove(&(*bt_node)->bt_elem[i + 1], &(*bt_node)->bt_elem[i],
			move_size);
	}
	bt_elem = (t_bt_elem *)ft_memalloc(sizeof(*bt_elem));
	(*bt_node)->bt_elem[i].bt_data.data = bt_data->data;
	(*bt_node)->bt_elem[i].bt_data.data_size = bt_data->data_size;
	(*bt_node)->bt_elem[i].bt_key.key = bt_key->key;
	(*bt_node)->bt_elem[i].bt_key.key_size = bt_key->key_size;
	(*bt_node)->num_of_elems++;
	return ;
}

void	ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data, t_bt_node **bt_root)
{
	t_bt_node		*bt_node;

	if (!(*bt_root))
	{
		bt_node = (t_bt_node *)ft_memalloc(sizeof(*bt_node));
		*bt_root = bt_node;
	}
	instert_elem(bt_root, bt_key, bt_data);
	return ;
}
