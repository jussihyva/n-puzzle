/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_map_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 17:08:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/21 16:42:32 by jkauppi          ###   ########.fr       */
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
			FT_LOG_ERROR("%s %s.\n",
				"ERROR: Value of a tile should be int. Check line: ", line);
		ft_strdel(&(str_array[i]));
		i++;
	}
	ft_memdel((void **)&str_array);
	if (size != i)
		FT_LOG_ERROR("%s %s %d %s %s.\n",
			"ERROR: Number of tiles is not valid:", ". Should be: ", size,
			"Line:", line);
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

static void	read_map_line(t_map *puzzle_map, char *line,
												t_read_state *state, int *row_i)
{
	if (remove_comment(line))
		return ;
	FT_LOG_DEBUG("Line: %s", line);
	if (*state == E_READ_SIZE)
	{
		puzzle_map->size = read_map_size(line);
		puzzle_map->tile_map = initialize_tile_table(puzzle_map->size);
		*state = E_READ_TILES;
	}
	else if (*state == E_READ_TILES)
	{
		read_tiles(line, puzzle_map->tile_map, ++(*row_i), puzzle_map->size);
		if (puzzle_map->size == *row_i + 1)
			*state = E_DONE;
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
	if (puzzle_map->size < 3)
		FT_LOG_ERROR("Size of a N-puzzle is too small. Minimum size is 3x3.");
	return (puzzle_map);
}
