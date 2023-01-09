/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:46:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/08 21:23:21 by mdias-ma         ###   ########.fr       */
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
	ctx.proc_queue = NULL;
	save_tree_ref(root);
	exec_node(root, &ctx);
	reaper(&ctx);
	set_exit_status(ctx.retcode);
	return (ctx.quit);
}

void	exec_node(t_node *node, t_context *ctx)
{
	wait_user_signals();
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
	int		wstatus;
	t_list	*proc;
	t_list	*aux;

	proc = ctx->proc_queue;
	while (proc)
	{
		waitpid((long)proc->content, &wstatus, 0);
		aux = proc;
		proc = proc->next;
		free(aux);
	}
	set_wstatus(wstatus, ctx);
	ctx->proc_queue = NULL;
}

static void	set_wstatus(int wstatus, t_context *ctx)
{
	if (ctx->proc_queue == NULL)
		return ;
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
