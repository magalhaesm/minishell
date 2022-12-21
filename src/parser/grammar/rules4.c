/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:37:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/14 00:52:23 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// redirect_list -> io_redirect redirect_list_null
t_node	*redirect_list(t_scanner *scanner)
{
	t_node	*parent;
	t_node	*child;

	if (first_set(IO_REDIRECT, scanner))
	{
		parent = io_redirect(scanner);
		if (parent)
		{
			child = redirect_list_null(scanner);
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
	t_node	*parent;
	t_node	*child;

	if (first_set(IO_REDIRECT, scanner))
	{
		parent = io_redirect(scanner);
		if (parent)
		{
			child = redirect_list_null(scanner);
			return (subtree(parent, child));
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
