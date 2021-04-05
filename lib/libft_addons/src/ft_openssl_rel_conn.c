/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_rel_conn.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:41:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/05 12:07:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_openssl_rel_conn(t_tls_connection **connection)
{
	printf("SSL connect error\n");
	SSL_free((*connection)->ssl_bio);
	SSL_CTX_free((*connection)->ctx);
	(*connection)->ctx = NULL;
	(*connection)->ssl_bio = NULL;
	ft_memdel((void **)connection);
	return ;
}
