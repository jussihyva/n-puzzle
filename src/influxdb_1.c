/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:14:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 17:11:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

static void	set_client_socket_params(int socket_fd)
{
	t_timeval		timeout;
	int				on;

	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	on = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
		sizeof(timeout));
	return ;
}

static t_influxdb	*init_influx_session(t_tls_connection *tls_connection)
{
	t_influxdb	*influxdb;

	influxdb = (t_influxdb *)ft_memalloc(sizeof(*influxdb));
	influxdb->connection = tls_connection;
	influxdb->connection_status = e_waiting_msg2;
	return (influxdb);
}

t_influxdb	*setup_influxdb_connection(char *host_name, char *port_number)
{
	t_tls_connection	*tls_connection;
	SSL_CTX				*ctx;
	int					socket_fd;
	t_influxdb			*influxdb;
	char				read_buf[READ_BUF_MAX_SIZE];
	int					chars;

	ft_openssl_init();
	tls_connection = NULL;
	influxdb = NULL;
	while (!tls_connection)
	{
		ctx = ft_openssl_init_client(PEM_CERT_FILE, PEM_PRIVTE_KEY_FILE,
				&socket_fd);
		tls_connection = ft_openssl_connect(host_name, port_number,
				socket_fd, ctx);
		set_client_socket_params(socket_fd);
		influxdb = init_influx_session(tls_connection);
		influxdb->connection_status = e_send_msg0;
	}
	chars = SSL_read(tls_connection->ssl_bio, read_buf, READ_BUF_MAX_SIZE);
	while (chars > 0)
	{
		ft_printf("%s\n", read_buf);
		chars = SSL_read(tls_connection->ssl_bio, read_buf, READ_BUF_MAX_SIZE);
	}
	return (influxdb);
}
