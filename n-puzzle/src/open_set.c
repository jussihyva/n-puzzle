/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 12:45:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 13:08:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

t_puzzle_status	*add_puzzle_state_to_prio_queue(t_puzzle *puzzle)
{
	t_puzzle_status		*next_status;

	if (is_visited_puzzle_status_b_tree(&puzzle->curr_status->tiles_pos_map,
			puzzle, &next_status))
		next_status = NULL;
	else
	{
		next_status = save_current_puzzle_status(puzzle->curr_status);
		ft_prio_enqueue(puzzle->states_prio_queue, &next_status->prio,
			(void *)next_status);
		next_status->is_in_queue = 1;
		store_visited_puzzle_status_b_tree(next_status, puzzle);
	}
	return (next_status);
}

void	add_puzzle_state_to_prio_queue_1(t_puzzle_status *puzzle_state,
												t_bt_node **states_prio_queue)
{
	puzzle_state->is_in_queue = 1;
	ft_prio_enqueue(states_prio_queue, &puzzle_state->prio,
		(void *)puzzle_state);
	return ;
}
