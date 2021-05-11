/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dequeue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 08:53:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/11 15:12:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	*ft_dequeue(t_queue *queue)
{
	void	*data;

	data = NULL;
	if (!*queue->out_stack)
	{
		while (*queue->in_stack)
		{
			data = ft_stack_pop(queue->in_stack);
			ft_stack_push(queue->out_stack, data);
		}
	}
	data = ft_stack_pop(queue->out_stack);
	return (data);
}
