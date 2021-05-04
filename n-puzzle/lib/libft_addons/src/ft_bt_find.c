/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:52:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/04 15:18:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root, t_bt_data *return_bt_data)
{
	return_bt_data->data = NULL;
	if (bt_root)
		find_elem_index(bt_key, &bt_root, return_bt_data);
	return ;
}
