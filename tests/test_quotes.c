#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "expansion.h"

void setup(void)
{
	extern char	**environ;

	init_environ(environ);
	ft_setenv("var1", "value1");
	ft_setenv("var2", "value2");
	ft_setenv("var3", "value3");
}

void teardown(void)
{
	free_environ();
}

Test(quotes, split_quotes, .init = setup, .fini = teardown,
		.description = "Separates the string in quotes")
{
	t_list	*list;
	char	*expected;
	char	*string;

	string = "var1'var2'\"var3\"";
	list = split_quotes(string);
	expected = list->content;
	cr_assert(eq(str, "var1", expected));
	list = list->next;
	expected = list->content;
	cr_assert(eq(str, "'var2'", expected));
	list = list->next;
	expected = list->content;
	cr_assert(eq(str, "\"var3\"", expected));
	ft_lstclear(&list, free);
}

Test(quotes, unquote, .init = setup, .fini = teardown,
		.description = "Expand and remove quotes")
{
	t_list	*list;
	char	*result;
	char	*expected;
	char	*string;

	string = "'sapien'\"pellentesque\"'habitant'";
	list = split_quotes(string);
	unquote(list);
	result = concatenate(list);
	expected = "sapienpellentesquehabitant";
	cr_assert(eq(str, result, expected));
	ft_lstclear(&list, free);
	free(result);
}

Test(quotes, concatenate, .init = setup, .fini = teardown,
		.description = "Concatenate quotes")
{
	t_list	*list;
	char	*result;
	char	*expected;
	char	*string;

	string = "$var1'$var2'\"$var3\"''\"\"";
	list = split_quotes(string);
	parameter_expansion(list);
	unquote(list);
	result = concatenate(list);
	expected = "value1$var2value3";
	cr_assert(eq(str, result, expected));
	ft_lstclear(&list, free);
}
