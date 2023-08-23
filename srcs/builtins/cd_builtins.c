#include "minishell.h"

char	*get_env_value(char *name, t_shell *g_shell)//doit recuperer la valeur de la variaable name ds l'env contenue ds g_shell donc tout ce qu'il y aapres le =
{
	char	*value;
	int		indx;

	indx = get_env_idx(name, g_shell);
	if (indx == -1)
		return (NULL);
	value = g_shell->split_env[indx];
	value = ft_strchr(value, '=') + 1;//pas besoin de free buff car on ne l'a pas alloue
	return (value);
}

int	get_env_idx(const char *name, t_shell *g_shell)
{
	int		i;
	char	*buff;
	char	**env;

	i = 0;
	buff = ft_strjoin(name, "=");
	env = g_shell->split_env;
	while (env[i])
	{
		if (ft_strncmp(buff, env[i], ft_strlen(buff)) == 0)
			return(ft_free_ptr(buff), i);
		i++;
	}
	return (ft_free_ptr(buff), -1);
}

static int	change_dir(char	*path, t_shell *g_shell)
{
	char	*cwd;
	char	buff[PATH_MAX];

	cwd = getcwd(buff, PATH_MAX);
	if (!cwd || !path)
		return (0);
	if (chdir(path) == -1)
		return (0);
	my_set_env("OLD_PWD", get_env_value("PWD", g_shell), g_shell);
	my_set_env("PWD", cwd, g_shell);
	return (1);
}

int	cd_builtin(t_cmd *c, t_shell *g_shell)
{
	int	len;

	len = split_lenght(c->cmd);
	if (len > 2)
		return(0);//trop d'arguments
	else if (len == 1)
		return (change_dir(get_env_value("HOME", g_shell), g_shell));
	else if (len == 2 && !ft_strcmp(c->cmd[1], "-"))
		return (change_dir(getenv("OLD_PWD"), g_shell));
	return (change_dir(c->cmd[1], g_shell));
}
