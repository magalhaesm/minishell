/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:32:27 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/27 16:12:58 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

static void		skip_whitespace(t_scanner *self);
static t_bool	match(t_scanner *self, char expected);

t_token	scan_token(t_scanner *self)
{
	char	c;

	skip_whitespace(self);
	if (is_at_end(self))
		return (make_token(self, TOKEN_EOF));
	c = advance(self);
	if (c == '(')
		return (make_token(self, TOKEN_LEFT_PAREN));
	if (c == ')')
		return (make_token(self, TOKEN_RIGHT_PAREN));
	return (scan_double_char_token(self, c));
}

t_token	scan_double_char_token(t_scanner *self, char c)
{
	if (c == '<')
	{
		if (match(self, '<'))
			return (make_token(self, TOKEN_DLESS));
		return (make_token(self, TOKEN_LESS));
	}
	if (c == '>')
	{
		if (match(self, '>'))
			return (make_token(self, TOKEN_DGREAT));
		return (make_token(self, TOKEN_GREAT));
	}
	if (c == '&')
	{
		if (match(self, '&'))
			return (make_token(self, TOKEN_AND));
	}
	if (c == '|')
	{
		if (match(self, '|'))
			return (make_token(self, TOKEN_OR));
		return (make_token(self, TOKEN_PIPE));
	}
	return (token_word(self, c));
}

static t_bool	match(t_scanner *self, char expected)
{
	if (is_at_end(self))
		return (FALSE);
	if (*self->iter.current != expected)
		return (FALSE);
	advance(self);
	return (TRUE);
}

static void	skip_whitespace(t_scanner *self)
{
	while (ft_isspace(*self->iter.current))
		advance(self);
	self->iter.start = self->iter.current;
}
