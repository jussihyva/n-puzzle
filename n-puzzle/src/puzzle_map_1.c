/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:08:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/23 23:03:52 by jkauppi          ###   ########.fr       */
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
			FT_LOG_ERROR("%s %s",
				"ERROR: Value of a tile should be int. Check line: ", line);
		ft_strdel(&(str_array[i]));
		i++;
	}
	ft_memdel((void **)&str_array);
	if (size != i)
		FT_LOG_ERROR("%s %s %d %s %s",
			"ERROR: Number of tiles is not valid:", ". Should be:", size,
			". Check tile line:", line);
	return ;
}

static int	read_map_size(const char *line)
{
	char			*remainings;
	int				size;

	size = ft_strtoi(line, &remainings, 10);
	if (*remainings != '\0' || errno)
	{
		FT_LOG_ERROR("%s %s",
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

static void	read_map_line(t_map *puzzle_map, char *line,
												t_read_state *state, int *row_i)
{
	if (remove_comment(line))
	{
		if (*state == E_READ_TILES)
			FT_LOG_ERROR("Empty line in the input file.");
	}
	else
	{
		FT_LOG_DEBUG("Line: %s", line);
		if (*state == E_READ_SIZE)
		{
			puzzle_map->size = read_map_size(line);
			puzzle_map->tile_map = initialize_tile_table(puzzle_map->size);
			*state = E_READ_TILES;
		}
		else if (*state == E_READ_TILES)
		{
			read_tiles(line, puzzle_map->tile_map, ++(*row_i),
				puzzle_map->size);
			if (puzzle_map->size == *row_i + 1)
				*state = E_DONE;
		}
	}
	return ;
}

int	open_fd(char *file_path)
{
	int		fd;

	fd = 0;
	if (file_path)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			FT_LOG_ERROR("%s (%s) failed! errno=%d. %s: %s",
				"Opening of a file", file_path, errno, "Detail info",
				strerror(errno));
			exit(42);
		}
	}
	return (fd);
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

static void	validate_puzzle_map(t_map *puzzle_map)
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

t_map	*read_puzzle_map(char *input_file)
{
	t_map			*puzzle_map;
	char			*line;
	int				row_i;
	t_read_state	state;
	int				fd;

	puzzle_map = (t_map *)ft_memalloc(sizeof(*puzzle_map));
	line = NULL;
	state = E_READ_SIZE;
	row_i = -1;
	fd = open_fd(input_file);
	while (ft_get_next_line(fd, &line) > 0)
	{
		read_map_line(puzzle_map, line, &state, &row_i);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (fd)
		close(fd);
	FT_LOG_INFO("Puzzle size: %d", puzzle_map->size);
	if (puzzle_map->size != (row_i + 1))
		FT_LOG_ERROR("Number of tile lines should be %d. Check the input file",
			puzzle_map->size);
	validate_puzzle_map(puzzle_map);
	return (puzzle_map);
}
