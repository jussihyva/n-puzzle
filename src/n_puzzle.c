/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 17:59:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

// static void	print_map()
// {
// 	return ;
// }

int	main(int argc, char **argv)
{
	t_input		*input;

	input = (t_input *)ft_memalloc(sizeof(*input));
	set_loging_parameters(input, LOG_TRACE);
	input->cmd_args = arg_parser(save_cmd_arguments, argc, argv);
	ft_log_set_level(input->cmd_args->loging_level);
	input->puzzle_map = read_puzzle_map();
	release_mem(input);
	return (0);
}
