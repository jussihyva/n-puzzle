/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:28:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/06 13:24:54 by jkauppi          ###   ########.fr       */
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
							t_cmd_args *cmd_args, int *arg_index, char *options)
{
	int			i;
	char		*arg;
	char		*opt_ptr;

	arg = cmd_args->argv[*arg_index];
	i = 1;
	while (arg[i])
	{
		opt_ptr = ft_strchr(options, arg[i]);
		if (opt_ptr)
		{
			if (*(opt_ptr + 1) == ':')
			{
				if (++(*arg_index) >= cmd_args->argc)
					param_error("Missing argument for parameter: -%c", arg[i]);
				fn(cmd_args, arg[i], cmd_args->argv[*arg_index]);
				break ;
			}
			else
				fn(cmd_args, arg[i], NULL);
			i++;
		}
		else
			param_error("Unknown parameter: -%c", arg[i]);
	}
}

static t_cmd_args	*initialize_cmd_args(int argc, char **argv)
{
	t_cmd_args			*cmd_args;

	cmd_args = (t_cmd_args *)ft_memalloc(sizeof(*cmd_args));
	cmd_args->argc = argc;
	cmd_args->argv = argv;
	cmd_args->loging_level = LOG_ERROR;
	cmd_args->algorithm = ft_strdup("dfs_1");
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
													char **argv, char *options)
{
	t_cmd_args			*cmd_args;
	int					arg_index;

	cmd_args = initialize_cmd_args(argc, argv);
	arg_index = 0;
	while (++arg_index < argc)
	{
		if (argv[arg_index][0] == '-')
			split_cmd_argument(fn, cmd_args, &arg_index, options);
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
