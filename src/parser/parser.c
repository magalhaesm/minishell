/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:17:47 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:24:00 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse(t_scanner *scanner)
{
	list(scanner);
	if (peek(scanner).type != TOKEN_EOF)
		syntax_error(scanner);
}

t_bool	match(t_token_type type, t_scanner *scanner)
{
	if (peek(scanner).type == type)
	{
		next(scanner);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	consume(t_token_type type, t_scanner *scanner)
{
	if (match(type, scanner))
		return (TRUE);
	syntax_error(scanner);
	return (FALSE);
}
