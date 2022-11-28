/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:36:49 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:25:18 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// fcmd_prefix : ε | WORD fword1
t_bool	fcmd_prefix(t_scanner *scanner)
{
	if (match(TOKEN_WORD, scanner) && null_word(scanner))
		return (TRUE);
	return (TRUE);
}

// cmd_prefix : io_redirect cmd_prefix1
t_bool	cmd_prefix(t_scanner *scanner)
{
	return (io_redirect(scanner) && null_cmd_prefix(scanner));
}

// cmd_prefix1 : io_redirect cmd_prefix1 | ε
t_bool	null_cmd_prefix(t_scanner *scanner)
{
	if (io_redirect(scanner) && null_cmd_prefix(scanner))
		return (TRUE);
	return (TRUE);
}

// cmd_suffix : io_redirect cmd_suffix1 | WORD cmd_suffix1
t_bool	cmd_suffix(t_scanner *scanner)
{
	if (io_redirect(scanner) && null_cmd_suffix(scanner))
		return (TRUE);
	if (match(TOKEN_WORD, scanner) && null_cmd_suffix(scanner))
		return (TRUE);
	return (FALSE);
}

// cmd_suffix1 : io_redirect cmd_suffix1 | WORD cmd_suffix1 | ε
t_bool	null_cmd_suffix(t_scanner *scanner)
{
	if (io_redirect(scanner) && null_cmd_suffix(scanner))
		return (TRUE);
	if (match(TOKEN_WORD, scanner) && null_cmd_suffix(scanner))
		return (TRUE);
	return (TRUE);
}
