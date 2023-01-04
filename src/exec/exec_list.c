/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:24:20 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/03 17:58:03 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_and(t_node *node, t_context *ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->data.pair.left;
	rhs = node->data.pair.right;
	exec_node(lhs, ctx);
	reaper(ctx);
	if (ctx->retcode == EXIT_SUCCESS)
		exec_node(rhs, ctx);
}

void	exec_or(t_node *node, t_context *ctx)
{
	t_node	*lhs;
	t_node	*rhs;

	lhs = node->data.pair.left;
	rhs = node->data.pair.right;
	exec_node(lhs, ctx);
	reaper(ctx);
	if (ctx->retcode != EXIT_SUCCESS)
		exec_node(rhs, ctx);
}
