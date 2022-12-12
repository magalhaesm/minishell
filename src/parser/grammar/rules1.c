/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:34:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 10:19:19 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// list -> pipeline conditional
t_node	*list(t_scanner *scanner)
{
	t_node	*pipe;
	t_node	*logical;

	if (first_set(PIPELINE, scanner))
	{
		pipe = pipeline(scanner);
		if (pipe)
		{
			logical = conditional(scanner);
			if (logical)
			{
				logical->data.pair.left = pipe;
				return (logical);
			}
			return (pipe);
		}
	}
	syntax_error(scanner);
	return (NULL);
}

// conditional -> AND pipeline conditional
//              | OR pipeline conditional
//              | empty
t_node	*conditional(t_scanner *scanner)
{
	t_node	*pipe;
	t_node	*logical;

	if (match(TOKEN_AND, scanner))
	{
		pipe = pipeline(scanner);
		logical = conditional(scanner);
		if (logical)
			return (mknode(AND, pipe, logical));
		return (mknode(AND, NULL, pipe));
	}
	if (match(TOKEN_OR, scanner))
	{
		pipe = pipeline(scanner);
		logical = conditional(scanner);
		if (logical)
			return (mknode(OR, pipe, logical));
		return (mknode(OR, NULL, pipe));
	}
	return (NULL);
}

// pipeline -> command pipeline_null
t_node	*pipeline(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	child = command(scanner);
	if (child)
	{
		parent = pipeline_null(scanner);
		return (subtree(parent, child));
	}
	syntax_error(scanner);
	return (NULL);
}

// command -> simple_cmd
//          | subshell subshell_null
t_node	*command(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (first_set(SIMPLE_CMD, scanner))
	{
		child = simple_cmd(scanner);
		if (child)
			return (child);
	}
	child = subshell(scanner);
	if (child)
	{
		parent = subshell_null(scanner);
		return (subtree(parent, child));
	}
	syntax_error(scanner);
	return (NULL);
}

// pipeline_null -> PIPE pipeline
//                | empty
t_node	*pipeline_null(t_scanner *scanner)
{
	t_node	*child;

	if (match(TOKEN_PIPE, scanner))
	{
		child = pipeline(scanner);
		if (child)
			return (mknode(PIPE, NULL, child));
	}
	return (NULL);
}
