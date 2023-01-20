/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:06:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/20 16:47:16 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define GREEN_PROMPT "\e[m\e[1;32m❯ \e[m"

static void	msh_loop(void);
static void	prompt_logo(void);

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	prompt_logo();
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

static void	prompt_logo(void)
{
	printf("-------------------------------------" \
			"-----------------------------------------------\n\n" \
			"              ______              _____  " \
			"     _________      __________       _____ \n" \
			"___   _______ ___  /______ __________(_)_________" \
			"___  /_____ ___  /__(_)________  /_\n" \
			"__ | / /  __ `/_  /__  __ `/_  ___/_  /__  __ \\ " \
			" __  /_  __ `/_  /__  /__  ___/  __/\n" \
			"__ |/ // /_/ /_  / _  /_/ /_  /   _  / _  / / / /" \
			"_/ / / /_/ /_  / _  / _(__  )/ /_  \n" \
			"_____/ \\__,_/ /_/  _\\__, / /_/    /_/  /_/ /_/" \
			"\\__,_/  \\__,_/ /_/  /_/  /____/ \\__/  \n" \
			"                   /____/                        " \
			"                                   \n\n" \
			"-------------------------------------------------" \
			"-----------------------------------\n" \
			"                       by Marcelo Magalhães & Ygo" \
			"r Sena, 2023                       \n" \
			"-------------------------------------------------" \
			"-----------------------------------\n\n");
}
