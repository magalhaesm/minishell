/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdias-ma <mdias-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:32:01 by ygorgsena         #+#    #+#             */
/*   Updated: 2022/12/20 19:36:43 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include "helpers.h"

# define NEW_LINE "-n"

typedef int	(*t_builtin)(char **args);

t_builtin	builtin_pool(char *name);
int			ft_echo(char	**args);
int			ft_env(char **args);

#endif
