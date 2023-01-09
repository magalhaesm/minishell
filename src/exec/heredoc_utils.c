/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:51:04 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/08 17:47:30 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansion.h"
#include "events.h"

#define ERRMSG "here-document delimited by end-of-file (wanted `eof')"

static t_bool	delimiter(char *word, char *line);
static t_bool	next_line(char *input, char *word);

void	here_doc(char *delimiter)
{
	char	*input;
	char	*expanded;
	int		fd;

	fd = open(HEREDOC_TEMPFILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_fd_close(fd);
	wait_heredoc_signals();
	while (TRUE)
	{
		input = readline("> ");
		if (next_line(input, delimiter) == FALSE)
			break ;
		expanded = variable_expansion(input);
		ft_putendl_fd(expanded, fd);
		free(expanded);
		free(input);
	}
	close(fd);
}

static t_bool	next_line(char *input, char *word)
{
	if (!input)
	{
		msh_error("warning", ERRMSG, 0);
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

int	*get_fd_close(void)
{
	static int	fd;

	return (&fd);
}

void	set_fd_close(int fd)
{
	int	*save;

	save = get_fd_close();
	*save = fd;
}
