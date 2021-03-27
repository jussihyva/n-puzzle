/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 08:15:12 by juhani            #+#    #+#             */
/*   Updated: 2021/03/27 11:00:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_max_int(int nbr1, int nbr2)
{
	int		max;

	if (nbr1 > nbr2)
		max = nbr1;
	else
		max = nbr2;
	return (max);
}
