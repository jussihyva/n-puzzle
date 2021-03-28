/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_map_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 15:23:04 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 15:27:18 by jkauppi          ###   ########.fr       */
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
		ptr = line;
		while (ft_isspace(*ptr))
			ptr++;
		if (!(*ptr))
			is_line_empty = 1;
	}
	return (is_line_empty);
}
