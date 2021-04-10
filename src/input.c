/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:57:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/10 14:32:21 by jkauppi          ###   ########.fr       */
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
	else if (opt == 'A')
	{
		ft_strdel(&cmd_args->algorithm);
		cmd_args->algorithm = next_arg;
	}
	else if (opt == 'r')
		cmd_args->release = 1;
	return ;
}

static char	*set_algorithm_substring(t_algorithm algorithm)
{
	static char		*algorithm_substring[4];

	if (!*algorithm_substring)
	{
		algorithm_substring[E_DFS_NO_MEM] = ft_strdup("no_mem_rand");
		algorithm_substring[E_DFS_DEEPING] = ft_strdup("deeping");
		algorithm_substring[E_DFS_DEEPING_MEM] = ft_strdup("deeping_mem");
		algorithm_substring[E_BFS] = ft_strdup("mem");
	}
	return (algorithm_substring[algorithm]);
}

t_algorithm	validate_algorithm(char *algorithm_string, t_statistics *statistics)
{
	t_algorithm		algorithm;

	algorithm = 0;
	if (!ft_strcmp(algorithm_string, "dfs_1"))
		algorithm = E_DFS_NO_MEM;
	else if (!ft_strcmp(algorithm_string, "dfs_2"))
		algorithm = E_DFS_DEEPING;
	else if (!ft_strcmp(algorithm_string, "dfs_3"))
		algorithm = E_DFS_DEEPING_MEM;
	else if (!ft_strcmp(algorithm_string, "bfs_1"))
		algorithm = E_BFS;
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", algorithm_string,
			"Specify a valid algorithm with the param -A");
	statistics->algorithm_substring = set_algorithm_substring(algorithm);
	return (algorithm);
}

t_input	*read_input_data(int argc, char **argv, t_statistics *statistics)
{
	t_input		*input;
	char		*options;

	input = (t_input *)ft_memalloc(sizeof(*input));
	input->statistics = statistics;
	set_loging_parameters(input, LOG_TRACE, statistics);
	options = ft_strdup("L:rA:");
	input->cmd_args = arg_parser(save_cmd_arguments, argc, argv, options);
	ft_log_set_level(input->cmd_args->loging_level);
	input->puzzle_map = read_puzzle_map();
	input->algorithm = validate_algorithm(input->cmd_args->algorithm,
			statistics);
	ft_strdel(&options);
	return (input);
}
