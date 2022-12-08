/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:36:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/08 18:17:02 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// cmd_prefix -> io_redirect cmd_prefix_null
t_node	*cmd_prefix(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(IO_REDIRECT, scanner))
	{
		left = io_redirect(scanner);
		if (left)
		{
			node = cmd_prefix_null(scanner);
			return (make_subtree(node, left));
		}
	}
	syntax_error(scanner);
	return (NULL);
}

// cmd_prefix_null -> io_redirect cmd_prefix_null
//                  | empty
t_node	*cmd_prefix_null(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(IO_REDIRECT, scanner))
	{
		left = io_redirect(scanner);
		if (left)
		{
			node = cmd_prefix_null(scanner);
			return (make_subtree(node, left));
		}
	}
	return (NULL);
}

// cmd_suffix -> io_redirect cmd_suffix_null
//             | WORD cmd_suffix_null
t_node	*cmd_suffix(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(IO_REDIRECT, scanner))
	{
		left = io_redirect(scanner);
		if (left)
		{
			node = cmd_suffix_null(scanner);
			return (make_subtree(node, left));
		}
	}
	if (peek(scanner).type == TOKEN_WORD)
	{
		left = mkleaf(next(scanner));
		node = cmd_suffix_null(scanner);
		return (make_subtree(node, left));
	}
	syntax_error(scanner);
	return (NULL);
}

// cmd_suffix_null -> io_redirect cmd_suffix_null
//                  | WORD cmd_suffix_null
//                  | empty
t_node	*cmd_suffix_null(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(IO_REDIRECT, scanner))
	{
		left = io_redirect(scanner);
		if (left)
		{
			node = cmd_suffix_null(scanner);
			return (make_subtree(node, left));
		}
	}
	if (peek(scanner).type == TOKEN_WORD)
	{
		left = mkleaf(next(scanner));
		node = cmd_suffix_null(scanner);
		return (make_subtree(node, left));
	}
	return (NULL);
}

// redirect_list -> io_redirect redirect_list_null
t_node	*redirect_list(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(IO_REDIRECT, scanner))
	{
		left = io_redirect(scanner);
		if (left)
		{
			node = redirect_list_null(scanner);
			return (make_subtree(node, left));
		}
	}
	syntax_error(scanner);
	return (NULL);
}
