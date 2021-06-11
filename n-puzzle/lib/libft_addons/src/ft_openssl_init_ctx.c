/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_init_ctx.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:18:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/11 10:54:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

SSL_CTX	*ft_openssl_init_ctx(const SSL_METHOD *tls_method, char *pem_cert_file,
													char *pem_private_key_file)
{
	SSL_CTX				*ctx;
	int					error;

	ctx = SSL_CTX_new(tls_method);
	error = 0;
	if (!SSL_CTX_use_certificate_file(ctx, pem_cert_file, SSL_FILETYPE_PEM))
		error = 1;
	else if (!SSL_CTX_use_PrivateKey_file(ctx, pem_private_key_file,
			SSL_FILETYPE_PEM))
		error = 1;
	else if (!SSL_CTX_check_private_key(ctx))
		error = 1;
	if (error)
	{
		ERR_print_errors_fp(stderr);
		SSL_CTX_free(ctx);
		FT_LOG_FATAL("Error setting up connection to INFLUXDB\n");
		ctx = NULL;
	}
	return (ctx);
}
