/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 10:38:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
# define N_PUZZLE_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

typedef struct s_cmd_args
{
	int				argc;
	char			**argv;
	t_loging_level	loging_level;
}				t_cmd_args;

typedef struct s_input
{
	const char			**level_strings;
	const char			**level_colors;
	t_cmd_args			*cmd_args;
}				t_input;

void		set_loging_parameters(t_input *input, t_loging_level event_type);
t_cmd_args	*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
				char **argv);

#endif
