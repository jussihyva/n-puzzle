/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/01 08:20:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef N_PUZZLE_H
# define N_PUZZLE_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <unistd.h>
# include <fcntl.h>
# include <time.h>
# include <sys/resource.h>
# include <sys/sysinfo.h>

# define MAX_NUM_OF_NEIGHBORS	4
# define READ_BUF_MAX_SIZE		4096
# define PEM_CERT_FILE			"/var/tmp/tls-selfsigned.crt"
# define PEM_PRIVTE_KEY_FILE	"/var/tmp/tls-selfsigned.key"

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

typedef enum e_heuristic_alg
{
	E_NO_HEURISTIC_ALG,
	E_TAXICAB
}				t_heuristic_alg;

typedef enum e_algorithm
{
	E_DFS_NO_MEM,
	E_DFS_DEEPING,
	E_DFS_DEEPING_MEM,
	E_BFS_1,
	E_BFS_2,
	E_TOOP_1,
	E_A_STAR_T,
	E_IDA_STAR
}				t_algorithm;

typedef struct s_xy_values
{
	int		y;
	int		x;
}				t_xy_values;

# define	NUM_OF_STAT_COUNTERS	16

typedef enum e_stat_counter_name
{
	E_PUZZLE_INITIAL_STATE,
	E_PUZZLE_FINAL_STATE,
	E_IS_PUZZLE_SOLVABLE,
	E_IS_PUZZLE_SOLVED,
	E_NUM_OF_SOLUTION_MOVES,
	E_EXECUTION_TIME,
	E_TOTAL_CPU_USAGE_TIME,
	E_SOLVER_CPU_USAGE_TIME,
	E_PRINTING_CPU_USAGE_TIME,
	E_TOTAL_NUM_OF_PUZZLE_STATES,
	E_TOTAL_NUM_OF_PUZZLE_STATE_COLLISIONS,
	E_MAX_NUM_OF_SAVED_PUZZLE_STATES,
	E_MAX_QUEUE_LEN,
	E_TOTAL_NUM_OF_ELEM_IN_QUEUE,
	E_MAX_MEM_USAGE,
	E_MIN_FREE_MEM
}				t_stat_counter_name;

typedef struct s_stat_counters
{
	char				**string_names;
	int					counter_values[NUM_OF_STAT_COUNTERS];
	long				active_counters[NUM_OF_STAT_COUNTERS];
}				t_stat_counters;

typedef struct s_statistics
{
	t_order				order;
	char				*algorithm;
	char				*algorithm_substring;
	struct timespec		start_time;
	struct timespec		end_time;
	time_t				start_time_ms;
	time_t				end_time_ms;
	clock_t				cpu_usage_ms;
	t_tls_connection	*connection;
	int					tile_move_cnt;
	int					solution_move_cnt;
	int					max_mem_usage;
	int					puzzle_size;
	int					puzzle_states_cnt;
	int					puzzle_state_collision_cnt;
	t_stat_counters		stat_counters;
	int					solver_start_time_ms;
	int					solver_end_time_ms;
}				t_statistics;

typedef struct s_cmd_args
{
	int				argc;
	char			**argv;
	t_loging_level	loging_level;
	char			*algorithm;
	char			*heurestic_algorithm;
	int				release;
	char			*input_file;
	int				print_delay;
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
	t_heuristic_alg		heuristic_algorithm;
	t_map				*puzzle_map;
}				t_input;

typedef struct s_pos
{
	t_xy_values			xy_pos;
	int					pos_index;
	int					right_tile_number;
	struct s_pos		**neighbors;
	int					num_of_neighbors;
}				t_pos;

typedef struct s_move
{
	t_pos	*from_pos;
	t_pos	*to_pos;
}				t_move;

typedef struct s_tiles_pos_map
{
	unsigned long	*map;
	int				bits_for_tile_number;
	int				tiles_per_map_index;
	int				bit_mask;
	int				map_size;
}				t_tiles_pos_map;

