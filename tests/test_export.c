/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:25:49 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/03 11:44:27 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>

#include "builtins.h"

void	redirect_all_std(void)
{
	extern char	**environ;

	init_environ(environ);
	cr_redirect_stdout();
}

void teardown(void)
{
	free_environ();
}

Test(builtin_export, export_only, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", NULL};
	int		expected;
	int		result;
	
	expected = 0;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, wrong_name_nbr, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "1magic_br=42", NULL};
	int		expected;
	int		result;
	
	expected = 1;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, wrong_name_space, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "magic nbr=42", NULL};
	int		expected;
	int		result;
	
	expected = 1;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, key_without_value, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "magic", NULL};
	int		expected;
	int		result;
	
	expected = 0;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, key_with_value, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "_magic_nbr=42", NULL};
	int		expected;
	int		result;
	
	expected = 0;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, value_with_hyphen, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "_magic_nbr=42-forty", NULL};
	int		expected;
	int		result;
	
	expected = 0;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, multiple_export, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "_magic_nbr=42", "test", "test42=forty-two", NULL};
	int		expected;
	int		result;
	
	expected = 0;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_export, invalid_char, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"export", "==test", NULL};
	int		expected;
	int		result;
	
	expected = 1;
	result = ft_export(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}
