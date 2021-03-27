/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_puzzle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 07:38:43 by jkauppi           #+#    #+#             */
/*   Updated: 2021/03/27 16:22:08 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

int	main(void)
{
	t_input		*input;

	input = (t_input *)ft_memalloc(sizeof(*input));
	set_loging_parameters(input, LOG_TRACE);
	FT_LOG_FATAL("MOI");
	FT_LOG_ERROR("MOI");
	FT_LOG_WARN("MOI");
	FT_LOG_INFO("MOI");
	FT_LOG_DEBUG("MOI");
	FT_LOG_TRACE("MOI");
	return (0);
}
