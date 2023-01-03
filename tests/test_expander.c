/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:30:29 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/02 11:08:21 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "helpers.h"
#include "expansion.h"

void setup(void)
{
	extern char	**environ;

	init_environ(environ);
	ft_setenv("expandable", "value");
	ft_setenv("valueless", "");
}

void teardown(void)
{
	free_environ();
}

Test(expander, interpolate, .init = setup, .fini = teardown)
{
	char	*string;
	char	*expected;
	char	*result;

	string = "$expandable .$valueless. $expandable";
	expected = "value .. value";
	result = variable_expansion(string);
	cr_assert(eq(str, expected, result));
	free(result);
}

Test(expander, nonexistent, .init = setup, .fini = teardown)
{
	char	*string;
	char	*expected;
	char	*result;

	string = ".$nonexistent.";
	expected = "..";
	result = variable_expansion(string);
	cr_assert(eq(str, expected, result));
	free(result);
}

Test(expander, ignore, .init = setup, .fini = teardown,
	.description = "Expand only valid identifiers")
{
	char	*string;
	char	*expected;
	char	*result;

	string = "$* $@ $# $expandable $- $$ $! $0";
	expected = "$* $@ $# value $- $$ $! $0";
	result = variable_expansion(string);
	cr_assert(eq(str, expected, result));
	free(result);
}
