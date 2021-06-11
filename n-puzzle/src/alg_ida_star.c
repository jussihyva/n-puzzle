/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_ida_star.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 12:37:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/11 08:11:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	is_state_in_path(t_puzzle_status *puzzle_status,
														t_list **states_stack)
{
	t_list		*elem;
	int			found;

	found = 0;
	elem = *states_stack;
	while (elem)
	{
		if (!(ft_memcmp(puzzle_status->tiles_pos_map.map,
					(*(t_puzzle_status **)elem->content)->tiles_pos_map.map,
					puzzle_status->tiles_pos_map.map_size)))
		{
			found = 1;
			break ;
		}
		elem = elem->next;
	}
	return (found);
}

static int	ida_star_search_algorithm(t_puzzle *puzzle,
			t_puzzle_status *puzzle_status, int g_h_cost, int *is_puzzle_ready)
{
	t_puzzle_status		*available_puzzle_state;
	int					search_pos_index;
	int					new_g_h_cost_limit;
	int					received_g_h_cost_limit;

	*is_puzzle_ready = 0;
	if (g_h_cost >= puzzle_status->prio)
	{
		search_pos_index = 0;
		available_puzzle_state = alg_n_puzzle_search_state(puzzle,
				puzzle_status, &search_pos_index);
		new_g_h_cost_limit = INT_MAX;
		while (available_puzzle_state && !*is_puzzle_ready)
		{
			available_puzzle_state->prio = available_puzzle_state->depth
				+ calculate_heuristic_distance(available_puzzle_state, puzzle);
			if (available_puzzle_state->tiles_in_right_pos
				== puzzle->num_of_tile_pos)
			{
				*is_puzzle_ready
					= print_solution(available_puzzle_state, puzzle);
				delete_puzzle_status((void *)available_puzzle_state, 0);
			}
			else
			{
				if (is_state_in_path(available_puzzle_state,
						&puzzle->states_stack))
					(*puzzle->state_collision_cnt)++;
				else
				{
					ft_stack_push(&puzzle->states_stack,
						(void *)available_puzzle_state);
					(*puzzle->states_cnt)++;
					received_g_h_cost_limit = ida_star_search_algorithm(puzzle,
							available_puzzle_state, g_h_cost, is_puzzle_ready);
					new_g_h_cost_limit = ft_min_int(received_g_h_cost_limit,
							new_g_h_cost_limit);
					ft_stack_pop(&puzzle->states_stack);
				}
				delete_puzzle_status((void *)available_puzzle_state, 0);
				available_puzzle_state = alg_n_puzzle_search_state(puzzle,
						puzzle_status, &search_pos_index);
			}
		}
	}
	else
		new_g_h_cost_limit = puzzle_status->prio;
	return (new_g_h_cost_limit);
}

static int	check_is_limit_reached(int *counter_values)
{
	int		is_limit_reached;

	is_limit_reached = 0;
	if (counter_values[E_IS_MEM_LIMIT_REACHED]
		|| counter_values[E_IS_TIME_LIMIT_REACHED])
		is_limit_reached = 1;
	return (is_limit_reached);
}

void	alg_ida_star(t_puzzle *puzzle)
{
	int					is_puzzle_ready;
	t_puzzle_status		*puzzle_status;
	int					g_h_cost_limit;
	int					new_g_h_cost_limit;

	is_puzzle_ready = 0;
	if (puzzle->curr_status->tiles_in_right_pos == puzzle->num_of_tile_pos)
		is_puzzle_ready = 1;
	puzzle_status = save_current_puzzle_status(puzzle->curr_status);
	g_h_cost_limit = puzzle_status->depth + calculate_taxicab_distance(
			&puzzle_status->tiles_pos_map, puzzle->size,
			puzzle->tile_right_pos_array);
	puzzle_status->prio = g_h_cost_limit;
	ft_stack_push(&puzzle->states_stack, (void *)puzzle_status);
	(*puzzle->states_cnt)++;
	while (!is_puzzle_ready
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		update_current_puzzle_state(puzzle->curr_status, puzzle_status);
		new_g_h_cost_limit = ida_star_search_algorithm(puzzle, puzzle_status,
				g_h_cost_limit, &is_puzzle_ready);
		print_depth_level(puzzle->curr_status->depth);
		g_h_cost_limit = new_g_h_cost_limit;
	}
	ft_stack_pop(&puzzle->states_stack);
	delete_puzzle_status((void *)puzzle_status, 0);
	return ;
}
