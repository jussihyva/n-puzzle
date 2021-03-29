/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/29 22:44:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
# define N_PUZZLE_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <time.h>

# define MAX_NUM_OF_NEIGHBOR	4

typedef enum e_dir
{
	E_RIGHT,
	E_DOWN,
	E_LEFT,
	E_UP
}				t_dir;

typedef enum e_read_state
{
	E_DONE,
	E_READ_SIZE,
	E_READ_TILES
}				t_read_state;

typedef struct s_xy_values
{
	int		x;
	int		y;
}				t_xy_values;

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

typedef struct s_tile_pos
{
	t_xy_values		xy_pos;
	int				order_num;
	int				num;
	void			**neighbors;
	int				is_visited;
}				t_tile_pos;

typedef struct s_puzzle
{
	int				size;
	t_tile_pos		*root_tile;
	t_tile_pos		***tile_pos_table;
}				t_puzzle;

void		set_loging_parameters(t_input *input, t_loging_level event_type);
t_cmd_args	*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
				char **argv);
t_map		*read_puzzle_map(void);
int			remove_comment(char *line);
void		release_input(t_input *input);
void		save_cmd_arguments(t_cmd_args *cmd_args, char opt, char *next_arg);
void		dfs(t_map *puzzle_map);
t_puzzle	*initialize_puzzle(t_map *puzzle_map);
void		set_order_number(t_puzzle *puzzle, int order_num,
				t_xy_values xy_pos, t_dir dir);
void		release_puzzle(t_puzzle *puzzle);

#endif
