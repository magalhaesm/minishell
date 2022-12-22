/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:32:01 by yde-goes          #+#    #+#             */
/*   Updated: 2022/12/22 11:07:01 by yde-goes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "helpers.h"

# define NEW_LINE "-n"

typedef int	(*t_builtin)(char **args);

t_builtin	builtin_pool(char *name);
int			ft_echo(char **args);
int			ft_env(char **args);

#endif
