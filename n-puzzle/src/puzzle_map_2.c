/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:23:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 17:25:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

int	remove_comment(char *line)
{
	int			is_line_empty;
	char		*ptr;

	is_line_empty = 0;
	ptr = ft_strchr(line, '#');
	if (ptr)
	{
		FT_LOG_DEBUG("Comment line: %s", line);
		*ptr = '\0';
	}
	ptr = line;
	while (ft_isspace(*ptr))
		ptr++;
	if (!(*ptr))
		is_line_empty = 1;
	return (is_line_empty);
}

static void	validate_tile_number(int **tile_map, t_xy_values yx_pos,
										int number_of_tiles, int *map_numbers)
{
	int				tile_number;

	tile_number = tile_map[yx_pos.y][yx_pos.x];
	if (tile_number >= number_of_tiles)
		FT_LOG_ERROR("The input file include too big tile number(%d).",
			tile_number);
	else if (tile_number < 0)
		FT_LOG_ERROR("The input file include negative tile number(%d).",
			tile_number);
	else if (map_numbers[tile_number])
		FT_LOG_ERROR("The input file includes dublicates (%d)", tile_number);
	map_numbers[tile_number] = 1;
	return ;
}

void	validate_puzzle_map(t_map *puzzle_map)
{
	int				*map_numbers;
	t_xy_values		yx_pos;
	int				number_of_tiles;

	number_of_tiles = puzzle_map->size * puzzle_map->size;
	if (puzzle_map->size < 3)
		FT_LOG_ERROR("Size of a N-puzzle is too small. Minimum size is 3x3.");
	map_numbers = (int *)ft_memalloc(sizeof(*map_numbers) * number_of_tiles);
	yx_pos.y = -1;
	while (++yx_pos.y < puzzle_map->size)
	{
		yx_pos.x = -1;
		while (++yx_pos.x < puzzle_map->size)
			validate_tile_number(puzzle_map->tile_map, yx_pos, number_of_tiles,
				map_numbers);
	}
	ft_memdel((void **)&map_numbers);
	return ;
}
