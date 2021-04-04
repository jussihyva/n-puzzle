/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/04 19:40:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
# define N_PUZZLE_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <time.h>

# define MAX_NUM_OF_NEIGHBORS	4
# define READ_BUF_MAX_SIZE		4096
# define PEM_CERT_FILE			"./tls-selfsigned.crt"
# define PEM_PRIVTE_KEY_FILE	"./tls-selfsigned.key"

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

typedef enum e_order
{
	E_NONE,
	E_SEND_TO_INFLUXDB
}				t_order;

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
	char			*algorithm;
}				t_cmd_args;

typedef struct s_map
{
	int		size;
	int		**tile_map;
}				t_map;

typedef struct s_input
{
	const char			**level_strings;
	const char			**level_colors;
	t_cmd_args			*cmd_args;
	t_map				*puzzle_map;
}				t_input;

typedef struct s_pos
{
	t_xy_values			xy_pos;
	int					order_num;
	int					num;
	struct s_pos		**neighbors;
	int					num_of_neighbors;
	struct s_pos		*prev_tile;
	void				*tile;
}				t_pos;

typedef struct s_tile
{
	int			number;
	t_pos		*curr_pos;
	t_pos		*prev_pos;
}				t_tile;

typedef struct s_puzzle
{
	int				size;
	t_pos			*empty_pos;
	t_pos			***pos_table;
	t_tile			**tile_array;
	unsigned long	*move_cnt;
	unsigned int	right_pos_status;
}				t_puzzle;

typedef struct s_statistics
{
	t_order				order;
	char				*algorithm;
	char				*algorithm_substring;
	unsigned long		tile_move_cnt;
	time_t				start_time;
	time_t				end_time;
	t_tls_connection	*connection;
	int					puzzle_size;
}				t_statistics;

typedef enum e_connection_status
{
	e_idle,
	e_waiting_msg0,
	e_waiting_msg1,
	e_waiting_msg2,
	e_waiting_msg3,
	e_waiting_msg4,
	e_send_msg0
}						t_connection_status;

typedef struct s_influxdb
{
	void					*connection;
	t_connection_status		connection_status;
}						t_influxdb;

void			set_loging_parameters(t_input *input,
					t_loging_level event_type, t_statistics *statistics);
t_cmd_args		*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
					char **argv, char *options);
t_map			*read_puzzle_map(void);
int				remove_comment(char *line);
void			release_input(t_input *input);
void			save_cmd_arguments(t_cmd_args *cmd_args, char opt,
					char *next_arg);
void			dfs(t_puzzle *puzzle, t_statistics *statistics,
					t_cmd_args *cmd_args);
t_puzzle		*initialize_puzzle(t_map *puzzle_map);
void			set_order_number(t_puzzle *puzzle, int order_num,
					t_xy_values xy_pos, t_dir dir);
void			release_puzzle(t_puzzle *puzzle);
void			print_puzzle(int fd, t_puzzle *puzzle);
t_statistics	*get_statistics(void);
void			set_start_time(void);
void			set_end_time(void);
time_t			get_execution_time(void);
void			initialize_statistics(t_statistics **g_statistics);
void			influxdb_plugin(t_log_event *event);
t_influxdb		*setup_influxdb_connection(char *host_name, char *port_number);
void			write_influxdb(t_tls_connection *connection, char *body,
					char *database);
void			set_connection(t_tls_connection *connection);
void			set_puzzle_size(int puzzle_size);
void			dfs_no_mem(t_puzzle *puzzle, t_statistics *statistics);
void			dfs_deeping(t_puzzle *puzzle, t_statistics *statistics);
void			tile_num_swap(t_pos *pos1, t_pos *pos2,
					unsigned long *move_cnt);
void			update_right_pos_status(t_pos *pos1, t_pos *pos2,
					unsigned int *right_pos_status);
t_tile			**initialize_tile_array(t_map *puzzle_map);

#endif
