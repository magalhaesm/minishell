/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygorgsena <ygorgsena@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:43:36 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/11/09 09:49:31 by ygorgsena        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* TODO: configure a variable to save EXIT_STATUS value.
		Here, according to bash docs, is 128 + 2 (SIGINT value) = 130 */
void	show_new_prompt(int sig)
{
	(void) sig;
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* //TODO: function to be created
void	exit_heredoc(int sig)
{
	(void) sig;
	// Maybe leaks will occur. Check signals before use 
	close(STDIN_FILENO);
} */
