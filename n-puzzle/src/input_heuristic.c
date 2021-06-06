/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heuristic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:30:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/06 12:35:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

char	*based_on_heuristic_alg(t_heuristic_alg algorithm)
{
	char		*algorithm_substring;

	algorithm_substring = NULL;
	if (algorithm == E_TAXICAB)
		algorithm_substring = ft_strdup("taxicab");
	else if (algorithm == E_HAMMING)
		algorithm_substring = ft_strdup("hamming");
	return (algorithm_substring);
}

t_heuristic_alg	validate_heuristic_algorithm(char *algorithm_string,
													char *heuristic_algorithm)
{
	t_heuristic_alg		heuristic_alg;

	heuristic_alg = E_NO_HEURISTIC_ALG;
	if (!ft_strcmp(heuristic_algorithm, ""))
		heuristic_alg = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(heuristic_algorithm, "t"))
		heuristic_alg = E_TAXICAB;
	else if (!ft_strcmp(heuristic_algorithm, "h"))
		heuristic_alg = E_HAMMING;
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", algorithm_string,
			"Specify a valid algorithm with the param -A");
	return (heuristic_alg);
}
