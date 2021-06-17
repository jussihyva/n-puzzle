/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 13:14:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/17 14:55:31 by jkauppi          ###   ########.fr       */
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

t_influxdb	*setup_influxdb_connection(char *host_name, char *port_number,
													t_statistics *statistics)
{
	t_tls_connection	*tls_connection;
	SSL_CTX				*ctx;
	int					socket_fd;
	t_influxdb			*influxdb;

	ft_openssl_init();
	tls_connection = NULL;
	influxdb = NULL;
	ctx = ft_openssl_init_client(PEM_CERT_FILE, PEM_PRIVTE_KEY_FILE,
			&socket_fd);
	tls_connection = ft_openssl_connect(host_name, port_number,
			socket_fd, ctx);
	if (tls_connection)
	{
		set_client_socket_params(socket_fd);
		influxdb = init_influx_session(tls_connection);
		influxdb->connection = (void *)tls_connection;
		influxdb->connection_status = e_send_msg0;
		statistics->connection = (t_tls_connection *)influxdb->connection;
	}
	else
		FT_LOG_WARN("Connection setup to Influxdb failed!");
	return (influxdb);
}

void	write_influxdb(t_tls_connection *connection, char *body, char *database)
{
	char		header[READ_BUF_MAX_SIZE];
	char		read_buf[READ_BUF_MAX_SIZE];
	int			chars;
	clock_t		start;
	clock_t		end;

	if (connection)
	{
		sprintf(header,
			"POST /write?db=%s&precision=s %sContent-Length: %ld\r\n\r\n",
			database, "HTTP/1.1\r\nHost: none\r\n", strlen(body));
		SSL_write(connection->ssl_bio, header, strlen(header));
		SSL_write(connection->ssl_bio, body, strlen(body));
		start = clock();
		end = start + CLOCKS_PER_SEC;
		chars = 1;
		while (chars == -1 && end > clock())
			chars = SSL_read(connection->ssl_bio, read_buf, READ_BUF_MAX_SIZE);
		if (chars == -1)
			FT_LOG_ERROR("%s", read_buf);
		chars = 1;
		while (chars > 0)
			chars = SSL_read(connection->ssl_bio, read_buf, READ_BUF_MAX_SIZE);
	}
	return ;
}
