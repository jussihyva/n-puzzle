/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:28:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 10:51:00 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	param_error(const char *error_string, const char s)
{
	FT_LOG_ERROR(error_string, s);
	exit(42);
	return ;
}

static void	split_cmd_argument(void (fn)(t_cmd_args *, char, char *),
										t_cmd_args *cmd_args, int *arg_index)
{
	int			i;
	char		*arg;

	arg = cmd_args->argv[*arg_index];
	i = 1;
	while (arg[i] && ft_strchr("fMLPSFAxyz", arg[i]))
	{
		if ((*arg_index + 1) < cmd_args->argc)
		{
			fn(cmd_args, arg[i], cmd_args->argv[*arg_index + 1]);
			(*arg_index)++;
			i++;
			break ;
		}
		else
			param_error("Missing argument for parameter: -%c", arg[i]);
		i++;
	}
	if (arg[i])
		param_error("Unknown parameter: -%c", arg[i]);
	return ;
}

static t_cmd_args	*initialize_cmd_args(int argc, char **argv)
{
	t_cmd_args			*cmd_args;

	cmd_args = (t_cmd_args *)ft_memalloc(sizeof(*cmd_args));
	cmd_args->argc = argc;
	cmd_args->argv = argv;
	cmd_args->loging_level = LOG_ERROR;
	return (cmd_args);
}

static void	print_usage(void)
{
	ft_printf("Usage: ./bin/n_puzzle\n");
	ft_printf("Optional parameters:\n");
	ft_printf("	-L (loging level)\n");
	exit(0);
	return ;
}

t_cmd_args	*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
																	char **argv)
{
	t_cmd_args			*cmd_args;
	int					arg_index;

	cmd_args = initialize_cmd_args(argc, argv);
	arg_index = 0;
	while (++arg_index < argc)
	{
		if (argv[arg_index][0] == '-')
			split_cmd_argument(fn, cmd_args, &arg_index);
		else
		{
			fn(cmd_args, 'f', argv[arg_index]);
			break ;
		}
	}
	if (1 == 2)
		print_usage();
	return (cmd_args);
}
