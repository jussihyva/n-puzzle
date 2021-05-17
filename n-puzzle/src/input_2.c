/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:32:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/17 10:35:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static int	conv_str_to_int(const char opt, const char *s)
{
	char		*remainings;
	int			value;

	value = ft_strtoi(s, &remainings, 10);
	if (*remainings || errno != 0)
	{
		FT_LOG_ERROR("Not valid parameter value -%c %s", opt, s);
		exit(42);
	}
	if (value < 0)
	{
		FT_LOG_ERROR("Negative value is not allowed -%c %s", opt, s);
		exit(42);
	}
	return (value);
}

void	save_cmd_arguments(t_cmd_args *cmd_args, char opt, char *next_arg)
{
	if (opt == 'L')
		cmd_args->loging_level = conv_str_to_int(opt, next_arg);
	else if (opt == 'D')
		cmd_args->print_delay = conv_str_to_int(opt, next_arg);
	else if (opt == 'A')
	{
		ft_strdel(&cmd_args->algorithm);
		cmd_args->algorithm = next_arg;
	}
	else if (opt == 'H')
	{
		ft_strdel(&cmd_args->heurestic_algorithm);
		cmd_args->heurestic_algorithm = next_arg;
	}
	else if (opt == 'f')
	{
		cmd_args->input_file = next_arg;
	}
	else if (opt == 'r')
		cmd_args->release = 1;
	return ;
}
