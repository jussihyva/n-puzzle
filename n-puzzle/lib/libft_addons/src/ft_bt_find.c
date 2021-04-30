/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:52:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/30 14:47:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root)
{
	int				is_found;
	int				recursive;

	recursive = 2;
	find_elem_index(bt_key, &bt_root, recursive, &is_found);
	return (is_found);
}
