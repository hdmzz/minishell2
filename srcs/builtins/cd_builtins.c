#include "minishell.h"

int	cd_builtin(char **cmd)
{
	printf("%s\n", cmd[0]);
}
