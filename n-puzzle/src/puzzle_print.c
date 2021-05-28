/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:59:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/28 18:21:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	print_puzzle(int fd, t_tiles_pos_map *tiles_pos_map, int puzzle_size)
{
	char			line[1000];
	char			string[6];
	int				tile_number;
	t_xy_values		yx;

	ft_dprintf(fd, " %d\n", puzzle_size);
	yx.y = -1;
	while (++yx.y < puzzle_size)
	{
		ft_bzero(line, sizeof(line));
		yx.x = -1;
		while (++yx.x < puzzle_size)
		{
			tile_number = get_tile_number(puzzle_size, &yx, tiles_pos_map);
			ft_sprintf(string, " %4d", tile_number);
			ft_strcat(line, string);
		}
		ft_dprintf(fd, "%s\n", line);
	}
	return ;
}
