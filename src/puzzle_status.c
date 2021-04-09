/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/09 14:48:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	delete_puzzle_status(void *content, size_t size)
{
	(void)size;
	ft_memdel(&content);
	return ;
}

unsigned long	create_puzzle_status(t_puzzle *puzzle)
{
	unsigned long	puzzle_status;
	t_tile			**tile_array;
	int				i;
	int				j;

	tile_array = puzzle->tile_array;
	puzzle_status = 0;
	i = -1;
	while (++i < puzzle->size)
	{
		j = -1;
		while (++j < puzzle->size)
		{
			puzzle_status |= ((t_tile *)puzzle->pos_table[i][j]->tile)->number
				<< (4 * (i * puzzle->size + j));
		}
	}
	return (puzzle_status);
}

static void	add_puzzle_status(unsigned long tiles_status_map, int depth,
											t_list **visited_puzzle_statuses)
{
	t_list				*new_elem;
	t_puzzle_status		*puzzle_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	puzzle_status->tiles_status_map = tiles_status_map;
	puzzle_status->visibility_depth = depth;
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
			if (puzzle_status->visibility_depth > depth)
			{
				puzzle_status->visibility_depth = depth;
				is_visited = 0;
			}
			break ;
		}
		elem = elem->next;
	}
	if (!is_visited)
		add_puzzle_status(tiles_status_map, depth, visited_puzzle_statuses);
	return (is_visited);
}
