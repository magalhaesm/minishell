/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:29:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/20 19:31:18 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	enqueue(long pid, t_context *ctx)
{
	ctx->pid[ctx->proc] = pid;
	ctx->proc += 1;
}

void	copy_queue(t_context *ctx, t_context aux)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ctx->proc = aux.proc;
	while (aux.pid[j] != 0)
	{
		ctx->pid[i] = aux.pid[j];
		i++;
		j++;
	}
}

void	redirect_io(int saved[], t_context *ctx)
{
	saved[STDIN_FILENO] = STDIN_FILENO;
	saved[STDOUT_FILENO] = STDOUT_FILENO;
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		saved[STDIN_FILENO] = dup(STDIN_FILENO);
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		close(ctx->fd[STDIN_FILENO]);
	}
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		saved[STDOUT_FILENO] = dup(STDOUT_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		close(ctx->fd[STDOUT_FILENO]);
	}
}

void	restore_io(int saved[])
{
	if (saved[STDIN_FILENO] != STDIN_FILENO)
	{
		dup2(saved[STDIN_FILENO], STDIN_FILENO);
		close(saved[STDIN_FILENO]);
	}
	if (saved[STDOUT_FILENO] != STDOUT_FILENO)
	{
		dup2(saved[STDOUT_FILENO], STDOUT_FILENO);
		close(saved[STDOUT_FILENO]);
	}
}
