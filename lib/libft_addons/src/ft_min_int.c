/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:28:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 11:00:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_min_int(int nbr1, int nbr2)
{
	int		min;

	if (nbr1 < nbr2)
		min = nbr1;
	else
		min = nbr2;
	return (min);
}
