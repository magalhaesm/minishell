/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:35:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 10:18:10 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// subshell -> LBRACE list RBRACE
t_node	*subshell(t_scanner *scanner)
{
	t_node	*parent;

	parent = NULL;
	if (match(TOKEN_LEFT_PAREN, scanner))
	{
		parent = list(scanner);
		if (parent && match(TOKEN_RIGHT_PAREN, scanner))
			return (mknode(SUBSHELL, parent, NULL));
	}
	syntax_error(scanner);
	return (parent);
}

// subshell_null -> redirect_list
//                | empty
t_node	*subshell_null(t_scanner *scanner)
{
	if (first_set(IO_REDIRECT, scanner))
		return (redirect_list(scanner));
	return (NULL);
}

// simple_cmd -> WORD word_null
//             | cmd_prefix fcmd_prefix
t_node	*simple_cmd(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (peek(scanner).type == TOKEN_WORD)
		return (word_null(scanner));
	if (first_set(CMD_PREFIX, scanner))
	{
		child = cmd_prefix(scanner);
		if (child)
		{
			parent = fcmd_prefix(scanner);
			return (subtree(parent, child));
		}
	}
	syntax_error(scanner);
	return (NULL);
}

// word_null -> cmd_suffix
//            | empty
t_node	*word_null(t_scanner *scanner)
{
	if (first_set(CMD_SUFFIX, scanner))
		return (cmd_suffix(scanner));
	return (NULL);
}

// fcmd_prefix -> WORD word_null
//              | empty
t_node	*fcmd_prefix(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (peek(scanner).type == TOKEN_WORD)
	{
		child = mkleaf(next(scanner));
		parent = word_null(scanner);
		return (subtree(parent, child));
	}
	return (NULL);
}
