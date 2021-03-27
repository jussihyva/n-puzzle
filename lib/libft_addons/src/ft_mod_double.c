/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:11:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/22 15:58:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

double		ft_mod_double(double dividend, double divisor)
{
	double		remainder;

	remainder = dividend < 0 ? -dividend : dividend;
	divisor = divisor < 0 ? -divisor : divisor;
	while (remainder >= divisor)
		remainder -= divisor;
	if (dividend < 0)
		remainder = -remainder;
	return (remainder);
}
