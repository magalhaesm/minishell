/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:35:36 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 15:32:38 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "helpers.h"

#define ENOENT 2
#define EACCES 13
#define EISDIR 21
#define FORKED_CHILD 0

static int		spawn_process(char **argv, t_context *ctx);
static int		launch_executable(char **argv, t_context *ctx);
static t_bool	is_executable(char *filename, t_context *ctx);
static void		report_sigterm(int wstatus);

void	exec_command(t_node *node, t_context *ctx)
{
	char		**argv;
	t_builtin	exec_builtin;

	argv = ft_split(node->data.cmd, ' ');
	if (ft_strchr(argv[0], '/') == NULL)
	{
		exec_builtin = builtin_pool(argv[0]);
		if (exec_builtin)
			ctx->retcode = exec_builtin(argv);
		else
			launch_executable(argv, ctx);
	}
	else if (is_executable(argv[0], ctx))
		spawn_process(argv, ctx);
	free_strtab(argv);
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
	return (EXIT_FAILURE);
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
	int			wstatus;
	extern char	**environ;

	if (pfork() == FORKED_CHILD)
	{
		execve(argv[0], argv, environ);
		exit(EXIT_FAILURE);
	}
	wait(&wstatus);
	if (WIFEXITED(wstatus))
		ctx->retcode = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		ctx->retcode = wstatus;
		report_sigterm(wstatus);
	}
	return (EXIT_SUCCESS);
}

static void	report_sigterm(int wstatus)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("Process finished with exit code ", STDERR_FILENO);
	ft_putnbr_fd(wstatus, STDERR_FILENO);
	ft_putstr_fd(" (interrupted by signal ", STDERR_FILENO);
	ft_putnbr_fd(WTERMSIG(wstatus), STDERR_FILENO);
	ft_putendl_fd(")", STDERR_FILENO);
}
