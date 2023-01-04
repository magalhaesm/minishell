/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:57:07 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/04 08:07:18 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	print_type(t_node *node);
void	print_cmd(t_node *node);
void	print_tree(t_node *root, int indentation);
void	indent(int indentation);

void	print_tree(t_node *root, int indentation)
{
	if (root == NULL)
		return ;
	indent(indentation);
	print_type(root);
	if (root->type != COMMAND)
	{
		print_tree(root->data.pair.left, indentation + 2);
		print_tree(root->data.pair.right, indentation + 2);
	}
}

void	print_type(t_node *node)
{
	if (node->type == COMMAND)
		print_cmd(node);
	else if (node->type == INPUT)
		ft_printf("INPUT:\n");
	else if (node->type == OUTPUT)
		ft_printf("OUTPUT:\n");
	else if (node->type == PIPE)
		ft_printf("PIPE:\n");
	else if (node->type == APPEND)
		ft_printf("APPEND:\n");
	else if (node->type == HERE_DOC)
		ft_printf("HERE_DOC:\n");
	else if (node->type == AND)
		ft_printf("AND:\n");
	else if (node->type == OR)
		ft_printf("OR:\n");
	else if (node->type == SUBSHELL)
		ft_printf("SUBSHELL:\n");
}

void	print_cmd(t_node *node)
{
	int	str;

	str = 0;
	ft_printf("COMMAND:");
	while (node->data.cmd[str])
		ft_printf(" %s", node->data.cmd[str++]);
	ft_printf("\n");
}

void	indent(int indentation)
{
	while (indentation--)
		ft_putchar_fd(' ', STDOUT_FILENO);
}
