/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:05:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 11:49:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static int	add_digit(long *nbr, char c, int base)
{
	long		tmp;

	if (!ft_isdigit_base(c, base))
		return (0);
	tmp = (*nbr * 10) + (c - '0');
	if (tmp >= *nbr)
	{
		*nbr = tmp;
		return (1);
	}
	else
	{
		*nbr = 0;
		errno = ERANGE;
		return (0);
	}
}

static void	set_endptr(char **endptr, const char *str, const char *start_ptr)
{
	if (str == start_ptr)
	{
		if (*str == '\0')
			errno = ECANCELED;
		else
			errno = EINVAL;
	}
	while (ft_isspace(*str))
		str++;
	if (endptr)
		*endptr = (char *)str;
	if (*str)
		errno = EINVAL;
	return ;
}

static int	validate_result(int neg, long nbr)
{
	if ((neg * nbr) > INT_MAX || (neg * nbr) < INT_MIN)
	{
		errno = ERANGE;
		nbr = 0;
	}
	if (neg != 1)
		nbr = -nbr;
	return ((int)nbr);
}

static int	validate_hex_prefixes(int *neg, const char **str)
{
	const char	*ptr;

	ptr = *str;
	if (*ptr == '0')
	{
		ptr++;
		if (*ptr == 'x')
			ptr++;
	}
	*neg = 0;
	return (1);
}

int	ft_strtoi(const char *str, char **endptr, int base)
{
	int			neg;
	long		nbr;
	const char	*start_ptr;

	errno = 0;
	nbr = 0;
	start_ptr = str;
	while (ft_isspace(*str))
		str++;
	if (base == 16 && !validate_hex_prefixes(&neg, &str))
		errno = EINVAL;
	else if (base == 10)
	{
		neg = 1;
		if (*str == '-')
			neg = -1;
		if (*str == '-' || *str == '+')
			str += 1;
	}
	start_ptr = str;
	while (add_digit(&nbr, *str, base))
		str++;
	set_endptr(endptr, str, start_ptr);
	return (validate_result(neg, nbr));
}
