/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:12:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/28 18:12:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	delete_puzzle_status(void *content, size_t size)
{
	t_puzzle_status		*puzzle_status;

	(void)size;
	puzzle_status = *(t_puzzle_status **)content;
	ft_memdel((void **)&puzzle_status);
	ft_memdel((void **)&content);
	return ;
}
