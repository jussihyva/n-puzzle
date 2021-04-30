/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/30 10:15:52 by jkauppi          ###   ########.fr       */
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

unsigned long	create_tiles_pos_map(int **tile_map, t_pos ***pos_table,
											int puzzle_size, t_pos **empty_pos)
{
	unsigned long	tiles_pos_map;
	int				i;
	int				j;
	unsigned long	tile_number;

	tiles_pos_map = 0;
	i = -1;
	while (++i < puzzle_size)
	{
		j = -1;
		while (++j < puzzle_size)
		{
			tile_number = (unsigned long)tile_map[i][j];
			tiles_pos_map |= tile_number << (4 * (i * puzzle_size + j));
			if (!tile_number)
				*empty_pos = pos_table[i][j];
		}
	}
	return (tiles_pos_map);
}

t_puzzle_status	*create_puzzle_status(unsigned long tiles_pos_map,
						t_puzzle_status *prev_puzzle_status, t_pos *empty_pos,
												unsigned int right_pos_status)
{
	t_puzzle_status		*puzzle_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	puzzle_status->empty_pos = empty_pos;
	puzzle_status->tiles_pos_map = tiles_pos_map;
	puzzle_status->right_pos_status = right_pos_status;
	if (prev_puzzle_status)
	{
		puzzle_status->depth = prev_puzzle_status->depth + 1;
		puzzle_status->prev_status = prev_puzzle_status;
	}
	return (puzzle_status);
}

void	add_visited_puzzle_status(t_puzzle_status *puzzle_status,
															t_puzzle *puzzle)
{
	t_list				*new_elem;
	t_bt_key			bt_key;
	t_bt_data			bt_data;

	new_elem = ft_lstnew((void **)&puzzle_status, sizeof(puzzle_status));
	ft_lstadd(puzzle->puzzle_status_lst, new_elem);
	bt_key.key = (void *)&puzzle_status->tiles_pos_map;
	bt_key.key_size = sizeof(puzzle_status->tiles_pos_map);
	bt_data.data = (void *)puzzle_status;
	bt_data.data_size = sizeof(puzzle_status);
	ft_bt_instert(&bt_key, &bt_data, puzzle->bt_root);
	(*puzzle->states_cnt)++;
	return ;
}

int	is_visited_puzzle_status(unsigned long tiles_pos_map,
										t_list **puzzle_status_lst, int depth)
{
	int					is_visited;
	t_list				*elem;
	t_puzzle_status		*puzzle_status;

	is_visited = 0;
	elem = *puzzle_status_lst;
	while (elem)
	{
		puzzle_status = *(t_puzzle_status **)elem->content;
		if (tiles_pos_map == puzzle_status->tiles_pos_map)
		{
			is_visited = 1;
			if (puzzle_status->depth > depth)
			{
				puzzle_status->depth = depth;
				is_visited = 0;
			}
			break ;
		}
		elem = elem->next;
	}
	return (is_visited);
}
