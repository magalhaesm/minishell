/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:34:00 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:25:41 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	list(t_scanner *scanner)
{
	pipeline(scanner);
	conditional(scanner);
	return (TRUE);
}

// conditional : AND pipeline conditional | OR pipeline conditional | ε
t_bool	conditional(t_scanner *scanner)
{
	if (match(TOKEN_AND, scanner))
	{
		if (pipeline(scanner) && conditional(scanner))
			return (TRUE);
		else
			syntax_error(scanner);
	}
	else if (match(TOKEN_OR, scanner))
	{
		if (pipeline(scanner) && conditional(scanner))
			return (TRUE);
		else
			syntax_error(scanner);
	}
	return (TRUE);
}

// pipeline : command fcommand
t_bool	pipeline(t_scanner *scanner)
{
	if (command(scanner) && null_command(scanner))
		return (TRUE);
	return (FALSE);
}

// command : simple_cmd | subshell fsubshell
t_bool	command(t_scanner *scanner)
{
	if (simple_cmd(scanner))
		return (TRUE);
	else if (subshell(scanner) && null_subshell(scanner))
		return (TRUE);
	return (FALSE);
}
