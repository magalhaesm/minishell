/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:36:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/24 11:03:19 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "scanner.h"

typedef enum e_node_type {
	COMMAND,
	AND,
	OR,
	PIPE,
	SUBSHELL,
	HERE_DOC,
	APPEND,
	INPUT,
	OUTPUT
}	t_node_type;

typedef struct s_node	t_node;
typedef char **			t_command;

typedef struct s_operand {
	t_node	*left;
	t_node	*right;
}	t_operand;

typedef union u_node_value {
	t_command	cmd;
	t_operand	pair;
}	t_node_value;

typedef struct s_node {
	t_node_type		type;
	t_node_value	data;
}	t_node;

t_node	*mkleaf(t_token token);
t_node	*mknode(t_node_type type, t_node *left, t_node *right);
t_node	*subtree(t_node *node, t_node *left);
void	free_tree(t_node *root);

#endif
