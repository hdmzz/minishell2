#include "minishell.h"

int	pwd_builtin(void)
{
	char	path[PATH_MAX];
	char	*cwd;

	cwd = getcwd(path, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (1);
	}
	return (0);
}
