/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:35:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/03 09:51:33 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "helpers.h"
#include "expansion.h"

#define ENOENT 2
#define EACCES 13
#define EISDIR 21
#define FORKED_CHILD 0

static int		spawn_process(char **argv, t_context *ctx);
static int		launch_executable(char **argv, t_context *ctx);
static t_bool	is_executable(char *filename, t_context *ctx);

int	exec_command(t_node *node, t_context *ctx)
{
	char		**argv;
	t_builtin	exec_builtin;
	int			saved_fd[2];
	int			children;

	children = 0;
	argv = expand(node->data.cmd);
	if (ft_strchr(argv[0], '/') == NULL)
	{
		exec_builtin = builtin_pool(argv[0]);
		if (exec_builtin)
		{
			redirect_io(saved_fd, ctx);
			ctx->retcode = exec_builtin(argv);
			if (ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) == 0)
				ctx->quit = TRUE;
			restore_io(saved_fd);
		}
		else
			children += launch_executable(argv, ctx);
	}
	else if (is_executable(argv[0], ctx))
		children += spawn_process(argv, ctx);
	free_strtab(argv);
	return (children);
}

static int	launch_executable(char **argv, t_context *ctx)
{
	char	*fullpath;

	fullpath = search_path(argv[0]);
	if (fullpath)
	{
		free(argv[0]);
		argv[0] = fullpath;
		return (spawn_process(argv, ctx));
	}
	msh_error(argv[0], "command not found", 0);
	ctx->retcode = 127;
	return (0);
}

static t_bool	is_executable(char *filename, t_context *ctx)
{
	struct stat	statbuf;

	if (access(filename, F_OK) != 0)
	{
		msh_error(filename, NULL, ENOENT);
		ctx->retcode = 127;
		return (FALSE);
	}
	stat(filename, &statbuf);
	if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
	{
		msh_error(filename, NULL, EISDIR);
		ctx->retcode = 126;
		return (FALSE);
	}
	else if (access(filename, X_OK) != 0)
	{
		msh_error(filename, NULL, EACCES);
		ctx->retcode = 126;
		return (FALSE);
	}
	return (TRUE);
}

static int	spawn_process(char **argv, t_context *ctx)
{
	extern char	**environ;

	if (pfork() == FORKED_CHILD)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		execve(argv[0], argv, environ);
		exit(EXIT_FAILURE);
	}
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		close(ctx->fd[STDIN_FILENO]);
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx->fd[STDOUT_FILENO]);
	return (1);
}
