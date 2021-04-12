/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/12 13:49:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	delete_puzzle_status(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
	return ;
}

unsigned long	create_tiles_status_map(t_pos ***pos_table, int puzzle_size)
{
	unsigned long	tiles_status_map;
	int				i;
	int				j;
	int				tile_number;

	tiles_status_map = 0;
	i = -1;
	while (++i < puzzle_size)
	{
		j = -1;
		while (++j < puzzle_size)
		{
			tile_number = ((t_tile *)pos_table[i][j]->tile)->number;
			tiles_status_map |= tile_number << (4 * (i * puzzle_size + j));
		}
	}
	return (tiles_status_map);
}

t_puzzle_status	*create_puzzle_status(t_pos ***pos_table,
					unsigned long tiles_status_map, int depth, t_pos *empty_pos)
{
	t_puzzle_status		*puzzle_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	puzzle_status->empty_pos = empty_pos;
	puzzle_status->tiles_status_map = tiles_status_map;
	puzzle_status->pos_table = pos_table;
	puzzle_status->depth = depth;
	return (puzzle_status);
}

void	add_visited_puzzle_status(t_puzzle_status *puzzle_status,
												t_list **tiles_status_map_lst)
{
	t_list				*new_elem;

	new_elem = ft_lstnew((void *)&puzzle_status, sizeof(*puzzle_status));
	ft_lstadd(tiles_status_map_lst, new_elem);
	return ;
}

int	is_visited_puzzle_status(unsigned long tiles_status_map,
									t_list **tiles_status_map_lst, int depth)
{
	int					is_visited;
	t_list				*elem;
	t_puzzle_status		*puzzle_status;

	is_visited = 0;
	elem = *tiles_status_map_lst;
	while (elem)
	{
		puzzle_status = *(t_puzzle_status **)elem->content;
		if (tiles_status_map == puzzle_status->tiles_status_map)
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
