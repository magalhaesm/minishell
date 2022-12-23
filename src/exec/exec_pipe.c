/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:30:25 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/22 20:29:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_pipe(t_node *node, t_context *ctx)
{
	int			pfd[2];
	t_context	aux_ctx;
	t_node		*rhs;
	t_node		*lhs;
	int			children;

	children = 0;
	pipe(pfd);
	lhs = node->data.pair.left;
	aux_ctx = *ctx;
	aux_ctx.fd[STDOUT_FILENO] = pfd[STDOUT_FILENO];
	aux_ctx.fd_close = pfd[STDIN_FILENO];
	children += exec_node(lhs, &aux_ctx);
	rhs = node->data.pair.right;
	aux_ctx = *ctx;
	aux_ctx.fd[STDIN_FILENO] = pfd[STDIN_FILENO];
	aux_ctx.fd_close = pfd[STDOUT_FILENO];
	children += exec_node(rhs, &aux_ctx);
	close(pfd[STDIN_FILENO]);
	close(pfd[STDOUT_FILENO]);
	return (children);
}
