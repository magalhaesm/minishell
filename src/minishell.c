/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/08 11:08:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int	main(void)
{
	char	*cmdline;

	cmdline = "";
	while (cmdline)
	{
		cmdline = readline("> ");
		if (cmdline)
		{
			printf("command: %s\n", cmdline);
			free(cmdline);
		}
	}
}
