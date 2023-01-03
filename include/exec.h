/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:45:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/03 09:52:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "parser.h"
# include "helpers.h"

typedef struct s_context {
	int		fd[2];
	int		fd_close;
	t_byte	retcode;
	t_bool	error;
	t_bool	quit;
}	t_context;

t_bool	execute(t_node *root);
int		exec_node(t_node *node, t_context *ctx);
int		exec_command(t_node *node, t_context *ctx);
int		exec_input(t_node *node, t_context *ctx);
int		exec_output(t_node *node, t_context *ctx);
int		exec_append(t_node *node, t_context *ctx);
int		exec_pipe(t_node *node, t_context *ctx);
int		*get_exit_status(void);
void	set_exit_status(int status);

void	redirect_io(int saved[], t_context *ctx);
void	restore_io(int saved[]);

#endif
