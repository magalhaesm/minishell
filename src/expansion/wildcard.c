/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 22:10:17 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 15:08:59 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void		is_first(t_regex *regex, char *pattern);
static t_bool	**alloc_table(t_regex *regex);
static void		match_expr(t_regex *regex,
					t_bool **dp_arr, char *eval, char *pattern);

t_bool	is_match(char *eval, char *pattern)
{
	t_regex	regex;
	t_bool	result;
	t_bool	**dp_arr;

	init_regex(&regex, eval, pattern);
	is_first(&regex, pattern);
	dp_arr = alloc_table(&regex);
	if (regex.write_index > 0 && pattern[0] == '*')
		dp_arr[0][1] = TRUE;
	dp_arr[0][0] = TRUE;
	match_expr(&regex, dp_arr, eval, pattern);
	result = dp_arr[regex.eval_size][regex.write_index];
	free_dparr(dp_arr, regex.eval_size + 1);
	return (result);
}

static void	is_first(t_regex *regex, char *pattern)
{
	size_t	i;

	i = 0;
	while (i < regex->pattern_size)
	{
		if (pattern[i] == '*')
		{
			if (regex->is_first)
			{
				pattern[regex->write_index++] = pattern[i];
				regex->is_first = FALSE;
			}
		}
		else
		{
			pattern[regex->write_index++] = pattern[i];
			regex->is_first = TRUE;
		}
		i++;
	}
}

static t_bool	**alloc_table(t_regex *regex)
{
	t_bool	**dp_arr;
	size_t	index;

	dp_arr = ft_calloc(regex->eval_size + 1, sizeof(t_bool *));
	index = 0;
	while (index < regex->eval_size + 1)
	{
		dp_arr[index]
			= ft_calloc(regex->write_index + 1, sizeof(t_bool));
		index++;
	}
	return (dp_arr);
}

static void	match_expr(t_regex *regex,
			t_bool **dp_arr, char *eval, char *pattern)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < regex->eval_size + 1)
	{
		j = 1;
		while (j < regex->write_index + 1)
		{
			if (pattern[j - 1] == '?' || eval[i - 1] == pattern[j - 1])
				dp_arr[i][j] = dp_arr[i - 1][j - 1];
			else if (pattern[j - 1] == '*')
				dp_arr[i][j] = (dp_arr[i - 1][j] || dp_arr[i][j - 1]);
			j++;
		}
		i++;
	}
}
