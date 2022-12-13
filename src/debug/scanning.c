/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:56:19 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 13:56:47 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

void	print_tokens(char *cmdline)
{
	t_token		token;
	t_scanner	scanner;

	scanner = init_scanner(cmdline);
	while (has_next(&scanner))
	{
		token = next(&scanner);
		ft_printf("token: %2d - lexema: ", token.type);
		write(STDOUT_FILENO, token.start, token.length);
		write(STDOUT_FILENO, "\n", 2);
	}
}
