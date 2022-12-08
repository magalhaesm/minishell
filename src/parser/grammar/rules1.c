/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:34:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/08 18:16:58 by mdias-ma         ###   ########.fr       */
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
	t_node	*left;
	t_node	*node;

	left = command(scanner);
	if (left)
	{
		node = pipeline_null(scanner);
		if (node)
			return (make_subtree(node, left));
		return (left);
	}
	syntax_error(scanner);
	return (NULL);
}

// command -> simple_cmd
//          | subshell subshell_null
t_node	*command(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(SIMPLE_CMD, scanner))
	{
		left = simple_cmd(scanner);
		if (left)
			return (left);
	}
	left = subshell(scanner);
	if (left)
	{
		node = subshell_null(scanner);
		return (make_subtree(node, left));
	}
	syntax_error(scanner);
	return (NULL);
}

// pipeline_null -> PIPE pipeline
//                | empty
t_node	*pipeline_null(t_scanner *scanner)
{
	t_node	*node;

	if (match(TOKEN_PIPE, scanner))
	{
		node = pipeline(scanner);
		if (node)
			return (mknode(PIPE, NULL, node));
	}
	return (NULL);
}
