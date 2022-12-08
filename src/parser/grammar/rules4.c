/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:37:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/08 18:17:07 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_node	*mkio(t_node_type type, t_token_type tk, t_scanner *scanner);

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
			return (make_subtree(node, left));
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

// io_file -> LESS WORD
//          | GREAT WORD
//          | DGREAT WORD
t_node	*io_file(t_scanner *scanner)
{
	if (match(TOKEN_LESS, scanner))
		return (mkio(INPUT, TOKEN_WORD, scanner));
	if (match(TOKEN_GREAT, scanner))
		return (mkio(OUTPUT, TOKEN_WORD, scanner));
	if (match(TOKEN_DGREAT, scanner))
		return (mkio(APPEND, TOKEN_WORD, scanner));
	return (NULL);
}

// io_here -> DLESS WORD
t_node	*io_here(t_scanner *scanner)
{
	if (match(TOKEN_DLESS, scanner))
		return (mkio(HERE_DOC, TOKEN_WORD, scanner));
	return (NULL);
}

static t_node	*mkio(t_node_type type, t_token_type tk, t_scanner *scanner)
{
	t_node	*right;

	if (peek(scanner).type == tk)
	{
		right = mkleaf(next(scanner));
		return (mknode(type, NULL, right));
	}
	syntax_error(scanner);
	return (NULL);
}
