/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:59:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/05 08:36:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

void	print_puzzle(int fd, t_puzzle *puzzle)
{
	int		i;
	int		j;
	char	line[1000];
	char	string[6];
	t_pos	*pos;

	ft_dprintf(fd, " %d\n", puzzle->size);
	i = -1;
	while (++i < puzzle->size)
	{
		ft_bzero(line, sizeof(line));
		j = -1;
		while (++j < puzzle->size)
		{
			pos = puzzle->pos_table[i][j];
			ft_sprintf(string, " %4d", ((t_tile *)pos->tile)->number);
			ft_strcat(line, string);
		}
		ft_dprintf(fd, "%s\n", line);
	}
	return ;
}
