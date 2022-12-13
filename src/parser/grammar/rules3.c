/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:36:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 20:31:01 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

// cmd_prefix -> io_redirect cmd_prefix_null
t_node	*cmd_prefix(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (first_set(IO_REDIRECT, scanner))
	{
		child = io_redirect(scanner);
		if (child)
		{
			parent = cmd_prefix_null(scanner);
			return (subtree(parent, child));
		}
	}
	syntax_error(scanner);
	return (NULL);
}

// cmd_prefix_null -> io_redirect cmd_prefix_null
//                  | empty
t_node	*cmd_prefix_null(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (first_set(IO_REDIRECT, scanner))
	{
		child = io_redirect(scanner);
		if (child)
		{
			parent = cmd_prefix_null(scanner);
			return (subtree(parent, child));
		}
	}
	return (NULL);
}

// cmd_suffix -> io_redirect cmd_suffix_null
//             | WORD cmd_suffix_null
t_node	*cmd_suffix(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (first_set(IO_REDIRECT, scanner))
	{
		child = io_redirect(scanner);
		if (child)
		{
			parent = cmd_suffix_null(scanner);
			return (subtree(parent, child));
		}
	}
	if (peek(scanner).type == TOKEN_WORD)
	{
		child = mkleaf(next(scanner));
		parent = cmd_suffix_null(scanner);
		return (subtree(parent, child));
	}
	syntax_error(scanner);
	return (NULL);
}

// cmd_suffix_null -> io_redirect cmd_suffix_null
//                  | WORD cmd_suffix_null
//                  | empty
t_node	*cmd_suffix_null(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (first_set(IO_REDIRECT, scanner))
	{
		child = io_redirect(scanner);
		if (child)
		{
			parent = cmd_suffix_null(scanner);
			return (subtree(parent, child));
		}
	}
	if (peek(scanner).type == TOKEN_WORD)
	{
		child = mkleaf(next(scanner));
		parent = cmd_suffix_null(scanner);
		return (subtree(parent, child));
	}
	return (NULL);
}
