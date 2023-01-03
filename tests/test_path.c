/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:49:55 by mdias-ma          #+#    #+#             */
/*   Updated: 2023/01/02 21:49:11 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "helpers.h"
#include "builtins.h"

void setup(void)
{
	extern char	**environ;

	init_environ(environ);
	init_pathtab();
}

void teardown(void)
{
	free_environ();
	free_pathtab();
}

Test(path, search, .init = setup, .fini = teardown)
{
	char	*executable;
	char	*expected;
	char	*result;

	executable = "ls";
	result = search_path(executable);
	expected = "/usr/bin/ls";
	cr_assert(eq(str, expected, result));
}

Test(path, fail, .init = setup, .fini = teardown)
{
	char	*executable;
	char	*expected;
	char	*result;

	executable = "nonexistent";
	result = search_path(executable);
	expected = NULL;
	cr_assert(eq(ptr, expected, result));
}

Test(path, reset, .init = setup, .fini = teardown)
{
	char	*executable;
	char	*expected;
	char	*result;
	char	*unset[] = {"unset", "PATH", NULL};
	char	*reset[] = {"export", "PATH=/usr/bin", NULL};

	executable = "ls";
	result = search_path(executable);
	expected = "/usr/bin/ls";
	cr_assert(eq(str, expected, result));

	ft_unset(unset);
	result = search_path(executable);
	expected = NULL;
	cr_assert(eq(ptr, expected, result));

	ft_export(reset);
	result = search_path(executable);
	expected = "/usr/bin/ls";
	cr_assert(eq(str, expected, result));
}
