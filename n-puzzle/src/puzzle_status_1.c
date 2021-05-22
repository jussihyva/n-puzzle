/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/22 10:37:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	update_tiles_pos_map(t_pos *pos1, t_pos *pos2, int puzzle_size,
												unsigned long *tiles_pos_map)
{
	unsigned long	tile_number1;
	unsigned long	tile_number2;

	tile_number1 = (*tiles_pos_map >> (4 * (pos1->xy_pos.y
					* puzzle_size + pos1->xy_pos.x))) & 0xF;
	tile_number2 = (*tiles_pos_map >> (4 * (pos2->xy_pos.y
					* puzzle_size + pos2->xy_pos.x))) & 0xF;
	*tiles_pos_map &= ~((unsigned long)0xF << (4 * (pos1->xy_pos.y
					* puzzle_size + pos1->xy_pos.x)));
	*tiles_pos_map &= ~((unsigned long)0xF << (4 * (pos2->xy_pos.y
					* puzzle_size + pos2->xy_pos.x)));
	*tiles_pos_map |= tile_number1 << (4 * (pos2->xy_pos.y
				* puzzle_size + pos2->xy_pos.x));
	*tiles_pos_map |= tile_number2 << (4 * (pos1->xy_pos.y
				* puzzle_size + pos1->xy_pos.x));
	return ;
}

static unsigned long	create_tiles_pos_map(int **tile_map, t_pos ***pos_table,
											int puzzle_size, t_pos **empty_pos)
{
	unsigned long	tiles_pos_map;
	int				i;
	int				j;
	unsigned long	tile_number;
	int				shift;

	tiles_pos_map = 0;
	i = -1;
	while (++i < puzzle_size)
	{
		j = -1;
		while (++j < puzzle_size)
		{
			tile_number = (unsigned long)tile_map[i][j];
			shift = 4 * (i * puzzle_size + j);
			tiles_pos_map |= tile_number << shift;
			if (!tile_number)
				*empty_pos = pos_table[i][j];
		}
	}
	return (tiles_pos_map);
}

t_puzzle_status	*save_current_puzzle_status(t_puzzle_status *curr_status)
{
	t_puzzle_status		*puzzle_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	ft_memcpy(puzzle_status, curr_status, sizeof(*puzzle_status));
	return (puzzle_status);
}

static unsigned int	set_right_pos_status(t_pos ***pos_table, int puzzle_size,
													unsigned long tiles_pos_map)
{
	unsigned int	right_pos_status;
	int				i;
	int				j;
	t_pos			*pos;
	int				tile_number;

	right_pos_status = 0;
	i = -1;
	while (++i < puzzle_size)
	{
		j = -1;
		while (++j < puzzle_size)
		{
			pos = pos_table[i][j];
			tile_number = (tiles_pos_map >> (4 * (i * puzzle_size + j))) & 0xF;
			if (tile_number == pos->right_tile_number)
				right_pos_status |= 1 << pos->right_tile_number;
		}
	}
	FT_LOG_TRACE("Right position status: %u", right_pos_status);
	return (right_pos_status);
}

t_puzzle_status	*create_puzzle_status(int **tile_map, t_pos ***pos_table,
																int puzzle_size)
{
	t_puzzle_status		*puzzle_status;
	t_pos				*empty_pos;
	unsigned long		tiles_pos_map;
	unsigned int		right_pos_status;

	tiles_pos_map = create_tiles_pos_map(tile_map,
			pos_table, puzzle_size, &empty_pos);
	right_pos_status = set_right_pos_status(pos_table, puzzle_size,
			tiles_pos_map);
	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	puzzle_status->empty_pos = empty_pos;
	puzzle_status->tiles_pos_map = tiles_pos_map;
	puzzle_status->right_pos_status = right_pos_status;
	return (puzzle_status);
}

void	store_visited_puzzle_status_list(t_puzzle_status *puzzle_status,
															t_puzzle *puzzle)
{
	t_list				*new_elem;

	new_elem = ft_lstnew((void **)&puzzle_status, sizeof(puzzle_status));
	ft_lstadd(puzzle->puzzle_status_lst, new_elem);
	(*puzzle->states_cnt)++;
	return ;
}

void	store_visited_puzzle_status_b_tree(t_puzzle_status *puzzle_status,
															t_bt_node **bt_root)
{
	t_bt_key			bt_key;
	t_bt_data			bt_data;

	bt_key.key = (void *)&puzzle_status->tiles_pos_map;
	bt_key.key_size = sizeof(puzzle_status->tiles_pos_map);
	bt_data.data = (void *)puzzle_status;
	bt_data.data_size = sizeof(puzzle_status);
	ft_bt_instert(&bt_key, &bt_data, bt_root);
	return ;
}

int	is_visited_puzzle_status_list(unsigned long tiles_pos_map, t_puzzle *puzzle,
												t_puzzle_status **puzzle_status)
{
	int					is_visited;
	t_list				*elem;

	*puzzle_status = NULL;
	is_visited = 0;
	elem = *puzzle->puzzle_status_lst;
	while (elem)
	{
		*puzzle_status = *(t_puzzle_status **)elem->content;
		if (tiles_pos_map == (*puzzle_status)->tiles_pos_map)
		{
			is_visited = 1;
			(*puzzle->state_collision_cnt)++;
			break ;
		}
		elem = elem->next;
	}
	return (is_visited);
}

static void	verify_visited_puzzle_status(unsigned long tiles_pos_map,
								t_puzzle *puzzle, int bt_is_visited)
{
	int					is_visited;
	t_puzzle_status		*puzzle_status;

	is_visited = is_visited_puzzle_status_list(tiles_pos_map, puzzle,
			&puzzle_status);
	if (is_visited != bt_is_visited)
	{
		FT_LOG_WARN("Tiles pos map: %lx", tiles_pos_map);
		FT_LOG_WARN("Is visited: %d %d", is_visited, bt_is_visited);
	}
	return ;
}

int	is_visited_puzzle_status_b_tree(unsigned long tiles_pos_map,
							t_puzzle *puzzle, t_puzzle_status **puzzle_status)
{
	int					is_visited;
	t_bt_key			bt_key;
	t_bt_data			return_bt_data;

	bt_key.key = (void *)&tiles_pos_map;
	bt_key.key_size = sizeof(tiles_pos_map);
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
