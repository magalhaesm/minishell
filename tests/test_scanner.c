#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "scanner.h"

t_token	fixture(char *source)
{
	t_scanner	scanner;
	t_token		tok;

	scanner = init_scanner(source);
	tok = next(&scanner);
	return (tok);
}

Test(scanner, one_char)
{
	t_token	tok;

	tok = fixture("+");
	cr_assert(eq(tok.length, 1));
	cr_assert(eq(tok.type, TOKEN_WORD));
}

Test(scanner, one_word)
{
	t_token	tok;

	tok = fixture("ls");
	cr_assert(eq(tok.length, 2));
	cr_assert(eq(tok.type, TOKEN_WORD));
}

Test(scanner, special_chars)
{
	t_token	tok;

	tok = fixture("mini-shell");
	cr_assert(eq(tok.length, 10));
	cr_assert(eq(tok.type, TOKEN_WORD));
	tok = fixture("$minishell");
	cr_assert(eq(tok.length, 10));
	cr_assert(eq(tok.type, TOKEN_WORD));
}

Test(scanner, word_with_spaces)
{
	t_token	tok;

	tok = fixture(" \t minishell \t ");
	cr_assert(eq(tok.length, 9));
	cr_assert(eq(tok.type, TOKEN_WORD));
}

Test(scanner, concatenation)
{
	t_token	tok;

	tok = fixture("echo'test'");
	cr_assert(eq(tok.length, 10));
	cr_assert(eq(tok.type, TOKEN_WORD));

	tok = fixture("echo\"t\"e's't\"e\"");
	cr_assert(eq(tok.length, 15));
	cr_assert(eq(tok.type, TOKEN_WORD));

	tok = fixture("\"test string\"");
	cr_assert(eq(tok.length, 13));
	cr_assert(eq(tok.type, TOKEN_WORD));

	tok = fixture("'t'e's''t'e");
	cr_assert(eq(tok.length, 11));
	cr_assert(eq(tok.type, TOKEN_WORD));
}

Test(scanner, misc)
{
	t_token	tok;

	tok = fixture("' '");
	cr_assert(eq(tok.length, 3), "Fail in ' '");
	cr_assert(eq(tok.type, TOKEN_WORD));

	tok = fixture("''");
	cr_assert(eq(tok.length, 2), "Fail with empty strings");
	cr_assert(eq(tok.type, TOKEN_WORD));

	tok = fixture("echo'");
	cr_assert(eq(tok.type, TOKEN_ERROR), "Fail with unclosed strings");
}
