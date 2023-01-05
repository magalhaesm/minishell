/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:24:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/04 22:35:16 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_and(t_node *node, t_context *ctx)
{
	t_node		*lhs;
	t_node		*rhs;
	t_context	aux_ctx;

	lhs = node->data.pair.left;
	aux_ctx = *ctx;
	exec_node(lhs, &aux_ctx);
	ctx->proc_queue = aux_ctx.proc_queue;
	reaper(ctx);
	if (ctx->retcode == EXIT_SUCCESS)
	{
		aux_ctx = *ctx;
		rhs = node->data.pair.right;
		exec_node(rhs, &aux_ctx);
		reaper(&aux_ctx);
	}
}

void	exec_or(t_node *node, t_context *ctx)
{
	t_node		*lhs;
	t_node		*rhs;
	t_context	aux_ctx;

	lhs = node->data.pair.left;
	aux_ctx = *ctx;
	exec_node(lhs, &aux_ctx);
	ctx->proc_queue = aux_ctx.proc_queue;
	reaper(ctx);
	if (ctx->retcode != EXIT_SUCCESS)
	{
		aux_ctx = *ctx;
		rhs = node->data.pair.right;
		exec_node(rhs, &aux_ctx);
		reaper(&aux_ctx);
	}
}
