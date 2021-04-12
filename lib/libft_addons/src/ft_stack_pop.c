/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 10:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/12 12:08:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	*ft_stack_pop(t_list **stack)
{
	void	*data;

	data = NULL;
	if (*stack)
	{
		data = (*stack)->content;
		*stack = (*stack)->next;
	}
	return (data);
}
