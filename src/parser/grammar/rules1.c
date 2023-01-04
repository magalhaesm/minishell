/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:34:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/04 08:06:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// list -> pipeline conditional
t_node	*list(t_scanner *scanner)
{
	t_node	*pipe;
	t_node	*logical;
	t_node	*aux;

	if (first_set(PIPELINE, scanner))
	{
		pipe = pipeline(scanner);
		if (pipe)
		{
			logical = conditional(scanner);
			if (logical)
			{
				aux = logical;
				while (aux->data.pair.left)
					aux = aux->data.pair.left;
				aux->data.pair.left = pipe;
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
			return (mknode(logical->type, mknode(AND, NULL, pipe), logical));
		return (mknode(AND, NULL, pipe));
	}
	if (match(TOKEN_OR, scanner))
	{
		pipe = pipeline(scanner);
		logical = conditional(scanner);
		if (logical)
			return (mknode(logical->type, mknode(OR, NULL, pipe), logical));
		return (mknode(OR, NULL, pipe));
	}
	return (NULL);
}

// pipeline -> command pipeline_null
t_node	*pipeline(t_scanner *scanner)
{
	t_node	*parent;
	t_node	*child;

	parent = command(scanner);
	if (parent)
	{
		child = pipeline_null(scanner);
		if (child && child->data.pair.left == NULL)
		{
			child->data.pair.left = parent;
			return (child);
		}
		return (subtree(parent, child));
	}
	syntax_error(scanner);
	return (NULL);
}

// command -> simple_cmd
//          | subshell subshell_redir
t_node	*command(t_scanner *scanner)
{
	t_node	*parent;
	t_node	*child;

	if (first_set(SIMPLE_CMD, scanner))
	{
		parent = simple_cmd(scanner);
		if (parent)
			return (parent);
	}
	child = subshell(scanner);
	if (child)
	{
		parent = subshell_redir(scanner);
		if (parent == NULL)
			return (child);
		return (subtree(parent, child));
	}
	syntax_error(scanner);
	return (NULL);
}
