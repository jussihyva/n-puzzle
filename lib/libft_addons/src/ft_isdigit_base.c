/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 05:53:26 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 10:53:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_isdigit_base(int c, int base)
{
	int		result;

	errno = 0;
	result = 0;
	if (base <= 10)
	{
		if ((c >= '0') && (c < '0' + base))
			result = 1;
	}
	else
	{
		if (((c >= '0') && (c < '0' + base))
			|| ((c >= 'A') && (c < 'A' + base))
			|| ((c >= 'a') && (c < 'a' + base)))
			result = 1;
	}
	return (result);
}
