/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 00:42:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 11:09:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_mod_int(int dividend, int divisor)
{
	int		remainder;
	int		t_divisor;

	remainder = dividend;
	if (divisor < 0)
		t_divisor = -divisor;
	else
		t_divisor = divisor;
	if (remainder < 0)
	{
		while (remainder < 0)
			remainder += t_divisor;
	}
	else
	{
		while (remainder >= t_divisor)
			remainder -= t_divisor;
	}
	if (divisor < 0)
		remainder = -remainder;
	return (remainder);
}
