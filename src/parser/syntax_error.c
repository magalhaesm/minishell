/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 18:21:22 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/23 19:17:06 by mdias-ma         ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (token.type == TOKEN_ERROR)
		show(token);
	else
	{
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
		ft_putchar_fd('`', STDERR_FILENO);
		if (token.type == TOKEN_EOF)
			ft_putstr_fd("newline", STDERR_FILENO);
		else
			show(token);
		ft_putchar_fd('\'', STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	scanner->next.type = TOKEN_UNKNOWN;
}

static void	show(t_token token)
{
	write(STDERR_FILENO, token.start, token.length);
}
