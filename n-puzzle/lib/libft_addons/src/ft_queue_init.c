/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:46:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/28 18:51:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

t_queue	*ft_queue_init(void)
{
	t_queue		*queue;

	queue = (t_queue *)ft_memalloc(sizeof(*queue));
	queue->in_stack = (t_list **)ft_memalloc(sizeof(*queue->in_stack));
	queue->out_stack = (t_list **)ft_memalloc(sizeof(*queue->out_stack));
	return (queue);
}
