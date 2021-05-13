/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prio_enqueue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 08:05:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/13 08:04:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_prio_enqueue(t_bt_node **states_prio_queue, int *prio,
														void *puzzle_status)
{
	t_bt_key			bt_key;
	t_bt_data			bt_data;

	bt_key.key = (void *)prio;
	bt_key.key_size = sizeof(*prio);
	bt_data.data = (void *)puzzle_status;
	bt_data.data_size = sizeof(*puzzle_status);
	ft_bt_instert(&bt_key, &bt_data, states_prio_queue);
	return ;
}
