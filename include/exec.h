/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:45:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 15:28:28 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/wait.h>
# include <sys/stat.h>

# include "parser.h"
# include "helpers.h"

typedef struct s_context {
	t_byte	retcode;
	t_bool	error;
}	t_context;

void	execute(t_node *root);
void	exec_node(t_node *node, t_context *ctx);
void	exec_command(t_node *node, t_context *ctx);

#endif
