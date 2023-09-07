/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsilverb <hsilverb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:52 by hdamitzi          #+#    #+#             */
/*   Updated: 2023/09/07 16:50:21 by hsilverb         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (0);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	add_new_var(char *new_env_var, t_shell *g_shell)
{
	char	**new_env;
	int		env_size;
	int		i;

	i = 0;
	env_size = split_lenght(g_shell->split_env) + 1;
	new_env = ft_calloc(env_size + 1, sizeof(char *));
	if (new_env == NULL)
		return (0);
	while (i < env_size)
	{
		if (i == env_size - 1)
			new_env[i] = ft_strdup(new_env_var);
		else
			new_env[i] = ft_strdup(g_shell->split_env[i]);
		i++;
	}
	new_env[i] = NULL;
	ft_free_split(g_shell->split_env);
	g_shell->split_env = NULL;
	g_shell->split_env = new_env;
	new_env_var = ft_free_ptr(new_env_var);
	return (1);
}

int	my_set_env(const char *name, char *value, t_shell *g_shell)
{
	char	*new_env_var;
	int		idx;

	idx = get_env_idx(name, g_shell);
	if (value == NULL)
		value = "";
	new_env_var = ft_calloc(ft_strlen(name) + \
	ft_strlen(value) + 2, sizeof(char));
	if (!new_env_var)
		return (0);
	ft_vsprintf(new_env_var, "%s=%s", name, value);
	if (idx != -1)
	{
		ft_free_ptr(g_shell->split_env[idx]);
		g_shell->split_env[idx] = new_env_var;
	}
	else
		add_new_var(new_env_var, g_shell);
	return (1);
}

static char	**get_name_value(char *str)
{
	char	*eq_position;
	char	**name_value_key;

	name_value_key = ft_calloc(3, sizeof(char *));
	if (!name_value_key)
		return (NULL);
	eq_position = ft_strchr(str, '=');
	name_value_key[0] = ft_substr(str, 0, eq_position - str);
	name_value_key[1] = ft_substr(eq_position, 1, ft_strlen(str));
	name_value_key[2] = NULL;
	return (name_value_key);
}

int	export_builtin(t_cmd *c, t_shell *g_shell)
{
	char	**name_value_key;
	int		i;
	char	**user_input;

	i = 1;
	user_input = c->cmd;
	if (!user_input[i])
		return (env_builtin(user_input, g_shell));
	while (user_input[i])
	{
		if (!is_valid_env_var_key(user_input[i]))
			return (error_handler("export", user_input[i], \
			"not a valid env var key", EXIT_FAILURE));
		else if (ft_strchr(user_input[i], '=') != NULL)
		{
			name_value_key = get_name_value(user_input[i]);
			my_set_env(name_value_key[0], name_value_key[1], g_shell);
			ft_free_split(name_value_key);
			name_value_key = NULL;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
