/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:17:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/30 14:14:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_bt_print(t_bt_node *bt_node, int *count)
{
	t_bt_elem	*bt_elem;
	t_bt_node	*bt_child_node;
	int			i;

	i = -1;
	while (++i < bt_node->num_of_elems)
	{
		bt_elem = &bt_node->bt_elem[i];
		bt_child_node = bt_elem->left_child;
		if (bt_child_node)
			ft_bt_print(bt_child_node, count);
		(*count)++;
		FT_LOG_TRACE("KEY %03d: %#.9lx (%p)", *count,
			*(unsigned long *)bt_elem->bt_key.key,
			bt_elem->bt_key.key);
		bt_child_node = bt_elem->right_child;
		if (bt_child_node && i == bt_node->num_of_elems - 1)
			ft_bt_print(bt_child_node, count);
	}
	return ;
}
