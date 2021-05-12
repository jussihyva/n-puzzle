/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:57:06 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/12 18:24:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static char	*set_algorithm_string(t_algorithm algorithm)
{
	char		*algorithm_string;

	algorithm_string = NULL;
	if (algorithm == E_DFS_NO_MEM)
		algorithm_string = ft_strdup("dfs");
	else if (algorithm == E_DFS_DEEPING)
		algorithm_string = ft_strdup("dfs");
	else if (algorithm == E_DFS_DEEPING_MEM)
		algorithm_string = ft_strdup("dfs");
	else if (algorithm == E_BFS_1)
		algorithm_string = ft_strdup("bfs");
	else if (algorithm == E_BFS_2)
		algorithm_string = ft_strdup("bfs");
	else if (algorithm == E_TOOP_1)
		algorithm_string = ft_strdup("toop");
	return (algorithm_string);
}

static char	*set_algorithm_substring(t_algorithm algorithm)
{
	char		*algorithm_substring;

	algorithm_substring = NULL;
	if (algorithm == E_DFS_NO_MEM)
		algorithm_substring = ft_strdup("no_mem_rand");
	else if (algorithm == E_DFS_DEEPING)
		algorithm_substring = ft_strdup("deeping");
	else if (algorithm == E_DFS_DEEPING_MEM)
		algorithm_substring = ft_strdup("deeping_mem");
	else if (algorithm == E_BFS_1)
		algorithm_substring = ft_strdup("list");
	else if (algorithm == E_BFS_2)
		algorithm_substring = ft_strdup("b_tree");
	else if (algorithm == E_TOOP_1)
		algorithm_substring = ft_strdup("tiles_out_of_place");
	return (algorithm_substring);
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
		algorithm = E_BFS_1;
	else if (!ft_strcmp(algorithm_string, "bfs_2"))
		algorithm = E_BFS_2;
	else if (!ft_strcmp(algorithm_string, "toop_1"))
		algorithm = E_TOOP_1;
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", algorithm_string,
			"Specify a valid algorithm with the param -A");
	statistics->algorithm = set_algorithm_string(algorithm);
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
	options = ft_strdup("L:rA:f:D:");
	input->cmd_args = arg_parser(save_cmd_arguments, argc, argv, options);
	ft_log_set_level(input->cmd_args->loging_level);
	input->puzzle_map = read_puzzle_map(input->cmd_args->input_file);
	input->algorithm = validate_algorithm(input->cmd_args->algorithm,
			statistics);
	ft_strdel(&options);
	return (input);
}
