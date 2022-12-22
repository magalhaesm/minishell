/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:36:45 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 15:11:04 by yde-goes         ###   ########.fr       */
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
