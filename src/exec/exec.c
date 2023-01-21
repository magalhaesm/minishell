/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:46:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/21 18:19:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "events.h"

static void	report_sigterm(int wstatus);
static void	set_wstatus(int wstatus, t_context *ctx);

t_bool	execute(t_node *root)
{
	t_context	ctx;

	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.fd_close = -1;
	ctx.retcode = *get_exit_status();
	ctx.error = FALSE;
	ctx.quit = FALSE;
	ctx.proc = 0;
	ctx.pipeline = FALSE;
	ft_memset(ctx.pid, 0, PIPE_LIMIT * sizeof(int));
	save_tree_ref(root);
	exec_node(root, &ctx);
	reaper(&ctx);
	wait_user_signals();
	set_exit_status(ctx.retcode);
	return (ctx.quit);
}

void	exec_node(t_node *node, t_context *ctx)
{
	if (node == NULL || ctx->error)
		return ;
	if (node->type == COMMAND)
		exec_command(node, ctx);
	else if (node->type == INPUT)
		exec_input(node, ctx);
	else if (node->type == OUTPUT)
		exec_output(node, ctx);
	else if (node->type == APPEND)
		exec_append(node, ctx);
	else if (node->type == PIPE)
		exec_pipe(node, ctx);
	else if (node->type == AND)
		exec_and(node, ctx);
	else if (node->type == OR)
		exec_or(node, ctx);
	else if (node->type == HERE_DOC)
		exec_heredoc(node, ctx);
	else if (node->type == SUBSHELL)
		exec_subshell(node, ctx);
	return ;
}

void	reaper(t_context *ctx)
{
	int	it;
	int	wstatus;

	it = 0;
	wstatus = 0;
	while (ctx->pid[it] != 0)
	{
		waitpid(ctx->pid[it], &wstatus, 0);
		ctx->pid[it] = 0;
		ctx->proc--;
		it++;
	}
	if (ctx->error == TRUE || ctx->retcode)
		return ;
	set_wstatus(wstatus, ctx);
}

static void	set_wstatus(int wstatus, t_context *ctx)
{
	if (WIFEXITED(wstatus))
		ctx->retcode = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		ctx->retcode = WTERMSIG(wstatus);
		if (ctx->retcode == 11)
			report_sigterm(wstatus);
		ctx->retcode += 128;
	}
}

static void	report_sigterm(int wstatus)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Process finished with exit code ", STDERR_FILENO);
	ft_putnbr_fd(wstatus, STDERR_FILENO);
	ft_putstr_fd(" (interrupted by signal ", STDERR_FILENO);
	ft_putnbr_fd(WTERMSIG(wstatus), STDERR_FILENO);
	ft_putendl_fd(")", STDERR_FILENO);
}
