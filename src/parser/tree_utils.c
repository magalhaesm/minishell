/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:20:05 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/08 19:13:00 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static void		swap_nodes(t_node *node, t_node *cmd);
static t_node	*insert_command(t_node *node, t_node *cmd);
static t_node	*insert_left(t_node *node, t_node *left);
static void		append_cmd(t_node *cmd, t_node *param);

t_node	*make_subtree(t_node *node, t_node *left)
{
	if (node && left)
		return (insert_left(node, left));
	else if (node == NULL)
		return (left);
	return (NULL);
}

static t_node	*insert_command(t_node *node, t_node *cmd)
{
	if (node->data.pair.left == NULL)
		node->data.pair.left = cmd;
	else
		append_cmd(node->data.pair.left, cmd);
	return (node);
}

static void	append_cmd(t_node *cmd, t_node *param)
{
	(void) cmd;
	(void) param;
	return ;
}

// TODO: please refactor me!
static t_node	*insert_left(t_node *node, t_node *left)
{
	if (node->type == COMMAND)
		return (insert_command(left, node));
	if (node->data.pair.left == NULL)
		node->data.pair.left = left;
	else if (node->data.pair.left->type == COMMAND)
		swap_nodes(node, left);
	else
		insert_left(node->data.pair.left, left);
	return (node);
}

static void	swap_nodes(t_node *node, t_node *cmd)
{
	node->data.pair.left = insert_left(cmd, node->data.pair.left);
}
