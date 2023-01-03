/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:17:47 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/03 09:57:16 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "exec.h"

#define FAILED 2

t_node	*parse(t_scanner *scanner)
{
	t_node	*root;

	if (peek(scanner).type == TOKEN_EOF)
	{
		set_exit_status(EXIT_SUCCESS);
		return (NULL);
	}
	root = list(scanner);
	if (peek(scanner).type != TOKEN_EOF)
	{
		syntax_error(scanner);
		free_tree(root);
		set_exit_status(FAILED);
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
