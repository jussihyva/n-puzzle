/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_radian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 08:08:39 by juhani            #+#    #+#             */
/*   Updated: 2021/03/27 11:00:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

double	ft_radian(double angle_degree)
{
	double	angle_rad;

	angle_rad = angle_degree * PI / 180;
	return (angle_rad);
}
