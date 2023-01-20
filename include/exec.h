/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:45:35 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/20 17:57:26 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "parser.h"
# include "helpers.h"

# define FORKED_CHILD 0
# define PIPE_LIMIT 1024
# define HEREDOC_TEMPFILE "/tmp/heredoc_tempfile"

typedef struct s_context {
	int		fd[2];
	int		pid[PIPE_LIMIT];
	int		fd_close;
	int		proc;
	t_byte	retcode;
	t_bool	error;
	t_bool	quit;
	t_bool	pipeline;
}	t_context;

t_bool	execute(t_node *root);
void	exec_node(t_node *node, t_context *ctx);
void	exec_command(t_node *node, t_context *ctx);
void	exec_input(t_node *node, t_context *ctx);
void	exec_output(t_node *node, t_context *ctx);
void	exec_append(t_node *node, t_context *ctx);
void	exec_pipe(t_node *node, t_context *ctx);
void	exec_and(t_node *node, t_context *ctx);
void	exec_or(t_node *node, t_context *ctx);
void	exec_heredoc(t_node *node, t_context *ctx);
void	exec_subshell(t_node *node, t_context *ctx);
t_bool	exec_builtin(char **argv, t_context *ctx);

void	enqueue(long pid, t_context *ctx);
void	copy_queue(t_context *ctx, t_context aux_ctx);
void	redirect_io(int saved[], t_context *ctx);
void	restore_io(int saved[]);
void	reaper(t_context *ctx);

void	set_exit_status(int status);
int		*get_exit_status(void);
void	save_tree_ref(t_node *root);
t_node	**get_tree_ref(void);
void	msh_clean(void);

void	here_doc(char *delimiter);
void	set_fd_close(int fd);
int		*get_fd_close(void);

#endif
