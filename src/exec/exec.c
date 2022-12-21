/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:46:14 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 15:28:00 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute(t_node *root)
{
	t_context	ctx;

	ctx.retcode = parse_status();
	ctx.error = FALSE;
	exec_node(root, &ctx);
}

void	exec_node(t_node *node, t_context *ctx)
{
	if (node == NULL)
		return ;
	if (ctx->error)
		return ;
	if (node->type == COMMAND)
		exec_command(node, ctx);
}
