/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:41:15 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/10 09:08:53 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define SETS 4
#define TERMINALS 13

static t_token_type	*parse_table(t_nonterminal nts);

t_bool	first_set(t_nonterminal nts, t_scanner *scanner)
{
	t_token_type	*table;

	table = parse_table(nts);
	return (table[peek(scanner).type] != TOKEN_UNKNOWN);
}

// Some productions have the same first set, so this
// function groups these sets at the same index, which
// can be accessed by their common identifier. See parser.h
static t_token_type	*parse_table(t_nonterminal nts)
{
	static t_token_type	first[SETS][TERMINALS] = {
	[LIST] = {TOKEN_UNKNOWN, TOKEN_LESS, TOKEN_GREAT, TOKEN_UNKNOWN,
		TOKEN_LEFT_PAREN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
		TOKEN_DLESS, TOKEN_DGREAT, TOKEN_WORD, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
	},
	[SIMPLE_CMD] = {TOKEN_UNKNOWN, TOKEN_LESS, TOKEN_GREAT, TOKEN_UNKNOWN,
		TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
		TOKEN_DLESS, TOKEN_DGREAT, TOKEN_WORD, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
	},
	[IO_REDIRECT] = {TOKEN_UNKNOWN, TOKEN_LESS, TOKEN_GREAT, TOKEN_UNKNOWN,
		TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_DLESS,
		TOKEN_DGREAT, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
	},
	[IO_FILE] = {TOKEN_UNKNOWN, TOKEN_LESS, TOKEN_GREAT, TOKEN_UNKNOWN,
		TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
		TOKEN_UNKNOWN, TOKEN_DGREAT, TOKEN_UNKNOWN, TOKEN_UNKNOWN,
		TOKEN_UNKNOWN,
	},
	};

	return (first[nts]);
}
