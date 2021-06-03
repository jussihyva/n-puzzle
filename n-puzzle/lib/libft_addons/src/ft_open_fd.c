/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:18:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 17:34:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_open_fd(char *file_path)
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
