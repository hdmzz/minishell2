#include "../../include/minishell.h"

static bool	no_cmd_btw_pipes(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (temp->type == pipeline)
		{
			temp = temp->next;
			while (temp && temp->type == white_space)
				temp = temp->next;
			if (temp && temp->type == pipeline)
				return (true);
		}
		temp = temp->next;
	}
	return (false);
}

//normalement le token est au debut de la chaine de caractere
//donc on vance tant qu'il y a des espaces puis si le token suivant les espaces
//est un pipe alors erreur;
static bool	space_then_pipe(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp && temp->type == white_space)
		temp = temp->next;
	if (temp && temp->type == pipeline)
		return (true);
	return (false);
}

//il faut verifier 1)que lusieurs pipe ne se suivent pas sans commande entre,
//2)si le premier token n'est pas un pipe,
//3)si l'input commence par des espace suivi d'un pipe
//si 1 ou 2 ou 3 alors error
bool	pipes_conformity(t_shell *g_shell)
{
	t_token	*token;

	token = g_shell->list_token;
	if (token && token->type == pipeline)
		return (false);
	if (no_cmd_btw_pipes(token))
		return (false);
	if (space_then_pipe(token))
		return (false);
	return (true);
}
