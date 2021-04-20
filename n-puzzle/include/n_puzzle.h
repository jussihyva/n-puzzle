/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/16 13:02:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
# define N_PUZZLE_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <unistd.h>
# include <time.h>
# include <sys/resource.h>

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

typedef enum e_algorithm
{
	E_DFS_NO_MEM,
	E_DFS_DEEPING,
	E_DFS_DEEPING_MEM,
	E_BFS
}				t_algorithm;

typedef struct s_xy_values
{
	int		x;
	int		y;
}				t_xy_values;

typedef struct s_statistics
{
	t_order				order;
	char				*algorithm;
	char				*algorithm_substring;
	unsigned long		tile_move_cnt;
	struct timespec		start_time;
	struct timespec		end_time;
	time_t				start_time_ms;
	time_t				end_time_ms;
	clock_t				cpu_usage_ms;
	t_tls_connection	*connection;
	int					max_mem_usage;
	int					puzzle_size;
}				t_statistics;

typedef struct s_cmd_args
{
	int				argc;
	char			**argv;
	t_loging_level	loging_level;
	char			*algorithm;
	int				release;
}				t_cmd_args;

typedef struct s_map
{
	int		size;
	int		**tile_map;
}				t_map;

typedef struct s_input
{
	t_statistics		*statistics;
	const char			**level_strings;
	const char			**level_colors;
	t_cmd_args			*cmd_args;
	t_algorithm			algorithm;
	t_map				*puzzle_map;
}				t_input;

typedef struct s_tile
{
	int			number;
}				t_tile;

typedef struct s_pos
{
	t_xy_values			xy_pos;
	int					order_num;
	struct s_pos		**neighbors;
	int					num_of_neighbors;
}				t_pos;

typedef struct s_move
{
	t_pos	*from_pos;
	t_pos	*to_pos;
}				t_move;

typedef struct s_puzzle_status
{
	unsigned long			tiles_pos_map;
	int						depth;
	struct s_puzzle_status	*prev_status;
	t_move					prev_move;
	t_pos					*empty_pos;
	unsigned int			right_pos_status;
}				t_puzzle_status;

typedef struct s_puzzle
{
	t_statistics		*statistics;
	int					size;
	t_algorithm			algorithm;
	t_pos				***pos_table;
	t_tile				**tile_array;
	unsigned long		*move_cnt;
	unsigned int		puzzle_ready_status;
	int					max_depth;
	t_puzzle_status		*curr_status;
	t_list				**puzzle_status_lst;
	t_queue				*status_queue;
	t_bt_node			**bt_root;
}				t_puzzle;

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

t_input			*read_input_data(int argc, char **argv,
					t_statistics *statistics);
void			set_loging_parameters(t_input *input,
					t_loging_level event_type, t_statistics *statistics);
t_cmd_args		*arg_parser(void (fn)(t_cmd_args *, char, char *), int argc,
					char **argv, char *options);
t_map			*read_puzzle_map(void);
int				remove_comment(char *line);
void			release_input(t_input *input);
void			save_cmd_arguments(t_cmd_args *cmd_args, char opt,
					char *next_arg);
void			dfs(t_puzzle *puzzle, t_statistics *statistics);
t_puzzle		*initialize_puzzle(t_input *input);
void			set_order_number(t_puzzle *puzzle, t_pos ***pos_table,
					int order_num, t_xy_values xy_pos, t_dir dir);
void			release_puzzle(t_puzzle *puzzle);
void			print_puzzle(int fd, t_puzzle *puzzle);
void			stat_set_start_time(t_statistics *statistics);
void			stat_set_end_time(t_statistics *statistics);
time_t			get_execution_time(t_statistics *statistics);
t_statistics	*initialize_statistics(void);
void			influxdb_plugin(t_log_event *event);
t_influxdb		*setup_influxdb_connection(char *host_name, char *port_number);
void			write_influxdb(t_tls_connection *connection, char *body,
					char *database);
void			dfs_no_mem(t_puzzle *puzzle);
void			dfs_deeping(t_puzzle *puzzle);
void			dfs_deeping_mem(t_puzzle *puzzle);
void			tile_move(t_pos *pos1, t_pos *pos2, t_puzzle *puzzle);
t_tile			**initialize_tile_array(t_map *puzzle_map);
void			release_influxdb(t_influxdb *influxdb);
void			stat_update_mem_usage(t_statistics *statistics);
void			release_statistics_params(t_statistics *statistics);
void			stat_update_cpu_usage(t_statistics *statistics);
void			delete_puzzle_status(void *content, size_t size);
t_puzzle_status	*create_puzzle_status(unsigned long tiles_pos_map,
					t_puzzle_status *prev_puzzle_status, t_pos *empty_pos,
					unsigned int right_pos_status);
int				is_visited_puzzle_status(unsigned long tiles_pos_map,
					t_list **puzzle_status_lst, int depth);
void			add_visited_puzzle_status(t_puzzle_status *puzzle_status,
					t_list **puzzle_status_lst, t_bt_node **bt_root);
unsigned long	create_tiles_pos_map(int **tile_map, t_pos ***pos_table,
					int puzzle_size, t_pos **empty_pos);
void			bfs(t_puzzle *puzzle, t_statistics *statistics);
void			bfs_1(t_puzzle *puzzle);
void			update_tiles_pos_map(t_pos *pos1, t_pos *pos2,
					int puzzle_size, unsigned long *tiles_pos_map);
int				get_tile_number(unsigned long tiles_pos_map, t_pos *pos,
					int puzzle_size);

#endif