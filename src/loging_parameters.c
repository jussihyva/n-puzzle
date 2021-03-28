/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loging_parameters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:33:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 10:26:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	set_level_strings(const char **level_strings)
{
	level_strings[LOG_TRACE] = ft_strdup("TRACE");
	level_strings[LOG_DEBUG] = ft_strdup("DEBUG");
	level_strings[LOG_INFO] = ft_strdup("INFO");
	level_strings[LOG_WARN] = ft_strdup("WARN");
	level_strings[LOG_ERROR] = ft_strdup("ERROR");
	level_strings[LOG_FATAL] = ft_strdup("FATAL");
	return ;
}

void	set_loging_parameters(t_input *input, t_loging_level event_type)
{
	input->level_strings
		= (const char **)ft_memalloc(sizeof(*input->level_strings) * 6);
	input->level_colors
		= (const char **)ft_memalloc(sizeof(*input->level_strings) * 6);
	set_level_strings(input->level_strings);
	input->level_colors[LOG_TRACE] = ft_strdup("\x1b[94m");
	input->level_colors[LOG_DEBUG] = ft_strdup("\x1b[36m");
	input->level_colors[LOG_INFO] = ft_strdup("\x1b[32m");
	input->level_colors[LOG_WARN] = ft_strdup("\x1b[33m");
	input->level_colors[LOG_ERROR] = ft_strdup("\x1b[31m");
	input->level_colors[LOG_FATAL] = ft_strdup("\x1b[35m");
	ft_log_set_params(input->level_strings, input->level_colors);
	ft_log_set_level(event_type);
	return ;
}
