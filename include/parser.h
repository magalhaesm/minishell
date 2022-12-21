/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:49:48 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/21 14:40:55 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "scanner.h"
# include "tree.h"

typedef enum e_nonterminal {
	LIST = 0,
	PIPELINE = LIST,
	CMD = LIST,
	SIMPLE_CMD = 1,
	WORD_NULL = SIMPLE_CMD,
	CMD_SUFFIX = SIMPLE_CMD,
	CMD_SUFFIX_NULL = SIMPLE_CMD,
	IO_REDIRECT = 2,
	CMD_PREFIX = IO_REDIRECT,
	CMD_PREFIX_NULL = IO_REDIRECT,
	REDIRECT_LIST = IO_REDIRECT,
	REDIRECT_LIST_NULL = IO_REDIRECT,
	SUBSHELL_NULL = IO_REDIRECT,
	IO_FILE = 3,
}	t_nonterminal;

t_node	*parse(t_scanner *scanner);
t_bool	match(t_token_type type, t_scanner *scanner);
t_bool	first_set(t_nonterminal nts, t_scanner *scanner);
void	syntax_error(t_scanner *scanner);
int		parse_status(void);

// RULES:
t_node	*list(t_scanner *scanner);
t_node	*conditional(t_scanner *scanner);
t_node	*pipeline(t_scanner *scanner);
t_node	*pipeline_null(t_scanner *scanner);
t_node	*command(t_scanner *scanner);
t_node	*subshell(t_scanner *scanner);
t_node	*subshell_redir(t_scanner *scanner);
t_node	*simple_cmd(t_scanner *scanner);
t_node	*word_null(t_scanner *scanner);
t_node	*fcmd_prefix(t_scanner *scanner);
t_node	*cmd_prefix(t_scanner *scanner);
t_node	*cmd_prefix_null(t_scanner *scanner);
t_node	*cmd_suffix(t_scanner *scanner);
t_node	*cmd_suffix_null(t_scanner *scanner);
t_node	*redirect_list(t_scanner *scanner);
t_node	*redirect_list_null(t_scanner *scanner);
t_node	*io_redirect(t_scanner *scanner);
t_node	*io_file(t_scanner *scanner);
t_node	*io_here(t_scanner *scanner);

#endif
