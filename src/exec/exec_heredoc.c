/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:56:51 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/06 16:39:05 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansion.h"
#include "helpers.h"
#include "sig_func.h"

#define ERRMSG "here-document at line N delimited by end-of-file (wanted `eof')"

static char		*quote_removal(char *word);
static t_bool	delimiter(char *word, char *line);
static void		here_doc(char *limiter, t_context *ctx);
static t_bool	next_line(char *input, char *word, int line);

void	exec_heredoc(t_node *node, t_context *ctx)
{
	t_node	*lhs;
	char	*word;

	word = node->data.pair.right->data.cmd[0];
	word = quote_removal(word);
	here_doc(word, ctx);
	free(word);
	lhs = node->data.pair.left;
	exec_node(lhs, ctx);
}

static void	here_doc(char *word, t_context *ctx)
{
	int		line;
	char	*input;
	int		fd[2];

	pipe(fd);
	input = "";
	line = 1;
	while (input)
	{
		wait_heredoc_signals();
		input = readline("> ");
		if (next_line(input, word, line) == FALSE)
			break ;
		line++;
		ft_putendl_fd(input, fd[STDOUT_FILENO]);
		free(input);
	}
	close(fd[STDOUT_FILENO]);
	ctx->fd[STDIN_FILENO] = fd[STDIN_FILENO];
	ctx->retcode = EXIT_SUCCESS;
}

static t_bool	next_line(char *input, char *word, int line)
{
	char	*number;
	char	*err_msg;

	if (!input)
	{
		number = ft_itoa(line);
		err_msg = str_replace(ERRMSG, "N", number);
		msh_error("warning", err_msg, 0);
		free(number);
		free(err_msg);
		return (FALSE);
	}
	else if (delimiter(word, input))
	{
		free(input);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	delimiter(char *word, char *line)
{
	int	content;
	int	length;

	content = ft_strncmp(line, word, ft_strlen(word)) == 0;
	length = (ft_strlen(line) == ft_strlen(word));
	return (content && length);
}

static char	*quote_removal(char *word)
{
	t_list	*list;
	char	*chunk;

	list = split_quotes(word);
	unquote(list);
	chunk = concatenate(list);
	ft_lstclear(&list, free);
	return (chunk);
}
