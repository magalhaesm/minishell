/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:35:29 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/24 11:04:28 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "helpers.h"

static void	set_redir(char *file, int fd, int stdfd, t_context *ctx);

int	exec_input(t_node *node, t_context *ctx)
{
	int		fd;
	char	*filename;

	filename = node->data.pair.right->data.cmd[0];
	fd = open(filename, O_RDONLY | O_CLOEXEC);
	set_redir(filename, fd, STDIN_FILENO, ctx);
	return (exec_node(node->data.pair.left, ctx));
}

int	exec_output(t_node *node, t_context *ctx)
{
	int		fd;
	char	*filename;

	filename = node->data.pair.right->data.cmd[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	set_redir(filename, fd, STDOUT_FILENO, ctx);
	return (exec_node(node->data.pair.left, ctx));
}

int	exec_append(t_node *node, t_context *ctx)
{
	int		fd;
	char	*filename;

	filename = node->data.pair.right->data.cmd[0];
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC, 0644);
	set_redir(filename, fd, STDOUT_FILENO, ctx);
	return (exec_node(node->data.pair.left, ctx));
}

static void	set_redir(char *file, int fd, int stdfd, t_context *ctx)
{
	if (fd < 0)
	{
		msh_error(file, NULL, 0);
		ctx->error = TRUE;
		ctx->retcode = 1;
	}
	else
	{
		if (ctx->fd[stdfd] != stdfd)
			close(ctx->fd[stdfd]);
		ctx->fd[stdfd] = fd;
	}
}
