/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_instert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 10:23:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/16 12:46:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static int	find_elem_index(t_bt_key *bt_key, t_bt_node *bt_node)
{
	int		i;
	int		min;
	int		mid;
	int		max;
	void	*saved_key;
	int		cmp_result;

	min = -1;
	max = bt_node->num_of_elems;
	i = 0;
	while (min + 1 < max)
	{
		mid = (min + max) / 2;
		saved_key = bt_node->bt_elem[mid].bt_key.key;
		cmp_result = ft_memcmp(saved_key, bt_key->key, bt_key->key_size);
		if (cmp_result > 0)
		{
			max = mid;
		}
		else if (cmp_result < 0)
		{
			min = mid;
		}
		else
			FT_LOG_ERROR("New key value is already saved into B-tree!");
	}
	return (i);
}

static void	instert_elem(t_bt_node *bt_node, t_bt_key *bt_key,
															t_bt_data *bt_data)
{
	int				i;
	t_bt_elem		*bt_elem;
	size_t			move_size;

	i = find_elem_index(bt_key, bt_node);
	if (i)
	{
		move_size
			= sizeof(bt_node->bt_elem[i + 1]) * (bt_node->num_of_elems - i);
		ft_memmove(&bt_node->bt_elem[i + 1], &bt_node->bt_elem[i], move_size);
	}
	bt_elem = (t_bt_elem *)ft_memalloc(sizeof(*bt_elem));
	bt_node->bt_elem[i].bt_data.data = bt_data->data;
	bt_node->bt_elem[i].bt_data.data_size = bt_data->data_size;
	bt_node->bt_elem[i].bt_key.key = bt_key->key;
	bt_node->bt_elem[i].bt_key.key_size = bt_key->key_size;
	bt_node->num_of_elems++;
	return ;
}

void	ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data, t_bt_node **bt_root)
{
	t_bt_node		*bt_node;

	if (*bt_root)
		;
	else
	{
		bt_node = (t_bt_node *)ft_memalloc(sizeof(*bt_node));
		*bt_root = bt_node;
		instert_elem(*bt_root, bt_key, bt_data);
	}
	return ;
}
