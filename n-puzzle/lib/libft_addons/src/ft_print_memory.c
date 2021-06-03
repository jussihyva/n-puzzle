/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 08:28:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 10:23:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static size_t	print_ascii(char *addr, size_t size)
{
	char	i;
	size_t	index;

	index = 0;
	while (index < 16 && index < size)
	{
		i = *((char *)addr + index);
		if (ft_isprint(i))
			ft_putchar(i);
		else
			ft_putchar('.');
		index++;
	}
	return (index);
}

static size_t	print_hex(char *addr, size_t size)
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
			ft_putchar(letter[(i & 0xF0) >> 4]);
			ft_putchar(letter[i & 0x0F]);
		}
		else
		{
			ft_putchar(' ');
			ft_putchar(' ');
		}
		if (!((index + 1) % 2))
			ft_putchar(' ');
		index++;
	}
	return (index);
}

static void	print_ptr(char *addr, size_t index)
{
	ft_printf("%p (%0#6lx): ", addr + index, index);
	return ;
}

void	ft_print_memory(const void *addr, size_t size)
{
	size_t		index;

	index = 0;
	while (index < size)
	{
		print_ptr((char *)addr, index);
		print_hex((char *)addr + index, size - index);
		index += print_ascii((char *)addr + index, size - index);
		ft_putchar('\n');
	}
}
