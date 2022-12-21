/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:36:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/13 22:09:39 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// fcmd_prefix -> WORD word_null
//              | empty
t_node	*fcmd_prefix(t_scanner *scanner)
{
	t_node	*parent;
	t_node	*child;

	if (peek(scanner).type == TOKEN_WORD)
	{
		parent = mkleaf(next(scanner));
		child = word_null(scanner);
		return (subtree(parent, child));
	}
	return (NULL);
}

// cmd_prefix -> io_redirect cmd_prefix_null
t_node	*cmd_prefix(t_scanner *scanner)
{
	t_node	*parent;
	t_node	*child;

	if (first_set(IO_REDIRECT, scanner))
	{
		parent = io_redirect(scanner);
		if (parent)
		{
			child = cmd_prefix_null(scanner);
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
	t_node	*parent;
	t_node	*child;

	if (first_set(IO_REDIRECT, scanner))
	{
		parent = io_redirect(scanner);
		if (parent)
		{
			child = cmd_prefix_null(scanner);
			return (subtree(parent, child));
		}
	}
	return (NULL);
}

// cmd_suffix -> io_redirect cmd_suffix_null
//             | WORD cmd_suffix_null
t_node	*cmd_suffix(t_scanner *scanner)
{
	t_node	*parent;
	t_node	*child;

	if (first_set(IO_REDIRECT, scanner))
	{
		parent = io_redirect(scanner);
		if (parent)
		{
			child = cmd_suffix_null(scanner);
			return (subtree(parent, child));
		}
	}
	if (peek(scanner).type == TOKEN_WORD)
	{
		parent = mkleaf(next(scanner));
		child = cmd_suffix_null(scanner);
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
	t_node	*parent;
	t_node	*child;

	if (first_set(IO_REDIRECT, scanner))
	{
		parent = io_redirect(scanner);
		if (parent)
		{
			child = cmd_suffix_null(scanner);
			return (subtree(parent, child));
		}
	}
	if (peek(scanner).type == TOKEN_WORD)
	{
		parent = mkleaf(next(scanner));
		child = cmd_suffix_null(scanner);
		return (subtree(parent, child));
	}
	return (NULL);
}
