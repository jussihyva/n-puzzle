/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_queue_empty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 11:15:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/12 11:18:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_is_queue_empty(t_queue *queue)
{
	int		is_queue_empty;

	is_queue_empty = 0;
	if (!*queue->in_stack && !*queue->out_stack)
		is_queue_empty = 1;
	return (is_queue_empty);
}
