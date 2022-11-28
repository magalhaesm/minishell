/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:37:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:25:06 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// redirect_list : io_redirect redirect_list1
t_bool	redirect_list(t_scanner *scanner)
{
	if (io_redirect(scanner) && null_redirect_list(scanner))
		return (TRUE);
	return (FALSE);
}

// redirect_list1 : io_redirect redirect_list1 | ε
t_bool	null_redirect_list(t_scanner *scanner)
{
	if (io_redirect(scanner) && null_redirect_list(scanner))
		return (TRUE);
	return (TRUE);
}

// io_redirect : io_file | io_here
t_bool	io_redirect(t_scanner *scanner)
{
	if (io_file(scanner))
		return (TRUE);
	if (io_here(scanner))
		return (TRUE);
	return (FALSE);
}

// io_file : LESS WORD | GREAT WORD | DGREAT WORD
t_bool	io_file(t_scanner *scanner)
{
	if (match(TOKEN_LESS, scanner))
		return (consume(TOKEN_WORD, scanner));
	else if (match(TOKEN_GREAT, scanner))
		return (consume(TOKEN_WORD, scanner));
	else if (match(TOKEN_DGREAT, scanner))
		return (consume(TOKEN_WORD, scanner));
	return (FALSE);
}

// io_here : DLESS WORD
t_bool	io_here(t_scanner *scanner)
{
	if (match(TOKEN_DLESS, scanner))
		return (consume(TOKEN_WORD, scanner));
	return (FALSE);
}