typedef struct s_puzzle_status
{
	t_tiles_pos_map			tiles_pos_map;
	int						depth;
	int						tiles_out_of_place;
	int						prio;
	struct s_puzzle_status	*prev_status;
	t_pos					*empty_pos;
	int						is_in_queue;
	int						tiles_in_right_pos;
}				t_puzzle_status;

typedef struct s_puzzle
{
	t_statistics		*statistics;
	int					size;
	int					num_of_tile_pos;
	t_algorithm			algorithm;
	t_pos				***pos_table;
	int					*tile_move_cnt;
	int					*solution_move_cnt;
	t_xy_values			*tile_right_pos_array;
	int					max_depth;
	t_puzzle_status		*curr_status;
	t_list				**puzzle_status_lst;
	int					*states_cnt;
	int					*state_collision_cnt;
	t_queue				*status_queue;
	t_bt_node			**bt_root;
	t_bt_node			**states_prio_queue;
	int					print_delay;
	t_stat_counters		*stat_counters;
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
t_map			*read_puzzle_map(char *input_file);
int				remove_comment(char *line);
void			save_cmd_arguments(t_cmd_args *cmd_args, char opt,
					char *next_arg);
void			dfs(t_puzzle *puzzle);
t_puzzle		*initialize_puzzle(t_input *input);
void			set_tile_numbers_target_positions(t_pos ***pos_table, int size);
void			release(t_input *input, t_influxdb *influxdb, t_puzzle *puzzle);
void			print_puzzle(int fd, t_tiles_pos_map *tiles_pos_map,
					int puzzle_size);
void			stat_set_start_time(t_statistics *statistics);
void			stat_set_end_time(t_statistics *statistics);
void			set_solver_start_time(t_statistics *statistics);
void			set_solver_end_time(t_statistics *statistics);
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
int				is_puzzle_solvable(t_map *puzzle_map,
					t_xy_values *tile_right_pos_array);
void			stat_update_mem_usage(t_statistics *statistics);
void			release_statistics_params(t_statistics *statistics);
void			set_total_cpu_usage_time(t_statistics *statistics);
void			delete_puzzle_status(void *content, size_t size);
t_puzzle_status	*create_puzzle_status(int **tile_map, t_puzzle *puzzle);
t_puzzle_status	*save_current_puzzle_status(t_puzzle_status *curr_status);
int				is_visited_puzzle_status_list(t_tiles_pos_map *tiles_pos_map,
					t_puzzle *puzzle, t_puzzle_status **puzzle_status);
int				is_visited_puzzle_status_b_tree(t_tiles_pos_map *tiles_pos_map,
					t_puzzle *puzzle, t_puzzle_status **puzzle_status);
void			store_visited_puzzle_status_list(t_puzzle_status *puzzle_status,
					t_puzzle *puzzle);
void			store_visited_puzzle_status_b_tree(
					t_puzzle_status *puzzle_status, t_bt_node **bt_root);
void			bfs(t_puzzle *puzzle);
void			alg_toop(t_puzzle *puzzle);
void			alg_toop_1(t_puzzle *puzzle);
void			bfs_1(t_puzzle *puzzle);
int				update_tiles_pos_map(t_pos *pos1, t_pos *pos2,
					int puzzle_size, t_tiles_pos_map *tiles_pos_map);
int				print_solution(t_puzzle_status *puzzle_status,
					t_puzzle *puzzle);
void			alg_a_star(t_puzzle *puzzle);
int				calculate_taxicab_based_prio(t_puzzle_status *puzzle_status,
					int puzzle_size, t_xy_values *tile_right_pos_array);
t_puzzle_status	*add_puzzle_state_to_prio_queue(t_puzzle *puzzle);
void			add_puzzle_state_to_prio_queue_1(t_puzzle_status *puzzle_state,
					t_bt_node **states_prio_queue);
void			alg_ida_star(t_puzzle *puzzle);
void			update_current_puzzle_state(t_puzzle_status *curr_state,
					t_puzzle_status *puzzle_state);
int				get_tile_number(int puzzle_size, t_xy_values *xy,
					t_tiles_pos_map *tiles_pos_map);

#endif
