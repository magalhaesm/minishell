/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 16:11:28 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_printf("exit\n");
}

static void	msh_loop(void)
{
	char		*cmdline;
	t_scanner	scanner;
	t_node		*root;

	cmdline = "";
	while (cmdline)
	{
		cmdline = readline("> ");
		if (cmdline)
		{
			if (*cmdline)
				add_history(cmdline);
			scanner = init_scanner(cmdline);
			root = parse(&scanner);
			execute(root);
			free_tree(root);
			free(cmdline);
		}
	}
}
