/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:25:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/01 20:46:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_bt_remove(t_bt_node **bt_node, t_bt_key *bt_key)
{
	t_bt_elem	*bt_elem;
	t_bt_node	*bt_child_node;
	int			i;

	i = -1;
	while (*bt_node && ++i < (*bt_node)->num_of_elems)
	{
		bt_elem = &(*bt_node)->bt_elem[i];
		bt_child_node = bt_elem->left_child;
		if (bt_child_node)
			ft_bt_remove(&bt_child_node, bt_key);
		bt_child_node = bt_elem->right_child;
		if (bt_child_node && i == (*bt_node)->num_of_elems - 1)
			ft_bt_remove(&bt_child_node, bt_key);
	}
	if (!bt_key)
		ft_memdel((void **)bt_node);
	return ;
}
