/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:46:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 20:26:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute(t_node *root)
{
	t_context	ctx;

	ctx.fd[STDIN_FILENO] = STDIN_FILENO;
	ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
	ctx.retcode = parse_status();
	ctx.error = FALSE;
	exec_node(root, &ctx);
	if (ctx.fd[STDIN_FILENO] != STDIN_FILENO)
		close(ctx.fd[STDIN_FILENO]);
	if (ctx.fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx.fd[STDOUT_FILENO]);
}

void	exec_node(t_node *node, t_context *ctx)
{
	if (node == NULL)
		return ;
	if (ctx->error)
		return ;
	if (node->type == COMMAND)
		exec_command(node, ctx);
	else if (node->type == INPUT)
		exec_input(node, ctx);
	else if (node->type == OUTPUT)
		exec_output(node, ctx);
	else if (node->type == APPEND)
		exec_append(node, ctx);
}
