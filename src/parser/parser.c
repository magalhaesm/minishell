/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:17:47 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/17 19:11:51 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define FAILED 2

static int	*get_status(void);

t_node	*parse(t_scanner *scanner)
{
	t_node	*root;
	int		*status;

	if (peek(scanner).type == TOKEN_EOF)
	{
		status = get_status();
		*status = EXIT_SUCCESS;
		return (NULL);
	}
	root = list(scanner);
	if (peek(scanner).type != TOKEN_EOF)
	{
		syntax_error(scanner);
		free_tree(root);
		status = get_status();
		*status = FAILED;
		return (NULL);
	}
	return (root);
}

t_bool	match(t_token_type type, t_scanner *scanner)
{
	if (peek(scanner).type == type)
	{
		next(scanner);
		return (TRUE);
	}
	return (FALSE);
}

int	parse_status(void)
{
	int	*error;

	error = get_status();
	return (*error);
}

static int	*get_status(void)
{
	static int	error;

	return (&error);
}
