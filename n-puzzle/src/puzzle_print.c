/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:59:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/29 10:05:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	print_puzzle(int fd, unsigned long tiles_pos_map, int puzzle_size)
{
	char			line[1000];
	char			string[6];
	int				tile_number;
	t_xy_values		xy_pos;

	ft_dprintf(fd, " %d\n", puzzle_size);
	xy_pos.y = -1;
	while (++xy_pos.y < puzzle_size)
	{
		ft_bzero(line, sizeof(line));
		xy_pos.x = -1;
		while (++xy_pos.x < puzzle_size)
		{
			tile_number = (tiles_pos_map >> (4 * (xy_pos.y * puzzle_size
							+ xy_pos.x))) & 0xF;
			ft_sprintf(string, " %4d", tile_number);
			ft_strcat(line, string);
		}
		ft_dprintf(fd, "%s\n", line);
	}
	return ;
}
