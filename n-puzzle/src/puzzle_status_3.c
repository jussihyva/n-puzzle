/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:09:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 13:08:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	store_visited_puzzle_status_list(t_puzzle_status *puzzle_status,
															t_puzzle *puzzle)
{
	t_list				*new_elem;

	new_elem = ft_lstnew((void **)&puzzle_status, sizeof(puzzle_status));
	ft_lstadd(puzzle->puzzle_status_lst, new_elem);
	puzzle->stat_counters->counter_values[E_TOTAL_NUM_OF_PUZZLE_STATES]++;
	puzzle->stat_counters->counter_values[E_MAX_NUM_OF_SAVED_PUZZLE_STATES]++;
	return ;
}

void	store_visited_puzzle_status_b_tree(t_puzzle_status *puzzle_status,
															t_puzzle *puzzle)
{
	t_bt_key			bt_key;
	t_bt_data			bt_data;

	bt_key.key = (void *)puzzle_status->tiles_pos_map.map;
	bt_key.key_size = puzzle_status->tiles_pos_map.map_size;
	bt_data.data = (void *)puzzle_status;
	bt_data.data_size = sizeof(puzzle_status);
	ft_bt_instert(&bt_key, &bt_data, puzzle->bt_root);
	puzzle->stat_counters->counter_values[E_TOTAL_NUM_OF_PUZZLE_STATES]++;
	puzzle->stat_counters->counter_values[E_MAX_NUM_OF_SAVED_PUZZLE_STATES]++;
	return ;
}

int	is_visited_puzzle_status_list(t_tiles_pos_map *tiles_pos_map,
							t_puzzle *puzzle, t_puzzle_status **puzzle_status)
{
	int					is_visited;
	t_list				*elem;

	*puzzle_status = NULL;
	is_visited = 0;
	elem = *puzzle->puzzle_status_lst;
	while (elem)
	{
		*puzzle_status = *(t_puzzle_status **)elem->content;
		if (!(ft_memcmp(tiles_pos_map->map, (*puzzle_status)->tiles_pos_map.map,
					tiles_pos_map->map_size)))
		{
			is_visited = 1;
			(*puzzle->state_collision_cnt)++;
			break ;
		}
		elem = elem->next;
	}
	return (is_visited);
}

static void	verify_visited_puzzle_status(t_tiles_pos_map *tiles_pos_map,
								t_puzzle *puzzle, int bt_is_visited)
{
	int					is_visited;
	t_puzzle_status		*puzzle_status;

	is_visited = is_visited_puzzle_status_list(tiles_pos_map, puzzle,
			&puzzle_status);
	if (is_visited != bt_is_visited)
	{
		FT_LOG_WARN("Tiles pos map: %lx", tiles_pos_map->map[0]);
		FT_LOG_WARN("Is visited: %d %d", is_visited, bt_is_visited);
	}
	return ;
}

int	is_visited_puzzle_status_b_tree(t_tiles_pos_map *tiles_pos_map,
							t_puzzle *puzzle, t_puzzle_status **puzzle_status)
{
	int					is_visited;
	t_bt_key			bt_key;
	t_bt_data			return_bt_data;

	bt_key.key = (void *)tiles_pos_map->map;
	bt_key.key_size = tiles_pos_map->map_size;
	FT_LOG_TRACE("KEY to find: %#.9lx (%p)",
		*(unsigned long *)bt_key.key, bt_key.key);
	ft_bt_find(&bt_key, *puzzle->bt_root, &return_bt_data);
	*puzzle_status = NULL;
	is_visited = 0;
	if (return_bt_data.data)
	{
		is_visited = 1;
		*puzzle_status = (t_puzzle_status *)return_bt_data.data;
		(*puzzle->state_collision_cnt)++;
	}
	if (1 == 2)
		verify_visited_puzzle_status(tiles_pos_map, puzzle, is_visited);
	return (is_visited);
}
