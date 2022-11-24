/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/24 11:35:51 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char *cmdline);

int	main(void)
{
	char	*cmdline;

	cmdline = "";
	wait_user_signals();
	while (cmdline)
	{
		cmdline = readline("> ");
		if (cmdline)
		{
			if (*cmdline)
				add_history(cmdline);
			print_tokens(cmdline);
			printf("command: %s\n", cmdline);
			free(cmdline);
		}
	}
	rl_clear_history();
	ft_printf("exit\n");
}

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
