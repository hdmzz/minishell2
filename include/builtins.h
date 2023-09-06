/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdamitzi <hdamitzi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:13:15 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/06 14:24:06 by hdamitzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "typedef.h"

int		cd_builtin(t_cmd *c, t_shell *g_shell);
int		dispatcher_builtin(t_shell *g_shell, t_cmd *c);
int		exit_builtin(t_shell *g_shell, int last_exit);
int		export_builtin(t_cmd *c, t_shell *g_shell);
int		pwd_builtin(void);
int		echo_builtin(char **args);
int		unset_builtin(t_cmd *c, t_shell *g_shell);
int		env_builtin(char **cmd, t_shell *g_shell);

//export.c
int		my_set_env(const char *name, char *value, t_shell *g_shell);
int		get_env_idx(const char *name, t_shell *g_shell);
int		is_valid_env_var_key(char *var);
char	*get_env_value(char *name, t_shell *g_shell);

#endif
