/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:25:54 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/26 19:57:46 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <sys/stat.h>
#include <sys/types.h>

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

Test(builtin_cd, cd_home_arg, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"cd", NULL};
	int		expected;
	int		result;
	char	*pwd;
	char	*new_pwd;

	pwd = ft_getenv("PWD");
	expected = 0;
	result = ft_cd(input);
	new_pwd = ft_getenv("PWD");
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
	cr_assert(ne(str, pwd, new_pwd));
}

Test(builtin_cd, cd_many_arg, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"cd", "test", "folder", NULL};
	int		expected;
	int		result;
	
	expected = 1;
	result = ft_cd(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}

Test(builtin_cd, cd_false_dir, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"cd", "no_dir", NULL};
	int		expected;
	int		result;

	expected = 0; 
	result = ft_cd(input);
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
}


Test(builtin_cd, cd_dir_exist, .init = redirect_all_std, .fini = teardown)
{
	char	*input[] = {"cd", "test_folder", NULL};
	int		expected;
	int		result;
	char	*dir_name = "test_folder";
	char	*pwd;
	char	*new_pwd;

	
	pwd = ft_getenv("PWD");
	expected = 0;
	if (mkdir(dir_name, 777))
		cr_fail("Couldn't create directory to test " \
		  		"builtin_cd::cd_dir_exist");
	result = ft_cd(input);
	new_pwd = ft_getenv("PWD");
	if (rmdir(dir_name))
		cr_fail("Couldn't remove directory used for " \
		  		"builtin_cd::cd_dir_exist");
	fflush(stdout);
	cr_assert(eq(i32, result, expected));
	cr_assert(ne(str, pwd, new_pwd));
}
