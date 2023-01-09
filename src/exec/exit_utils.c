/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:01:52 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/08 17:30:12 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	msh_clean(void)
{
	free_pathtab();
	free_environ();
	rl_clear_history();
	free_tree(*get_tree_ref());
}

int	*get_exit_status(void)
{
	static int	status;

	return (&status);
}

void	set_exit_status(int status)
{
	int	*code;

	code = get_exit_status();
	*code = status;
}

void	save_tree_ref(t_node *root)
{
	t_node	**tree;

	tree = get_tree_ref();
	*tree = root;
}

t_node	**get_tree_ref(void)
{
	static t_node	*root;

	return (&root);
}
