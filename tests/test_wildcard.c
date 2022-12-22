/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:01:42 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 16:17:33 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "expansion.h"

Test(wildcard, first_mid_asterisk)
{
	char eval[] = "baaabab";
	char pattern[] = "*****ba*****ab";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, many_mid_asterisks)
{
	char eval[] = "baaabab";
	char pattern[] = "ba*****ab";

	cr_assert(eq(true, is_match(eval, pattern)));
}


Test(wildcard, one_mid_asterisk)
{
	char eval[] = "baaabab";
	char pattern[] = "ba*ab";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, first_chr_one_asterisk)
{
	char eval[] = "baaabab";
	char pattern[] = "a*ab";

	cr_assert(eq(false, is_match(eval, pattern)));
}

Test(wildcard, first_chr_many_asterisks)
{
	char eval[] = "baaabab";
	char pattern[] = "a*****ab";

	cr_assert(eq(false, is_match(eval, pattern)));
}

Test(wildcard, first_chr_two_wildcards)
{
	char eval[] = "baaabab";
	char pattern[] = "*a*****ab";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, mid_end_wildcards)
{
	char eval[] = "baaabab";
	char pattern[] = "ba*ab****";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, four_asterisks)
{
	char eval[] = "baaabab";
	char pattern[] = "****";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, single_asterisk)
{
	char eval[] = "baaabab";
	char pattern[] = "*";

	cr_assert(eq(true, is_match(eval, pattern)));
}


Test(wildcard, mid_question_mark)
{
	char eval[] = "baaabab";
	char pattern[] = "aa?ab";

	cr_assert(eq(false, is_match(eval, pattern)));
}

Test(wildcard, true_substr_eval)
{
	char eval[] = "baaabab";
	char pattern[] = "b*b";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, false_substr_eval)
{
	char eval[] = "baaabab";
	char pattern[] = "a*a";

	cr_assert(eq(false, is_match(eval, pattern)));
}

Test(wildcard, eq_eval_pattern)
{
	char eval[] = "baaabab";
	char pattern[] = "baaabab";

	cr_assert(eq(true, is_match(eval, pattern)));
}

Test(wildcard, null_question_mark)
{
	char eval[] = "baaabab";
	char pattern[] = "?baaabab";

	cr_assert(eq(false, is_match(eval, pattern)));
}

Test(wildcard, first_end_wildcard)
{
	char eval[] = "baaabab";
	char pattern[] = "*baaaba*";

	cr_assert(eq(true, is_match(eval, pattern)));
}
