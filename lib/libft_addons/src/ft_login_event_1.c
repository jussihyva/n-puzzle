/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_login_event_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 10:22:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 10:54:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_loging_params		*g_loging_params;

void	ft_log_set_params(const char **level_strings,
													const char **level_colors)
{
	g_loging_params = (t_loging_params *)ft_memalloc(sizeof(*g_loging_params));
	g_loging_params->level_strings = level_strings;
	g_loging_params->level_colors = level_colors;
	set_g_loging_params_2(g_loging_params);
	set_g_loging_params_3(g_loging_params);
	set_g_loging_params_4(g_loging_params);
	set_g_loging_params_5(g_loging_params);
	return ;
}

void	ft_log_debug(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_DEBUG;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
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

void	ft_log_info(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_INFO;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
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

void	ft_log_warn(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_WARN;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
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

void	ft_log_error(const char *fmt, ...)
{
	t_log_event				event;

	event.fmt = fmt;
	event.file = __FILE__;
	event.line = __LINE__;
	event.level = LOG_ERROR;
	gettimeofday(&event.tv, NULL);
	lock();
	if (!g_loging_params->quiet && event.level >= g_loging_params->level)
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
