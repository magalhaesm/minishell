/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internals.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:12:50 by mdias-ma          #+#    #+#             */
/*   Updated: 2022/11/15 08:15:47 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNALS_H
# define INTERNALS_H

# include "hash_table.h"

# define TABLE_LOAD_MAX 0.75
# define RIP ((void *)1)

typedef unsigned int	t_uint;

int		grow_capacity(int capacity);
t_uint	hash_string(char *key);

#endif
