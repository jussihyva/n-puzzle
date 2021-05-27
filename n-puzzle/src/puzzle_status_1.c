/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_status_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:07:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/26 13:49:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	update_tiles_pos_map(t_pos *pos1, t_pos *pos2, int puzzle_size,
												t_tiles_pos_map *tiles_pos_map)
{
	unsigned long	tile_number[2];
	int				i[2];
	int				position_number[2];
	int				shift[2];

	position_number[0] = pos1->xy_pos.y * puzzle_size + pos1->xy_pos.x;
	position_number[1] = pos2->xy_pos.y * puzzle_size + pos2->xy_pos.x;
	i[0] = position_number[0] / tiles_pos_map->tiles_per_map_index;
	i[1] = position_number[1] / tiles_pos_map->tiles_per_map_index;
	shift[0] = tiles_pos_map->bits_for_tile_number
		* (position_number[0] % tiles_pos_map->tiles_per_map_index);
	shift[1] = tiles_pos_map->bits_for_tile_number
		* (position_number[1] % tiles_pos_map->tiles_per_map_index);
	tile_number[0] = tiles_pos_map->map[i[0]] >> shift[0]
		& tiles_pos_map->bit_mask;
	tile_number[1] = tiles_pos_map->map[i[1]] >> shift[1]
		& tiles_pos_map->bit_mask;
	tiles_pos_map->map[i[0]] &= ~((unsigned long)tiles_pos_map->bit_mask
			<< (tiles_pos_map->bits_for_tile_number * position_number[0]));
	tiles_pos_map->map[i[1]] &= ~((unsigned long)tiles_pos_map->bit_mask
			<< (tiles_pos_map->bits_for_tile_number * position_number[1]));
	tiles_pos_map->map[i[0]] |= tile_number[0]
		<< (tiles_pos_map->bits_for_tile_number * position_number[0]);
	tiles_pos_map->map[i[1]] |= tile_number[1]
		<< (tiles_pos_map->bits_for_tile_number * position_number[1]);
}

static int	count_num_of_bits_required(int num_of_tiles, int *bit_mask)
{
	int		num_of_bits;

	num_of_bits = 0;
	while (num_of_tiles)
	{
		num_of_tiles = num_of_tiles >> 1;
		num_of_bits++;
		(*bit_mask) <<= 1;
		(*bit_mask) |= 1;
	}
	return (num_of_bits);
}

static t_tiles_pos_map	*initialize_tiles_pos_map(int puzzle_size)
{
	t_tiles_pos_map		*tiles_pos_map;
	int					num_of_tile_positions;
	int					num_of_index;

	tiles_pos_map = (t_tiles_pos_map *)ft_memalloc(sizeof(*tiles_pos_map));
	num_of_tile_positions = puzzle_size * puzzle_size;
	tiles_pos_map->bits_for_tile_number
		= count_num_of_bits_required(num_of_tile_positions - 1,
			&tiles_pos_map->bit_mask);
	tiles_pos_map->tiles_per_map_index = sizeof(tiles_pos_map->map) * 8
		/ tiles_pos_map->bits_for_tile_number;
	num_of_index = num_of_tile_positions / tiles_pos_map->tiles_per_map_index;
	if (num_of_tile_positions % tiles_pos_map->tiles_per_map_index)
		num_of_index++;
	tiles_pos_map->map_size = sizeof(*tiles_pos_map->map) * num_of_index;
	tiles_pos_map->map = (unsigned long *)ft_memalloc(tiles_pos_map->map_size);
	return (tiles_pos_map);
}

static t_tiles_pos_map	*create_tiles_pos_map(int **tile_map, t_pos ***pos_table,
											int puzzle_size, t_pos **empty_pos)
{
	t_tiles_pos_map	*tiles_pos_map;
	t_xy_values		yx_pos;
	int				shift;
	int				pos_number;
	int				pos_map_index;

	tiles_pos_map = initialize_tiles_pos_map(puzzle_size);
	yx_pos.y = -1;
	while (++yx_pos.y < puzzle_size)
	{
		yx_pos.x = -1;
		while (++yx_pos.x < puzzle_size)
		{
			pos_number = yx_pos.y * puzzle_size + yx_pos.x;
			pos_map_index = pos_number / tiles_pos_map->tiles_per_map_index;
			shift = tiles_pos_map->bits_for_tile_number
				* (pos_number % tiles_pos_map->tiles_per_map_index);
			tiles_pos_map->map[pos_map_index]
				|= (unsigned long)tile_map[yx_pos.y][yx_pos.x] << shift;
			if (!tile_map[yx_pos.y][yx_pos.x])
				*empty_pos = pos_table[yx_pos.y][yx_pos.x];
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
													t_tiles_pos_map *tiles_pos_map)
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
			tile_number = (tiles_pos_map->map[0] >> (4 * (i * puzzle_size + j))) & 0xF;
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
	unsigned int		right_pos_status;

	puzzle_status = (t_puzzle_status *)ft_memalloc(sizeof(*puzzle_status));
	puzzle_status->tiles_pos_map = create_tiles_pos_map(tile_map,
			pos_table, puzzle_size, &empty_pos);
	right_pos_status = set_right_pos_status(pos_table, puzzle_size,
			puzzle_status->tiles_pos_map);
	puzzle_status->empty_pos = empty_pos;
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

int	is_visited_puzzle_status_list(t_tiles_pos_map *tiles_pos_map, t_puzzle *puzzle,
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
		if (!(ft_memcmp(tiles_pos_map->map, (*puzzle_status)->tiles_pos_map->map, tiles_pos_map->map_size)))
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
