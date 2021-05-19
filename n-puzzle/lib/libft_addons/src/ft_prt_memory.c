/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 08:28:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/05/19 08:29:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
 * File: e_print_memory.c
 * Project: src
 * File Created: Friday, 30th October 2020 11:05:15 am
 * Author: eujhuka (matti.kauppi@ericsson.com)
 * -----
 * Last Modified: Friday, 30th October 2020 11:05:24 am
 * Modified By: eujhuka (matti.kauppi@ericsson.com>)
 * -----
 * Copyright <<projec	addr_len = sizeof(sockaddr);
tCreationYear>> - 2020 Oy L M Ericsson Ab, Oy L M Ericsson Ab
 */

#include "libe.h"

static int			e_putchar(int c)
{
	printf("%c", (char)c);
	return (c);
}

static int			e_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}

static size_t		e_print_ascii(char *addr, size_t size)
{
	char	i;
	size_t	index;

	index = 0;
	while (index < 16 && index < size)
	{
		i = *((char *)addr + index);
		if (e_isprint(i))
			e_putchar(i);
		else
			e_putchar('.');
		index++;
	}
	return (index);
}

static size_t		e_print_hex(char *addr, size_t size)
{
	static char		letter[] = "0123456789abcdef";
	char			i;
	size_t			index;

	index = 0;
	while (index < 16)
	{
		if (index < size)
		{
			i = *((char *)addr + index);
			e_putchar(letter[(i & 0xF0) >> 4]);
			e_putchar(letter[i & 0x0F]);
		}
		else
		{
			e_putchar(' ');
			e_putchar(' ');
		}
		if (!((index + 1) % 2))
			e_putchar(' ');
		index++;
	}
	return (index);
}

static void			e_print_ptr(char *addr, size_t index)
{
	printf("%p (%0#6lx): ", addr + index, index);
	return ;
}

void				e_print_memory(const void *addr, size_t size)
{
	size_t		index;

	index = 0;
	while (index < size)
	{
		e_print_ptr((char *)addr, index);
		e_print_hex((char *)addr + index, size - index);
		index += e_print_ascii((char *)addr + index, size - index);
		e_putchar('\n');
	}
}
