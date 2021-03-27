/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 08:21:58 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 10:56:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_loging_params	*g_loging_params;

void	set_g_loging_params_2(t_loging_params *loging_params)
{
	g_loging_params = loging_params;
	return ;
}

void	execute_login_extensions(t_log_event *event,
														const char *fmt, ...)
{
	size_t					i;
	t_loging_extension		*loging_extension;

	i = -1;
	while (++i < MAX_LOGING_EXTENSIONS)
	{
		if (g_loging_params->loging_extensions[i])
		{
			loging_extension = g_loging_params->loging_extensions[i];
			if (event->level >= loging_extension->level)
			{
				event->fd = loging_extension->fd;
				va_start(event->ap, fmt);
				loging_extension->fn(event);
				va_end(event->ap);
			}
		}
	}
	return ;
}

void	ft_login_event(int level, const char *file, int line,
														const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = level;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && level >= g_loging_params->level)
	{
		event.fd = 2;
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}
