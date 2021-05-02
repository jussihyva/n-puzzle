/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bt_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 13:52:53 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/02 16:58:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	*ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root)
{
	void				*bt_data;

	find_elem_index(bt_key, &bt_root, &bt_data);
	return (bt_data);
}
