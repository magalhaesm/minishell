/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 10:30:57 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/07 16:08:42 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "builtins.h"

Test(builtin_exit, exit_only_arg)
{
	char	*input[] = {"exit", NULL};
	int		expected;
	int		result;

	expected = 0;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, one_alfanumeric_arg)
{
	char	*input[] = {"exit", "42teste", NULL};
	int		expected;
	int		result;

	expected = 2;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, multi_alfanumeric_args)
{
	char	*input[] = {"exit", "42teste", "21teste", "1001teste", NULL};
	int		expected;
	int		result;

	expected = 2;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, multi_numeric_args)
{
	char	*input[] = {"exit", "42", "21", "1001", NULL};
	int		expected;
	int		result;

	expected = 127;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, single_positive_arg)
{
	char	*input[] = {"exit", "42", NULL};
	int		expected;
	int		result;

	expected = 42;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, single_negative_arg)
{
	char	*input[] = {"exit", "-42", NULL};
	int		expected;
	int		result;

	expected = 214;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, one_hyphen_only)
{
	char	*input[] = {"exit", "-", NULL};
	int		expected;
	int		result;

	expected = 2;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, double_hyphen)
{
	char	*input[] = {"exit", "--", NULL};
	int		expected;
	int		result;

	expected = 2;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, long_positive_nbr)
{
	char	*input[] = {"exit", "2147483649", NULL};
	int		expected;
	int		result;

	expected = 1;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}

Test(builtin_exit, long_negative_nbr)
{
	char	*input[] = {"exit", "-2147483649", NULL};
	int		expected;
	int		result;

	expected = 255;
	result = ft_exit(input);
	cr_assert(eq(int, result, expected));
}
