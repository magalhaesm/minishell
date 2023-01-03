/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 09:29:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/03 15:03:34 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	enqueue(long pid, t_context *ctx)
{
	ft_lstadd_back(&ctx->proc_queue, ft_lstnew((void *)pid));
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
