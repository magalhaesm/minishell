/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:20:41 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/12/29 14:05:05 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig_func.h"

static t_handler	*ft_signal(int signum, t_handler *handler);

/* Signals of interactive bash */
void	wait_user_signals(void)
{
	ft_signal(SIGINT, show_new_prompt);
	ft_signal(SIGQUIT, SIG_IGN);
}

/* //TODO: think of a better name for function heredoc
//Signals of heredoc bash
void	heredoc(void)
{
	ft_signal(SIGINT, exit_heredoc);
	ft_signal(SIGQUIT, SIG_IGN);
} */

static t_handler	*ft_signal(int signum, t_handler *handler)
{
	struct sigaction	action;
	struct sigaction	old_action;

	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(signum, &action, &old_action) < 0)
		msh_error("ft_signal", "signal error", 0);
	return (old_action.sa_handler);
}
