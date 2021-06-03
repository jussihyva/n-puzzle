/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heuristic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:30:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/06/03 17:33:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_puzzle.h"

char	*based_on_heuristic_alg(t_heuristic_alg algorithm)
{
	char		*algorithm_substring;

	algorithm_substring = NULL;
	if (algorithm == E_TAXICAB)
		algorithm_substring = ft_strdup("taxicab");
	return (algorithm_substring);
}

t_heuristic_alg	validate_heuristic_algorithm(char *algorithm_string)
{
	t_heuristic_alg		heuristic_algorithm;

	heuristic_algorithm = E_NO_HEURISTIC_ALG;
	if (!ft_strcmp(algorithm_string, "dfs_1"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "dfs_2"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "dfs_3"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "bfs_1"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "bfs_2"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "toop_1"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "a_star_t"))
		heuristic_algorithm = E_NO_HEURISTIC_ALG;
	else if (!ft_strcmp(algorithm_string, "ida*"))
		heuristic_algorithm = E_TAXICAB;
	else
		FT_LOG_ERROR("Unknown algorithm: %s. %s", algorithm_string,
			"Specify a valid algorithm with the param -A");
	return (heuristic_algorithm);
}
