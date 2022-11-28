/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:21:22 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/28 18:03:44 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	show(t_token token);

void	syntax_error(t_scanner *scanner)
{
	t_token	token;

	token = peek(scanner);
	if (token.type == TOKEN_UNKNOWN)
		return ;
	else if (token.type == TOKEN_ERROR)
		show(token);
	else
	{
		ft_printf("syntax error near unexpected token ");
		if (token.type == TOKEN_EOF)
			ft_printf("`newline'\n");
		else
			show(token);
	}
	scanner->next.type = TOKEN_UNKNOWN;
}

static void	show(t_token token)
{
	write(STDOUT_FILENO, "`", 1);
	write(STDOUT_FILENO, token.start, token.length);
	write(STDOUT_FILENO, "'\n", 3);
}
