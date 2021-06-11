/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 09:07:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/11 15:33:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_loging_params		*g_loging_params;

void	set_g_loging_params_5(t_loging_params *loging_params)
{
	g_loging_params = loging_params;
	return ;
}

int	ft_log_add_fd(int *fd, int level)
{
	return (ft_log_add_callback(file_callback, (void *)fd, level));
}

void	ft_log_trace(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_TRACE;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
	{
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}

void	unlock(void)
{
	if (g_loging_params->lock)
	{
		g_loging_params->lock(1, g_loging_params->udata);
	}
}

void	ft_log_fatal(const char *file, const int line, const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = file;
	event.line = line;
	event.level = LOG_FATAL;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
	{
		va_start(event.ap, fmt);
		stdout_callback(&event);
		va_end(event.ap);
		exit(42);
	}
	execute_login_extensions(&event, fmt);
	unlock();
	return ;
}
