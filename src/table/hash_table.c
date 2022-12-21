/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:39:31 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/12/15 21:10:47 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

static void		adjust_capacity(t_table *table, int capacity);
static int		grow_capacity(int capacity);
static t_uint	hash_string(char *key);

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
	entry->key = ft_strdup(key);
	entry->value = ft_strdup(value);
	return (is_new_key);
}

t_entry	*find_entry(t_entry *entries, int capacity, char *key)
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
		else if (ft_strncmp(entry->key, key, ft_strlen(key)) == 0)
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

// SOURCE: http://www.isthe.com/chongo/tech/comp/fnv/
static t_uint	hash_string(char *key)
{
	t_uint	hash;
	int		index;

	hash = 2166136261;
	index = 0;
	while (key[index])
	{
		hash ^= (t_byte)key[index];
		hash *= 16777619;
		index++;
	}
	return (hash);
}

static int	grow_capacity(int capacity)
{
	if (capacity < 8)
		return (8);
	return (capacity * 2);
}
