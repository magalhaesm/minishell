/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:56:51 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/06 09:09:17 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansion.h"
#include "libft.h"
#include "sig_func.h"

static t_bool	delimiter(char *word, char *line);
static void		here_doc(char *limiter, t_context *ctx);
static char		*unquote(char *word);

void	exec_heredoc(t_node *node, t_context *ctx)
{
	t_node	*lhs;
	char	*word;

	word = node->data.pair.right->data.cmd[0];
	word = unquote(word);
	here_doc(word, ctx);
	free(word);
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
		wait_heredoc_signals();
		line = readline("> ");
		if (!line)
		{
			close(fd[STDOUT_FILENO]);
			close(fd[STDIN_FILENO]);
			return ;
		}
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

static char	*unquote(char *word)
{
	t_list	*list;
	t_list	*aux;
	char	*chunk;

	list = split_quotes(word);
	aux = list;
	while (aux)
	{
		chunk = aux->content;
		if (empty_quotes(chunk))
		{
			free(aux->content);
			aux->content = ft_strdup("");
		}
		else if (chunk[0] == '\'' || chunk[0] == '"')
		{
			chunk = ft_strtrim(chunk, "'\"");
			free(aux->content);
			aux->content = chunk;
		}
		aux = aux->next;
	}
	chunk = concatenate(list);
	ft_lstclear(&list, free);
	return (chunk);
}
