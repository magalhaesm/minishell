/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 21:20:40 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/01 17:48:11 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	init_regex(t_regex *regex, char *eval, char *pattern)
{
	regex->eval_size = ft_strlen(eval);
	regex->pattern_size = ft_strlen(pattern);
	regex->write_index = 0;
	regex->is_first = TRUE;
}

void	free_dparr(t_bool **split, size_t length)
{
	size_t	x;

	x = 0;
	while (x < length)
	{
		free(split[x]);
		x++;
	}
	free(split);
}
