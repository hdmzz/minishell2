#include "minishell.h"

int	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')//on verifie la premiere lettre n'est pas un charactere alphabetique et si c'est le cas si le charactere n'est pas un underscore
		return (0);//on on pas un caractere alphabetique et que ce n'est pas
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
	return (1);
}

int	my_set_env(const char *name, char *value, t_shell *g_shell)
{
	char	*new_env_var;
	int		idx;

	idx = get_env_idx(name, g_shell);
	if (value == NULL)
		value = "";
	new_env_var = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2, sizeof(char));
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

	// Si l'entrée n'a pas été trouvée, ajouter la nouvelle entrée à la fin
int	export_builtin(t_cmd *c, t_shell *g_shell)
{
	char	**name_value_key;
	int		i;
	char	**user_input;

	i = 1;
	user_input = c->cmd;
	while (user_input[i])
	{
		if (!is_valid_env_var_key(user_input[i]))
			return(perror("Not a valid env var key value"), -1);
		else if (ft_strchr(user_input[i], '=') != NULL)
			name_value_key = get_name_value(user_input[i]);
		i++;
	}
	my_set_env(name_value_key[0], name_value_key[1], g_shell);
	ft_free_split(name_value_key);
	name_value_key = NULL;
	return (1);
}
