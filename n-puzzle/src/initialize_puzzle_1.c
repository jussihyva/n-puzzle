/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_puzzle_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:19:02 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/11 15:38:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static t_xy_values	*create_tile_right_pos_array(t_pos ***pos_table,
																int puzzle_size)
{
	t_xy_values		xy;
	t_xy_values		*tile_right_pos_array;

	tile_right_pos_array
		= (t_xy_values *)ft_memalloc(sizeof(*tile_right_pos_array)
			* puzzle_size * puzzle_size);
	xy.y = -1;
	while (++xy.y < puzzle_size)
	{
		xy.x = -1;
		while (++xy.x < puzzle_size)
			tile_right_pos_array[pos_table[xy.y][xy.x]->right_tile_number] = xy;
	}
	return (tile_right_pos_array);
}

static void	set_tile_neighbors(t_pos ***pos_table, int size)
{
	t_pos			*pos;
	int				i;
	int				j;
	int				k;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			k = 0;
			pos = pos_table[i][j];
			if (i > 0)
				pos->neighbors[k++] = pos_table[i - 1][j];
			if (j > 0)
				pos->neighbors[k++] = pos_table[i][j - 1];
			if (i < size - 1)
				pos->neighbors[k++] = pos_table[i + 1][j];
			if (j < size - 1)
				pos->neighbors[k++] = pos_table[i][j + 1];
			pos->num_of_neighbors = k;
		}
	}
	return ;
}

static t_pos	*initialize_tile_pos(t_xy_values *xy_pos)
{
	t_pos		*pos;

	pos = (t_pos *)ft_memalloc(sizeof(*pos));
	ft_memcpy(&pos->xy_pos, xy_pos, sizeof(pos->xy_pos));
	pos->neighbors = (t_pos **)ft_memalloc(sizeof(*pos->neighbors)
			* MAX_NUM_OF_NEIGHBORS);
	return (pos);
}

static t_pos	***initialize_pos_table(int puzzle_size)
{
	t_pos			***pos_table;
	t_xy_values		xy_pos;
	int				pos_index;

	pos_index = 0;
	pos_table = (t_pos ***)ft_memalloc(sizeof(*pos_table) * puzzle_size);
	xy_pos.y = -1;
	while (++xy_pos.y < puzzle_size)
	{
		pos_table[xy_pos.y] = (t_pos **)
			ft_memalloc(sizeof(*pos_table[xy_pos.y]) * puzzle_size);
		xy_pos.x = -1;
		while (++xy_pos.x < puzzle_size)
		{
			pos_table[xy_pos.y][xy_pos.x] = initialize_tile_pos(&xy_pos);
			pos_table[xy_pos.y][xy_pos.x]->pos_index = pos_index;
			pos_index++;
		}
	}
	set_tile_neighbors(pos_table, puzzle_size);
	return (pos_table);
}

t_puzzle	*initialize_puzzle(t_input *input)
{
	t_puzzle		*puzzle;
	t_map			*puzzle_map;

	puzzle_map = input->puzzle_map;
	puzzle = (t_puzzle *)ft_memalloc(sizeof(*puzzle));
	puzzle->print_delay = input->cmd_args->print_delay;
	puzzle->statistics = input->statistics;
	puzzle->algorithm = input->algorithm;
	puzzle->heuristic_algorithm = input->heuristic_algorithm;
	puzzle->size = puzzle_map->size;
	puzzle->num_of_tile_pos = puzzle->size * puzzle->size;
	puzzle->states_prio_queue
		= (t_bt_node **)ft_memalloc(sizeof(*puzzle->states_prio_queue));
	puzzle->bt_root
		= (t_bt_node **)ft_memalloc(sizeof(*puzzle->bt_root));
	puzzle->puzzle_status_lst
		= (t_list **)ft_memalloc(sizeof(*puzzle->puzzle_status_lst));
	puzzle->status_queue = ft_queue_init();
	puzzle->pos_table = initialize_pos_table(puzzle->size);
	set_tile_numbers_target_positions(puzzle->pos_table, puzzle->size);
	puzzle->tile_right_pos_array
		= create_tile_right_pos_array(puzzle->pos_table, puzzle->size);
	puzzle->curr_status = create_puzzle_status(puzzle_map->tile_map, puzzle);
	puzzle->solvable = is_puzzle_solvable(puzzle_map, puzzle->tile_right_pos_array);
	return (puzzle);
}
