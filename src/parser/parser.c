/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:17:47 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 13:01:44 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_node	*parse(t_scanner *scanner)
{
	t_node	*root;

	if (peek(scanner).type == TOKEN_EOF)
		return (NULL);
	root = list(scanner);
	if (peek(scanner).type != TOKEN_EOF)
	{
		syntax_error(scanner);
		free_tree(root);
		return (NULL);
	}
	return (root);
}

t_bool	match(t_token_type type, t_scanner *scanner)
{
	if (peek(scanner).type == type)
	{
		next(scanner);
		return (TRUE);
	}
	return (FALSE);
}
