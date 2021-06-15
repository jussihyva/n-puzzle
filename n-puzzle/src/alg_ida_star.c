/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_ida_star.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 12:37:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/15 12:27:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	ida_star_search_algorithm(t_puzzle *puzzle,
				t_puzzle_status *puzzle_status, int g_h_cost,
				int *is_puzzle_ready);

static int	is_state_in_path(t_puzzle_status *puzzle_status, t_puzzle *puzzle)
{
	t_list		*elem;
	int			found;

	found = 0;
	elem = puzzle->states_stack;
	while (elem)
	{
		if (!(ft_memcmp(puzzle_status->tiles_pos_map.map,
					(*(t_puzzle_status **)elem->content)->tiles_pos_map.map,
					puzzle_status->tiles_pos_map.map_size)))
		{
			found = 1;
			(*puzzle->state_collision_cnt)++;
			break ;
		}
		elem = elem->next;
	}
	return (found);
}

static int	analyze_puzzle_state(t_puzzle *puzzle,
		t_puzzle_status *puzzle_state, int g_h_cost, int *new_g_h_cost_limit)
{
	int			is_puzzle_ready;
	int			received_g_h_cost_limit;

	is_puzzle_ready = 0;
	puzzle_state->prio = puzzle_state->depth
		+ calculate_heuristic_distance(puzzle_state, puzzle);
	if (puzzle_state->tiles_in_right_pos == puzzle->num_of_tile_pos)
		is_puzzle_ready = print_solution(puzzle_state, puzzle);
	else
	{
		if (!is_state_in_path(puzzle_state, puzzle))
		{
			ft_stack_push(&puzzle->states_stack, puzzle_state);
			(*puzzle->states_cnt)++;
			received_g_h_cost_limit = puzzle_state->prio;
			if (g_h_cost >= puzzle_state->prio)
				received_g_h_cost_limit = ida_star_search_algorithm(
						puzzle, puzzle_state, g_h_cost, &is_puzzle_ready);
			*new_g_h_cost_limit = ft_min_int(received_g_h_cost_limit,
					*new_g_h_cost_limit);
			ft_stack_pop(&puzzle->states_stack);
		}
	}
	return (is_puzzle_ready);
}

static int	ida_star_search_algorithm(t_puzzle *puzzle,
			t_puzzle_status *puzzle_status, int g_h_cost, int *is_puzzle_ready)
{
	t_puzzle_status		*available_puzzle_state;
	int					search_pos_index;
	int					new_g_h_cost_limit;

	search_pos_index = 0;
	new_g_h_cost_limit = INT_MAX;
	available_puzzle_state = puzzle_status;
	while (available_puzzle_state && !*is_puzzle_ready
		&& !check_is_limit_reached(puzzle->stat_counters->counter_values))
	{
		available_puzzle_state = alg_n_puzzle_search_state(puzzle,
				puzzle_status, &search_pos_index);
		if (available_puzzle_state)
		{
			*is_puzzle_ready = analyze_puzzle_state(puzzle,
					available_puzzle_state, g_h_cost, &new_g_h_cost_limit);
			delete_puzzle_status((void *)available_puzzle_state, 0);
		}
	}
	return (new_g_h_cost_limit);
}

int	check_is_limit_reached(int *counter_values)
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
