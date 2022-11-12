/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:39:31 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/11 23:16:42 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_table(t_table *table)
{
	table->count = 0;
	table->capacity = 0;
	table->type_size = sizeof(*table->data);
	table->data = NULL;
}
