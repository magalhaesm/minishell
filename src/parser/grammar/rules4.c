/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:37:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 20:31:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// redirect_list -> io_redirect redirect_list_null
t_node	*redirect_list(t_scanner *scanner)
{
	t_node	*child;
	t_node	*parent;

	if (first_set(IO_REDIRECT, scanner))
	{
		child = io_redirect(scanner);
		if (child)
		{
			parent = redirect_list_null(scanner);
			return (subtree(parent, child));
		}
	}
	syntax_error(scanner);
	return (NULL);
}

// redirect_list_null -> io_redirect redirect_list_null
//                     | empty
t_node	*redirect_list_null(t_scanner *scanner)
{
	t_node	*left;
	t_node	*node;

	if (first_set(IO_REDIRECT, scanner))
	{
		left = io_redirect(scanner);
		if (left)
		{
			node = redirect_list_null(scanner);
			return (subtree(node, left));
		}
	}
	return (NULL);
}

// io_redirect -> io_file
//              | io_here
t_node	*io_redirect(t_scanner *scanner)
{
	if (first_set(IO_FILE, scanner))
		return (io_file(scanner));
	return (io_here(scanner));
}
