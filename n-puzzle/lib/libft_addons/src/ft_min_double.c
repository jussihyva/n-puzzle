/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:50:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 11:00:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

double	ft_min_double(double nbr1, double nbr2)
{
	double		min;

	if (nbr1 < nbr2)
		min = nbr1;
	else
		min = nbr2;
	return (min);
}
