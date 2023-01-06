/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:43:36 by ygorgsena         #+#    #+#             */
/*   Updated: 2023/01/06 09:15:02 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig_func.h"

void	show_new_prompt(int sig)
{
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_exit_status(128 + sig);
}

void	exit_heredoc(int sig)
{
	(void) sig;
	set_exit_status(128 + sig);
	write (1, "\n", 1);
	exit(128 + sig);
}
