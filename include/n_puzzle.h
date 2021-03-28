/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/28 17:57:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
# define N_PUZZLE_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

typedef enum e_read_state
{
	E_DONE,
	E_READ_SIZE,
	E_READ_TILES
}				t_read_state;

typedef struct s_cmd_args
{
	int				argc;
	char			**argv;
	t_loging_level	loging_level;
}				t_cmd_args;

typedef struct s_map
{
	int		size;
	int		**tile_table;
}				t_map;

typedef struct s_input
{
	const char			**level_strings;
	const char			**level_colors;
	t_cmd_args			*cmd_args;
	t_map				*puzzle_map;
}				t_input;

void		set_loging_parameters(t_input *input, t_loging_level event_type);
t_cmd_args	*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
				char **argv);
t_map		*read_puzzle_map(void);
int			remove_comment(char *line);
void		release_mem(t_input *input);
void		save_cmd_arguments(t_cmd_args *cmd_args, char opt, char *next_arg);

#endif
