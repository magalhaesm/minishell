/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:36:05 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/24 11:02:59 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
#include "helpers.h"

t_node	*mkleaf(t_token token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = COMMAND;
	node->data.cmd = malloc(sizeof(char *) * 2);
	node->data.cmd[0] = ft_substr(token.start, 0, token.length);
	node->data.cmd[1] = NULL;
	return (node);
}

t_node	*mknode(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);
}

void	free_tree(t_node *self)
{
	if (self == NULL)
		return ;
	else if (self->type == COMMAND)
		free_strtab(self->data.cmd);
	else
	{
		free_tree(self->data.pair.left);
		free_tree(self->data.pair.right);
	}
	free(self);
}
