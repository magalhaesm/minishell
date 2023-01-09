#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "helpers.h"

Test(string, wordcount, .description = "Count occurrences")
{
	int		expected;
	char	*string;
	char	*word;

	string = "var var2 var var3 var";
	word = "var";
	expected = 5;
	cr_assert(eq(int, expected, wordcount(string, word)));
	word = "VAR";
	expected = 0;
	cr_assert(eq(int, expected, wordcount(string, word)));
}

Test(string, replace, .description = "Replace words")
{
	char	*expected;
	char	*string;
	char	*oldw;
	char	*neww;

	string = "var var2 var var3 var";
	oldw = "var";
	neww = "VAR";
	expected = "VAR VAR2 VAR VAR3 VAR";
	cr_assert(eq(str, expected, str_replace(string, oldw, neww)));
}
