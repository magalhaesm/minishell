/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/14 16:56:03 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			printf("command: %s\n", cmdline);
			free(cmdline);
		}
	}
	rl_clear_history();
	ft_printf("exit\n");
}
