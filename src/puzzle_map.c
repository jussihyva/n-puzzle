/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:08:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 14:57:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	read_tiles(const char *line, int **tile_table, int row_i, int size)
{
	char			*remainings;
	char			**str_array;
	int				i;

	i = 0;
	str_array = ft_strsplit(line, ' ');
	while (str_array[i])
	{
		tile_table[row_i][i] = ft_strtoi(str_array[i], &remainings, 10);
		if (*remainings != '\0' || errno)
		{
			FT_LOG_ERROR("%s %s.\n",
				"ERROR: Value of a tile should be int. Check line: ", line);
			exit(42);
		}
		i++;
	}
	if (size != i)
	{
		FT_LOG_ERROR("%s %s %d %s %s.\n",
			"ERROR: Number of tiles is not valid:", ". Should be: ", size,
			"Line:", line);
		exit(42);
	}
	return ;
}

static int	read_map_size(const char *line)
{
	char			*remainings;
	int				size;

	size = ft_strtoi(line, &remainings, 10);
	if (*remainings != '\0' || errno)
	{
		FT_LOG_ERROR("%s %s.\n",
			"ERROR: Map size is not valid integer value:",
			line);
		exit(42);
	}
	return (size);
}

static int	**initialize_tile_table(int size)
{
	int		**tile_table;
	int		i;

	tile_table = (int **)ft_memalloc(sizeof(*tile_table) * size);
	i = -1;
	while (++i < size)
		tile_table[i] = (int *)ft_memalloc(sizeof(*tile_table[i]) * size);
	return (tile_table);
}

static int	remove_comment(char *line)
{
	int		is_line_empty;
	char	*ptr;

	ptr = ft_strchr(line, '#');
	if (ptr)
		*ptr = '\0';
	ptr = line;
	while (ft_isspace(*ptr))
		ptr++;
	if (*ptr)
		is_line_empty = 0;
	else
		is_line_empty = 1;
	return (is_line_empty);
}

static t_map	*read_map_lines(void)
{
	t_map			*map;
	char			*line;
	int				row_i;
	t_read_state	state;

	map = (t_map *)ft_memalloc(sizeof(*map));
	line = NULL;
	state = E_READ_SIZE;
	row_i = -1;
	while (state != E_DONE && ft_get_next_line(0, &line) > 0)
	{
		if (remove_comment(line))
			continue ;
		FT_LOG_DEBUG("Line: %s", line);
		if (state == E_READ_SIZE)
		{
			map->size = read_map_size(line);
			map->tile_table = initialize_tile_table(map->size);
			state = E_READ_TILES;
		}
		else if (state == E_READ_TILES)
		{
			read_tiles(line, map->tile_table, ++row_i, map->size);
			if (map->size == row_i + 1)
				state = E_DONE;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (map);
}

t_map	*read_puzzle_map(void)
{
	t_map			*puzzle_map;

	puzzle_map = read_map_lines();
	FT_LOG_INFO("Puzzle size: %d", puzzle_map->size);
	return (puzzle_map);
}
