/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statistics_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:08:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/28 18:09:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	release_statistics_params(t_statistics *statistics)
{
	if (statistics)
	{
		ft_strdel(&statistics->algorithm);
		ft_strdel(&statistics->algorithm_substring);
		ft_memdel((void **)&statistics);
	}
	return ;
}
