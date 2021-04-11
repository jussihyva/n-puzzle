/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/11 03:59:02 by jkauppi          ###   ########.fr       */
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
									unsigned long tiles_status_map, int depth)
{
	t_puzzle_status		*puzzle_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	puzzle_status->tiles_status_map = tiles_status_map;
	puzzle_status->pos_table = pos_table;
	puzzle_status->depth = depth;
	return (puzzle_status);
}

void	add_visited_puzzle_status(t_puzzle_status *puzzle_status,
											t_list **visited_puzzle_statuses)
{
	t_list				*new_elem;

	new_elem = ft_lstnew((void *)&puzzle_status, sizeof(*puzzle_status));
	ft_lstadd(visited_puzzle_statuses, new_elem);
	return ;
}

int	is_visited_puzzle_status(unsigned long tiles_status_map,
									t_list **visited_puzzle_statuses, int depth)
{
	int					is_visited;
	t_list				*elem;
	t_puzzle_status		*puzzle_status;

	is_visited = 0;
	elem = *visited_puzzle_statuses;
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
