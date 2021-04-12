/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 10:34:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/12 12:36:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_stack_push(t_list **stack, void *data)
{
	t_list		*new_elem;

	new_elem = ft_lstnew(data, sizeof(data));
	ft_lstadd(stack, new_elem);
	return ;
}
