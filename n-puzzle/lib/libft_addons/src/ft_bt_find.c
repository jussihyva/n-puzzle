/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:52:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/02 11:11:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root)
{
	int				is_found;
	int				recursive;
	t_bt_node		*parent;

	recursive = 2;
	parent = NULL;
	find_elem_index(bt_key, &bt_root, &parent, recursive, &is_found);
	return (is_found);
}
