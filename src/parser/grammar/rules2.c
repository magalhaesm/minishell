/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:35:41 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:25:40 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// fcommand :  ε | PIPE pipeline
t_bool	null_command(t_scanner *scanner)
{
	if (match(TOKEN_PIPE, scanner))
	{
		if (pipeline(scanner))
			return (TRUE);
		else
			syntax_error(scanner);
	}
	return (TRUE);
}

// subshell : LBRACE list RBRACE
t_bool	subshell(t_scanner *scanner)
{
	if (match(TOKEN_LEFT_PAREN, scanner))
	{
		list(scanner);
		return (consume(TOKEN_RIGHT_PAREN, scanner));
	}
	return (FALSE);
}

// fsubshell : ε | redirect_list
t_bool	null_subshell(t_scanner *scanner)
{
	redirect_list(scanner);
	return (TRUE);
}

// simple_cmd : WORD fword | cmd_prefix fcmd_prefix
t_bool	simple_cmd(t_scanner *scanner)
{
	if (match(TOKEN_WORD, scanner))
		return (null_word(scanner));
	else if (cmd_prefix(scanner) && fcmd_prefix(scanner))
		return (TRUE);
	return (FALSE);
}

// fword : ε | cmd_suffix
t_bool	null_word(t_scanner *scanner)
{
	cmd_suffix(scanner);
	return (TRUE);
}
