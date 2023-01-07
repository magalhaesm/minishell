/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:03:29 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/07 07:29:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_subshell(t_node *node, t_context *ctx)
{
	int			pid;
	int			saved_fd[2];
	t_node		*list;
	t_context	aux_ctx;

	list = node->data.pair.left;
	redirect_io(saved_fd, ctx);
	aux_ctx = *ctx;
	pid = pfork();
	if (pid == FORKED_CHILD)
	{
		exec_node(list, &aux_ctx);
		restore_io(saved_fd);
		reaper(&aux_ctx);
		msh_clean();
		exit(aux_ctx.retcode);
	}
	restore_io(saved_fd);
	enqueue(pid, ctx);
	reaper(ctx);
}
