/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:50:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 11:00:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

double	ft_max_double(double nbr1, double nbr2)
{
	double		max;

	if (nbr1 > nbr2)
		max = nbr1;
	else
		max = nbr2;
	return (max);
}
