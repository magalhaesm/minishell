/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:04:58 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/06 16:40:32 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <dirent.h>

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
 * @brief This function compares two strings and returns TRUE or FALSE.
 * The second argument is the pattern to search (i.e. val*ind) and the
 * first argument is the string to be evaluated (i.e. valgrind).
 * Here, valgrind is a possible pattern for val*ind. Hence, t_bool is TRUE. */
t_bool	is_match(char *eval, char *pattern);
void	init_regex(t_regex *regex, char *eval, char *pattern);
void	free_dparr(t_bool **split, size_t length);

/* Expand each string in the table.
 * Return the table with your modified values. */
char	**expand(char **cmdtab);

/* Expand each variable found in the string. Whether or not it finds a variable,
 * it always returns a copy of the original string. */
char	*variable_expansion(char *string);

/* Split a string by quotes. On success return a list of strings,
 * or null on error. */
t_list	*split_quotes(char *str);

/* Expand and remove quotes on each string in a list. */
void	parameter_expansion(t_list *list);

/* Join each string into a list. Return a complete string. */
char	*concatenate(t_list *list);

t_list	*pathname_expansion(t_list *chunks, t_bool glob);
t_list	*list_matches(char *pattern);
char	**table(t_list *list);
t_bool	has_pattern(t_list *list, char chr);
t_bool	empty_quotes(char *str);
void	unquote(t_list *list);

#endif
