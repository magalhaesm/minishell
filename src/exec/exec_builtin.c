/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 10:20:33 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/19 11:14:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "events.h"

static void	forked_builtin(char **argv, t_builtin builtin, t_context *ctx);

t_bool	exec_builtin(char **argv, t_context *ctx)
{
	int			saved_fd[2];
	t_bool		is_builtin;
	t_builtin	builtin;

	is_builtin = FALSE;
	builtin = builtin_pool(argv[0], ctx);
	if (builtin)
	{
		is_builtin = TRUE;
		if (ctx->pipeline)
			forked_builtin(argv, builtin, ctx);
		else
		{
			redirect_io(saved_fd, ctx);
			ctx->retcode = builtin(argv);
			restore_io(saved_fd);
		}
	}
	return (is_builtin);
}

static void	forked_builtin(char **argv, t_builtin builtin, t_context *ctx)
{
	int	pid;

	wait_child_signals();
	pid = pfork();
	if (pid == FORKED_CHILD)
	{
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		ctx->retcode = builtin(argv);
		free_strtab(argv);
		msh_clean();
		close(ctx->fd[STDIN_FILENO]);
		close(ctx->fd[STDOUT_FILENO]);
		exit(ctx->retcode);
	}
	wait_user_signals();
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		close(ctx->fd[STDIN_FILENO]);
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx->fd[STDOUT_FILENO]);
	enqueue(pid, ctx);
}
