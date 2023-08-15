#include "minishell.h"

//static int	my_set_env(const char *name, const char *value)
//{
//	char	*new_env_var;
//	// Vérifier si la variable d'environnement existe déjà
//	if (getenv(name) != NULL)
//		return (0);
//	// Sinon créer une nouvelle entrée sous forme de chaîne "nom=valeur"
//	new_env_var = ft_calloc(ft_strlen(name) + ft_strlen(value) + 2, sizeof(char));
//	if (!new_env_var)
//		return (0);
//	ft_vsprintf(new_env_var, "%s=%s", name, value);
//	printf("resultat = %s\n", new_env_var);
//	free(new_env_var);
//	return (1);
//}

	// Rechercher l'entrée existante dans la liste

	// Si l'entrée n'a pas été trouvée, ajouter la nouvelle entrée à la fin
int	export_builtin(char **user_input)
{
	char	*recomposed_cmd;
	char	**splitted_export;

	recomposed_cmd = ft_recompose_split(user_input, ' ');
	splitted_export = ft_split(recomposed_cmd, '=');
	printf("recompose cmd = :%s:\n splitted[1] = :%s:\n", recomposed_cmd, splitted_export[1]);
	//my_set_env(splited_input[0], splited_input[1]);
	//ft_free_split(splited_input);
	ft_free_split(splitted_export),
	free(recomposed_cmd);
	return (1);
}
