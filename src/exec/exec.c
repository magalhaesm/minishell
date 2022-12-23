/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:46:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/22 20:51:09 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	report_sigterm(int wstatus);
void	reaper(int zombies, t_context *ctx);

void	execute(t_node *root)
{
	t_context	ctx;
	int			children;

	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.fd_close = -1;
	ctx.retcode = parse_status();
	ctx.error = FALSE;
	children = exec_node(root, &ctx);
	if (children)
		reaper(children, &ctx);
}

int	exec_node(t_node *node, t_context *ctx)
{
	if (node == NULL)
		return (0);
	if (ctx->error)
		return (0);
	if (node->type == COMMAND)
		return (exec_command(node, ctx));
	else if (node->type == INPUT)
		return (exec_input(node, ctx));
	else if (node->type == OUTPUT)
		return (exec_output(node, ctx));
	else if (node->type == APPEND)
		return (exec_append(node, ctx));
	else if (node->type == PIPE)
		return (exec_pipe(node, ctx));
	return (0);
}

void	reaper(int zombies, t_context *ctx)
{
	int	wstatus;

	while (zombies--)
		wait(&wstatus);
	if (WIFEXITED(wstatus))
		ctx->retcode = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		ctx->retcode = wstatus;
		report_sigterm(wstatus);
	}
}

void	report_sigterm(int wstatus)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Process finished with exit code ", STDERR_FILENO);
	ft_putnbr_fd(wstatus, STDERR_FILENO);
	ft_putstr_fd(" (interrupted by signal ", STDERR_FILENO);
	ft_putnbr_fd(WTERMSIG(wstatus), STDERR_FILENO);
	ft_putendl_fd(")", STDERR_FILENO);
}
