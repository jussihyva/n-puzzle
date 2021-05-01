/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_addons.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 14:53:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/01 20:39:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_ADDONS_H
# define LIBFT_ADDONS_H
# include "libft.h"
# include "ft_printf.h"
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <openssl/ssl.h>
# include <openssl/err.h>

# define MAX_LOGING_EXTENSIONS		32
# define PI							3.141592654
# define LOGING_LEVELS				6
# define MAX_NUM_OF_B_TREE_ELEMS	1024

typedef enum e_loging_level
{
	LOG_TRACE = 0,
	LOG_DEBUG = 1,
	LOG_INFO = 2,
	LOG_WARN = 3,
	LOG_ERROR = 4,
	LOG_FATAL = 5
}				t_loging_level;

# if DARWIN
typedef struct s_timeval
{
	__darwin_time_t			tv_sec;
	__darwin_suseconds_t	tv_usec;
}									t_timeval;
# else
typedef struct s_timeval
{
	__kernel_time_t			tv_sec;
	__kernel_suseconds_t	tv_usec;
}									t_timeval;
# endif

typedef struct s_tls_connection
{
	int			socket_fd;
	SSL_CTX		*ctx;
	SSL			*ssl_bio;
}				t_tls_connection;

typedef struct s_matrix_size
{
	size_t		rows;
	size_t		columns;
}				t_matrix_size;

typedef struct s_log_event
{
	va_list			ap;
	const char		*fmt;
	const char		*file;
	struct timeval	tv;
	void			*additional_event_data;
	int				line;
	int				level;
}				t_log_event;

typedef void	(*t_loging_function)(t_log_event *event);
typedef void	(*t_loging_lock_function)(int lock, void *udata);

typedef struct s_loging_extension
{
	t_loging_function	fn;
	void				*additional_event_data;
	int					level;
}				t_loging_extension;

typedef struct s_loging_params
{
	void					*udata;
	t_loging_lock_function	lock;
	int						level;
	int						quiet;
	const char				**level_strings;
	const char				**level_colors;
	t_loging_extension		*loging_extensions[MAX_LOGING_EXTENSIONS];
}				t_loging_params;

typedef struct s_queue
{
	t_list		**in_stack;
	t_list		**out_stack;
}				t_queue;

typedef struct s_bt_key
{
	void				*key;
	size_t				key_size;
}				t_bt_key;

typedef struct s_bt_data
{
	void				*data;
	size_t				data_size;
}				t_bt_data;

typedef struct s_bt_elem
{
	t_bt_data			bt_data;
	t_bt_key			bt_key;
	struct s_bt_node	*left_child;
	struct s_bt_node	*right_child;
}				t_bt_elem;

typedef struct s_bt_node
{
	int					num_of_elems;
	t_bt_elem			bt_elem[MAX_NUM_OF_B_TREE_ELEMS];
	struct s_bt_node	*parent;
}				t_bt_node;

void				ft_log_trace(const char *file, const int line,
						const char *fmt, ...);
void				ft_log_debug(const char *file, const int line,
						const char *fmt, ...);
void				ft_log_info(const char *file, const int line,
						const char *fmt, ...);
void				ft_log_warn(const char *file, const int line,
						const char *fmt, ...);
void				ft_log_error(const char *file, const int line,
						const char *fmt, ...);
void				ft_log_fatal(const char *file, const int line,
						const char *fmt, ...);
void				ft_log_set_lock(t_loging_lock_function fn, void *udata);
void				ft_log_set_level(int level);
/*
** void			log_set_quiet(int enable);
*/
int					ft_log_add_fd(int *fd, int level);
void				ft_loging_event(int level, const char *file, int line,
						const char *fmt, ...);
void				ft_log_set_params(const char **level_strings,
						const char **level_colors);
void				set_g_loging_params_2(t_loging_params *loging_params);
void				set_g_loging_params_3(t_loging_params *loging_params);
void				set_g_loging_params_4(t_loging_params *loging_params);
void				set_g_loging_params_5(t_loging_params *loging_params);
double				ft_radian(double angle_degree);
int					ft_max_int(int nbr1, int nbr2);
int					ft_min_int(int nbr1, int nbr2);
double				ft_max_double(double nbr1, double nbr2);
double				ft_min_double(double nbr1, double nbr2);
double				ft_mod_double(double dividend, double divisor);
int					ft_mod_int(int dividend, int divisor);
void				ft_matrix_x_vector_double(t_matrix_size matrix_size,
						double **matrix, double *vector, double *new_vector);
int					ft_isdigit_base(int c, int base);
int					ft_strtoi(const char *str, char **endptr, int base);
void				stdout_callback(t_log_event *event);
void				unlock(void);
void				lock(void);
void				file_callback(t_log_event *event);
void				execute_login_extensions(t_log_event *event,
						const char *fmt, ...);
int					ft_log_add_callback(t_loging_function fn,
						void *additional_event_data, int level);
void				ft_release_loging_params(void);
void				ft_openssl_init(void);
SSL_CTX				*ft_openssl_init_ctx(const SSL_METHOD	*tls_method,
						char *pem_cert_file, char *pem_private_key_file);
SSL_CTX				*ft_openssl_init_client(char *pem_cert_file,
						char *pem_private_key_file, int *socket_fd);
t_tls_connection	*ft_openssl_connect(char *hostname, char *port,
						int socket_fd, SSL_CTX *ctx);
void				ft_openssl_rel_conn(t_tls_connection **connection);
void				ft_stack_push(t_list **stack, void **data);
void				*ft_stack_pop(t_list **stack);
void				ft_enqueue(t_queue *queue, void **data);
void				*ft_dequeue(t_queue *queue);
int					ft_is_queue_empty(t_queue *queue);
t_queue				*ft_queue_init(void);
void				ft_bt_instert(t_bt_key *bt_key, t_bt_data *bt_data,
						t_bt_node **bt_root);
void				ft_bt_print(t_bt_node *bt_node, int *count);
int					find_elem_index(t_bt_key *bt_key, t_bt_node **bt_node,
						int recursive, int *is_found);
int					ft_bt_find(t_bt_key *bt_key, t_bt_node *bt_root);
void				ft_bt_remove(t_bt_node **bt_node, t_bt_key *bt_key);

# define FT_LOG_FATAL(...)	ft_log_fatal(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_ERROR(...)	ft_log_error(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_WARN(...)	ft_log_warn(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_INFO(...)	ft_log_info(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_DEBUG(...)	ft_log_debug(__FILE__, __LINE__, __VA_ARGS__)
# define FT_LOG_TRACE(...)	ft_log_trace(__FILE__, __LINE__, __VA_ARGS__)

#endif
