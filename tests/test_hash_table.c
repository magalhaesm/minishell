#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "hash_table.h"

Test(hash_table, init_table)
{
	t_table	table;

	init_table(&table);
	cr_assert(eq(table.count, 0));
	cr_assert(eq(table.capacity, 0));
	cr_assert(eq(table.type_size, sizeof(t_entry)));
	cr_assert(eq(table.data, NULL));
	free_table(&table);
}

Test(hash_table, table_set)
{
	t_table	table;
	char	*key;
	char	*value;

	key = "chave";
	value = "valor";
	init_table(&table);
	cr_assert(eq(table_set(&table, key, value), TRUE), "Fail to insert");
	cr_assert(eq(table_set(&table, key, value), FALSE), "Fail to update");
	free_table(&table);
}

Test(hash_table, table_get)
{
	t_table	table;
	char	*key1;
	char	*key2;
	char	*value;
	char	*expected;

	key1 = "ls";
	key2 = strdup(key1);
	expected = "/usr/bin/ls";
	init_table(&table);
	cr_assert(eq(table_get(&table, key1, &value), FALSE),
			"Failed to return false when value not found");
	table_set(&table, key1, expected);
	cr_assert(eq(table_get(&table, key2, &value), TRUE),
			"Failed to return true when value found");
	cr_assert(eq(str, expected, value));
	free_table(&table);
}

Test(hash_table, table_delete)
{
	t_table	table;
	char	*key;
	char	*value;
	char	*expected;

	init_table(&table);
	key = "chave";
	value = "valor";
	cr_assert(eq(table_delete(&table, key), FALSE),
			"Failed to return false when value not found");
	table_set(&table, key, value);
	table_get(&table, key, &expected);
	cr_assert(eq(str, expected, value));
	cr_assert(eq(table_delete(&table, key), TRUE),
			"Failed to return true when value found");
	free_table(&table);
}
