/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/20 15:36:40 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	msh_loop(void);
void		print_tree(t_node *root, int indentation);

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	wait_user_signals();
	init_environ(envp);
	msh_loop();
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
			print_tree(root, 0);
			free_tree(root);
			free(cmdline);
		}
	}
}
