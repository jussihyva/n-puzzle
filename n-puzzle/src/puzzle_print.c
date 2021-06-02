/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:59:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/02 19:05:18 by jkauppi          ###   ########.fr       */
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

int	print_solution(t_puzzle_status *puzzle_status, t_puzzle *puzzle)
{
	int		is_puzzle_ready;

	puzzle->stat_counters->active_counters[E_NUM_OF_SOLUTION_MOVES] = 1;
	if (puzzle_status->prev_status)
	{
		puzzle->stat_counters->counter_values[E_NUM_OF_SOLUTION_MOVES]++;
		(*puzzle->solution_move_cnt)++;
		is_puzzle_ready = print_solution(puzzle_status->prev_status, puzzle);
	}
	print_puzzle(1, &puzzle_status->tiles_pos_map, puzzle->size);
	sleep(puzzle->print_delay / 10);
	is_puzzle_ready = 1;
	return (is_puzzle_ready);
}
