/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:34:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/04 17:38:31 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*and_or(t_node_type type, t_node *pipe, t_node *logical);

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
		return (and_or(AND, pipe, logical));
	}
	if (match(TOKEN_OR, scanner))
	{
		pipe = pipeline(scanner);
		logical = conditional(scanner);
		return (and_or(OR, pipe, logical));
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

static t_node	*and_or(t_node_type type, t_node *pipe, t_node *logical)
{
	t_node	*aux;

	if (logical)
	{
		aux = logical;
		while (aux->data.pair.left)
			aux = aux->data.pair.left;
		aux->data.pair.left = mknode(type, NULL, pipe);
		return (logical);
	}
	return (mknode(type, NULL, pipe));
}
