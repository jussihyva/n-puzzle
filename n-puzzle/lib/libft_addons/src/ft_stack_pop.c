/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 10:34:08 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/11 15:20:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	*ft_stack_pop(t_list **stack)
{
	void	*data;
	t_list	*old_elem;

	data = NULL;
	if (*stack)
	{
		data = *(void **)((*stack)->content);
		old_elem = *stack;
		*stack = (*stack)->next;
		ft_memdel((void **)&old_elem->content);
		ft_memdel((void **)&old_elem);
	}
	return (data);
}
