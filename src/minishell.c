/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2024/06/06 13:33:31 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define GREEN_PROMPT "\001\e[m\e[1;32m❯ \e[m\002"

static void	msh_loop(void);

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	wait_user_signals();
	init_environ(envp);
	init_pathtab();
	msh_loop();
	free_pathtab();
	free_environ();
	rl_clear_history();
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (*get_exit_status());
}

static void	msh_loop(void)
{
	t_bool		quit;
	char		*cmdline;
	t_scanner	scanner;
	t_node		*root;

	cmdline = "";
	while (cmdline)
	{
		cmdline = readline(GREEN_PROMPT);
		if (cmdline)
		{
			if (*cmdline)
				add_history(cmdline);
			scanner = init_scanner(cmdline);
			root = parse(&scanner);
			quit = execute(root);
			free_tree(root);
			free(cmdline);
			if (quit)
				cmdline = NULL;
		}
	}
}
