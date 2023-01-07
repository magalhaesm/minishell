/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:56:51 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/07 07:32:50 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansion.h"
#include "sig_func.h"

#define ERRMSG "here-document at line N delimited by end-of-file (wanted `eof')"

static char		*quote_removal(char *word);
static t_bool	delimiter(char *word, char *line);
static void		here_doc(char *limiter, t_context *ctx);
static t_bool	next_line(char *input, char *word, int line);

void	exec_heredoc(t_node *node, t_context *ctx)
{
	char		*word;
	int			pid;
	int			pfd[2];
	t_context	aux_ctx;

	pipe(pfd);
	aux_ctx = *ctx;
	aux_ctx.fd[STDOUT_FILENO] = pfd[STDOUT_FILENO];
	aux_ctx.fd_close = pfd[STDIN_FILENO];
	pid = pfork();
	if (pid == FORKED_CHILD)
	{
		word = node->data.pair.right->data.cmd[0];
		word = quote_removal(word);
		here_doc(word, &aux_ctx);
		free(word);
		msh_clean();
		exit(aux_ctx.retcode);
	}
	ctx->fd[STDIN_FILENO] = pfd[STDIN_FILENO];
	close(pfd[STDOUT_FILENO]);
	enqueue(pid, ctx);
	reaper(ctx);
	exec_node(node->data.pair.left, ctx);
}

static void	here_doc(char *word, t_context *ctx)
{
	int		line;
	char	*input;

	input = "";
	line = 1;
	while (input)
	{
		wait_heredoc_signals();
		input = readline("> ");
		if (next_line(input, word, line) == FALSE)
			break ;
		line++;
		ft_putendl_fd(input, ctx->fd[STDOUT_FILENO]);
		free(input);
	}
	close(ctx->fd[STDOUT_FILENO]);
	close(ctx->fd_close);
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
