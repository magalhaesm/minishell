#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "helpers.h"

void setup(void)
{
	extern char	**environ;

	init_environ(environ);
	ft_setenv("key1", "value1");
	ft_setenv("key2", "value2");
	ft_setenv("key3", "value3");
}

void teardown(void)
{
	free_environ();
}

Test(environ, ft_setenv, .init = setup, .fini = teardown)
{
	char		*expected;
	char		*value;

	value = ft_getenv("key1");
	expected = "value1";
	cr_assert(eq(str, expected, value));
	value = ft_getenv("key2");
	expected = "value2";
	cr_assert(eq(str, expected, value));
	value = ft_getenv("key3");
	expected = "value3";
	cr_assert(eq(str, expected, value));
}

Test(environ, ft_unsetenv, .init = setup, .fini = teardown)
{
	char		*expected;
	char		*value;

	ft_unsetenv("key2");
	value = ft_getenv("key2");
	expected = NULL;
	cr_assert(eq(ptr, expected, value));
}
