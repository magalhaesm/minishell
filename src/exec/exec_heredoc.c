/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:56:51 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/05 14:05:10 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	delimiter(char *word, char *line);
static void		here_doc(char *limiter, t_context *ctx);

void	exec_heredoc(t_node *node, t_context *ctx)
{
	t_node	*lhs;
	t_node	*rhs;
	char	*word;

	rhs = node->data.pair.right;
	word = rhs->data.cmd[0];
	here_doc(word, ctx);
	lhs = node->data.pair.left;
	exec_node(lhs, ctx);
}

static void	here_doc(char *word, t_context *ctx)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	line = "";
	while (line)
	{
		line = readline("> ");
		if (delimiter(word, line))
		{
			free(line);
			close(fd[STDOUT_FILENO]);
			ctx->fd[STDIN_FILENO] = fd[STDIN_FILENO];
			break ;
		}
		ft_putendl_fd(line, fd[STDOUT_FILENO]);
		free(line);
	}
}

static t_bool	delimiter(char *word, char *line)
{
	int	content;
	int	length;

	content = ft_strncmp(line, word, ft_strlen(word)) == 0;
	length = (ft_strlen(line) == ft_strlen(word));
	return (content && length);
}
