/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:56:51 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/05 12:53:11 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_limiter(char *line, char *limiter);
static void	here_doc(char *limiter, t_context *ctx);

void	exec_heredoc(t_node *node, t_context *ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	*limiter;

	rhs = node->data.pair.right;
	limiter = rhs->data.cmd[0];
	here_doc(limiter, ctx);
	lhs = node->data.pair.left;
	exec_node(lhs, ctx);
}

static void	here_doc(char *limiter, t_context *ctx)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	line = "";
	while (TRUE)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break;
		if (is_limiter(line, limiter))
		{
			free(line);
			close(STDIN_FILENO);
			get_next_line(STDIN_FILENO);
			break ;
		}
		ft_putstr_fd(line, fd[STDOUT_FILENO]);
		free(line);
	}
	close(fd[STDOUT_FILENO]);
	ctx->fd[STDIN_FILENO] = fd[STDIN_FILENO];
}

static int	is_limiter(char *line, char *limiter)
{
	int	content;
	int	length;

	content = ft_strncmp(line, limiter, ft_strlen(limiter)) == 0;
	length = (ft_strlen(line) - 1) == ft_strlen(limiter);
	return (content && length);
}
