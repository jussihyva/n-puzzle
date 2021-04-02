/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:42:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 17:28:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	release_connection(t_tls_connection **connection)
{
	printf("SSL connect error\n");
	SSL_free((*connection)->ssl_bio);
	(*connection)->ssl_bio = NULL;
	*connection = NULL;
	return ;
}

t_tls_connection	*ft_openssl_connect(char *hostname, char *port,
													int socket_fd, SSL_CTX *ctx)
{
	int					error;
	struct sockaddr_in	addr;
	t_tls_connection	*tls_connection;

	tls_connection = (t_tls_connection *)ft_memalloc(sizeof(*tls_connection));
	tls_connection->socket_fd = socket_fd;
	error = -1;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(port));
	addr.sin_addr.s_addr = inet_addr(hostname);
	error = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
	if (error != -1)
	{
		tls_connection->ssl_bio = SSL_new(ctx);
		SSL_set_fd(tls_connection->ssl_bio, tls_connection->socket_fd);
		error = SSL_connect(tls_connection->ssl_bio);
		if (error == -1)
			release_connection(&tls_connection);
	}
	else
		tls_connection = NULL;
	return (tls_connection);
}
