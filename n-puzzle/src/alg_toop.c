/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_toop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:48:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/06 17:56:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	alg_toop(t_puzzle *puzzle)
{
	stat_set_start_time(puzzle->statistics);
	print_puzzle(1, puzzle->curr_status->tiles_pos_map, puzzle->size);
	print_puzzle(2, puzzle->curr_status->tiles_pos_map, puzzle->size);
	if (puzzle->algorithm == E_TOOP_1)
		alg_toop_1(puzzle);
	else
		FT_LOG_ERROR("Functionality is not implemented for the algorithm. %s",
			"Specify an other algorithm with the param -A");
	return ;
}
