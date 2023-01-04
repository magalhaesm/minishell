/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-goes <yde-goes@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:32:01 by yde-goes          #+#    #+#             */
/*   Updated: 2023/01/03 12:18:57 by mdias-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <dirent.h>

# include "exec.h"
# include "helpers.h"

# define NEW_LINE "-n"

typedef int	(*t_builtin)(char **args);

t_builtin	builtin_pool(char *name, t_context *ctx);
int			ft_echo(char **args);
int			ft_env(char **args);
int			ft_pwd(char **args);
int			ft_unset(char **args);
int			ft_cd(char	**args);
int			ft_export(char	**args);
int			ft_exit(char **args);

#endif
