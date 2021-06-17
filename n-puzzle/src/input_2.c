/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:32:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 10:18:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	print_alg_alternatives(void)
{
	ft_printf("\n-A parameter <alg_name>:\n");
	ft_printf("  a       A* search algorithm\n");
	ft_printf("  ida     IDA* search algorithm\n");
	ft_printf("  greedy  Greedy search algorithm\n");
	ft_printf("  bfs_2   Breadth First Search algorithm\n");
	ft_printf("\n-H parameter <alg_name>:\n");
	ft_printf("  h       Hamming distance\n");
	ft_printf("  t       Taxicab (Manhattan) distance\n");
	ft_printf("  l       Taxicab distance with linear conflicts\n");
}

static void	print_usage(void)
{
	ft_printf("Usage:\n");
	ft_printf("1.     ./bin/n_puzzle [options]\n");
	ft_printf("      3\n");
	ft_printf("      1 2 3\n");
	ft_printf("      4 5 6\n");
	ft_printf("      8 7 0\n");
	ft_printf("      <Cntrl>-D\n");
	ft_printf("\n2.     cat data/3_3_05.map | ./bin/n_puzzle [options]\n");
	ft_printf("%s %s\n",
		"\n3.     python ./bin/PuzzleGenerator.py -s 3",
		"| ./bin/n_puzzle [options]");
	ft_printf("%s %s\n",
		"\n4.     python ./bin/PuzzleGenerator.py -s 3",
		"| ./bin/n_puzzle -D 2000 | ./bin/n-puzzle_gui.py\n");
	ft_printf("\n\nOptional parameters:\n");
	ft_printf("  -A <alg_name> Puzzle solving algorithm\n");
	ft_printf("  -H <alg_name> Heuristic algorithm for distance calculation\n");
	ft_printf("  -L    Event logging level\n");
	ft_printf("  -D    Result printout speed. Delay (ms) between tile moves\n");
	ft_printf("  -r    Release request for post proocessing functions\n");
	ft_printf("  -h    Help printout\n");
	print_alg_alternatives();
	exit(42);
}

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
		cmd_args->algorithm = ft_strdup(next_arg);
	}
	else if (opt == 'H')
	{
		ft_strdel(&cmd_args->heuristic_algorithm);
		cmd_args->heuristic_algorithm = ft_strdup(next_arg);
	}
	else if (opt == 'f')
		cmd_args->input_file = ft_strdup(next_arg);
	else if (opt == 'r')
		cmd_args->release = 1;
	else if (opt == 'h')
		print_usage();
	return ;
}
