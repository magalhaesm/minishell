/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:50:33 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/23 15:54:11 by yde-goes         ###   ########.fr       */
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

Test(builtin_pwd, get_pwd_value, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"pwd", NULL};
	char	*expected;
	
	expected = ft_strjoin(getenv("PWD"), "\n");
	ft_pwd(input);
	fflush(stdout);
	cr_assert_stdout_eq_str(expected);
}
