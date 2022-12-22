/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:04:58 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 15:57:11 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "libft.h"
# include "helpers.h"

typedef struct s_regex
{
	size_t	eval_size;
	size_t	pattern_size;
	size_t	write_index;
	t_bool	is_first;
}	t_regex;

/**
 * @brief This function compares two strings and returns TURE or FALSE.
 * The second argument is the pattern to search (i.e. val*ind) and the
 * first argument is the string to be evaluated (i.e. valgrind). Here,
 * valgrind is a possible pattern for val*ind. Hence, t_bool is TRUE;
 */
t_bool	is_match(char *eval, char *pattern);
void	init_regex(t_regex *regex, char *eval, char *pattern);
void	free_dparr(t_bool **split, size_t length);

#endif