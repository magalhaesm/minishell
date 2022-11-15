/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:59:43 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/15 08:13:18 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internals.h"

void	init_table(t_table *table)
{
	table->count = 0;
	table->capacity = 0;
	table->type_size = sizeof(*table->data);
	table->data = NULL;
}

// SOURCE: http://www.isthe.com/chongo/tech/comp/fnv/
t_uint	hash_string(char *key)
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

int	grow_capacity(int capacity)
{
	if (capacity < 8)
		return (8);
	return (capacity * 2);
}

void	free_table(t_table *table)
{
	free(table->data);
}
