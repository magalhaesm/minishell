/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:20:05 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/12 12:54:39 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_node	*append_cmd(t_node *command, t_node *param);
static t_node	*insert_left(t_node *parent, t_node *child, int level);
static t_node	*insert_command(t_node *parent, t_node *child, int level);

t_node	*subtree(t_node *node, t_node *child)
{
	if (node == NULL)
		return (child);
	if (node && child)
		return (insert_left(node, child, 0));
	return (NULL);
}

static t_node	*insert_left(t_node *parent, t_node *child, int level)
{
	t_node	**aux;

	aux = &parent->data.pair.left;
	if (parent->type == COMMAND)
		return (insert_command(parent, child, level));
	else if (*aux == NULL)
		*aux = child;
	else if ((*aux)->type == COMMAND)
		*aux = insert_left(child, *aux, level + 1);
	else
		insert_left(*aux, child, level);
	return (parent);
}

static t_node	*insert_command(t_node *parent, t_node *child, int level)
{
	if (child->type == COMMAND)
	{
		if (level == 0)
			return (append_cmd(child, parent));
		else
			return (append_cmd(parent, child));
	}
	return (insert_left(child, parent, level));
}

static t_node	*append_cmd(t_node *command, t_node *param)
{
	char	*aux;

	aux = command->data.cmd;
	command->data.cmd = ft_strjoin(aux, " ");
	free(aux);
	aux = command->data.cmd;
	command->data.cmd = ft_strjoin(aux, param->data.cmd);
	free(param->data.cmd);
	free(param);
	free(aux);
	return (command);
}
