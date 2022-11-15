/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:39:31 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/15 08:13:44 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internals.h"

static void		adjust_capacity(t_table *table, int capacity);
static t_entry	*find_entry(t_entry *entries, int capacity, char *key);

t_bool	table_set(t_table *table, char *key, char *value)
{
	t_entry	*entry;
	int		capacity;
	t_bool	is_new_key;

	if (table->count + 1 > table->capacity * TABLE_LOAD_MAX)
	{
		capacity = grow_capacity(table->capacity);
		adjust_capacity(table, capacity);
	}
	entry = find_entry(table->data, table->capacity, key);
	is_new_key = entry->key == NULL;
	if (is_new_key && !entry->value)
		table->count++;
	entry->key = key;
	entry->value = value;
	return (is_new_key);
}

t_bool	table_get(t_table *table, char *key, char **value)
{
	t_entry	*entry;

	if (table->count == 0)
		return (FALSE);
	entry = find_entry(table->data, table->capacity, key);
	if (entry->key == NULL)
		return (FALSE);
	*value = entry->value;
	return (TRUE);
}

t_bool	table_delete(t_table *table, char *key)
{
	t_entry	*entry;

	if (table->count == 0)
		return (FALSE);
	entry = find_entry(table->data, table->capacity, key);
	if (entry->key == NULL)
		return (FALSE);
	entry->key = NULL;
	entry->value = RIP;
	return (TRUE);
}

static t_entry	*find_entry(t_entry *entries, int capacity, char *key)
{
	t_uint	index;
	t_entry	*entry;
	t_entry	*tombstone;

	index = hash_string(key) % capacity;
	tombstone = NULL;
	while (TRUE)
	{
		entry = &entries[index];
		if (entry->key == NULL)
		{
			if (entry->value == NULL)
			{
				if (tombstone)
					return (tombstone);
				return (entry);
			}
			else if (tombstone == NULL)
					tombstone = entry;
		}
		else if (entry->key == key)
			return (entry);
		index = (index + 1) % capacity;
	}
}

static void	adjust_capacity(t_table *table, int capacity)
{
	int		index;
	t_entry	entry;
	t_entry	*dest;
	t_entry	*entries;

	entries = ft_calloc(capacity, table->type_size);
	index = 0;
	table->count = 0;
	while (index < table->capacity)
	{
		entry = table->data[index++];
		if (!entry.key)
			continue ;
		dest = find_entry(entries, capacity, entry.key);
		dest->key = entry.key;
		dest->value = entry.value;
		table->count++;
	}
	free(table->data);
	table->data = entries;
	table->capacity = capacity;
}
