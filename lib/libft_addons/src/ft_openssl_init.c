/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:09:41 by jkauppi           #+#    #+#             */
/*   Updated: 2021/04/01 16:17:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_openssl_init(void)
{
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	SSL_library_init();
	OpenSSL_add_ssl_algorithms();
	OpenSSL_add_all_ciphers();
}
