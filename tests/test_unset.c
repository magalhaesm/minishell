/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:11:35 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/23 16:12:21 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "builtins.h"

void setup(void)
{
	extern char	**environ;

	init_environ(environ);
}

void teardown(void)
{
	free_environ();
}

Test(builtin_unset, sucessfully_unset, .init = setup, .fini = teardown)
{
	char	*input[] = {"unset", "PWD", "HOME", NULL};
	char	*expected;
	char	*pwd;
	char	*home;

	ft_unset(input);
	pwd = ft_getenv("PWD");
	home = ft_getenv("HOME");
	expected = NULL;
	cr_assert(eq(ptr, expected, pwd));
	cr_assert(eq(ptr, expected, home));
}
