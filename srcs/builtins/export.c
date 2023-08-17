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

static int	my_set_env(const char *name, const char *value, t_shell *g_shell)
{
	char	*new_env_var;
	// Vérifier si la variable d'environnement existe déjà si elle existe deja overwrite
	
	// Sinon créer une nouvelle entrée sous forme de chaîne "nom=valeur"
	new_env_var = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2, sizeof(char));
	if (!new_env_var)
		return (0);
	ft_vsprintf(new_env_var, "%s=%s", name, value);
	printf("resultat = %s\n", new_env_var);
	free(new_env_var);
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

	// Rechercher l'entrée existante dans la liste

	// Si l'entrée n'a pas été trouvée, ajouter la nouvelle entrée à la fin
int	export_builtin(char **user_input, t_shell *g_shell)
{
	char	**name_value_key;
	int		i;

	i = 1;
	while (user_input[i])
	{
		if (!is_valid_env_var_key(user_input[i]))
			return(0);
		else if (ft_strchr(user_input[i], '=') != NULL)
			name_value_key = get_name_value(user_input[i]);
		i++;
	}
	my_set_env(name_value_key[0], name_value_key[1], g_shell);
	ft_free_split(name_value_key);
	return (0);
}

//bool	set_env_var(t_data *data, char *key, char *value)
//{
//	int		idx;
//	char	*tmp;

//	idx = get_env_var_index(data->env, key);
//	if (value == NULL)
//		value = "";
//	tmp = ft_strjoin("=", value);
//	if (!tmp)
//		return (false);
//	if (idx != -1 && data->env[idx])
//	{
//		free_ptr(data->env[idx]);
//		data->env[idx] = ft_strjoin(key, tmp);
//	}
//	else
//	{
//		idx = env_var_count(data->env);
//		data->env = realloc_env_vars(data, idx + 1);
//		if (!data->env)
//			return (false);
//		data->env[idx] = ft_strjoin(key, tmp);
//	}
//	free_ptr(tmp);
//	return (true);
//}
