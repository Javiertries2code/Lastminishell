#include "../mini.h"

int	env_len(t_env *env)
{
	int	i = 0;

	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int	args_len(t_token *list)
{
	int	i;

	i = 0;
	while (list && list->token_op == STRING)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	check_redirs(t_token *list)
{
	while (list)
	{
		if (list->token_op == RED_FORWD)
			return (1);
		else if (list->token_op == RED_BACKWD)
			return (2);
		else if (list->token_op == APPEND)
			return (3);
		else if (list->token_op == HEREDOC)
			return (4);
		list = list->next;
	}
	return (0);
}

t_token	*get_cmd_from_list(t_token *list)
{
	while (list)
	{
		if (list->token_op == COMMAND || list->token_op == BUILTIN)
		{
			return (list);
		}
		list = list->next;
	}
	return (NULL);
}

void	setcmd(t_token ***list, t_data *data)
{
	char	*cmd = NULL;
	int		i = 0;

	while (i < data->num_comands)
	{
		while ((*list)[i]->next)
		{
			cmd = get_cmd_path(data->env_head, (*list)[i]->value);
			if (cmd)
				(*list)[i]->token_op = COMMAND;
			free(cmd);
			(*list)[i] = (*list)[i]->next;
		}
		cmd = get_cmd_path(data->env_head, (*list)[i]->value);
		if (cmd)
			(*list)[i]->token_op = COMMAND;
		free(cmd);
		while ((*list)[i]->prev)
		{
			(*list)[i] = (*list)[i]->prev;
		}
		i++;
	}
}

/*
DEBUG!!!!!!!
void	printcharptrptrnull(char **ptrptr)
{
	int	i = 0;

	while (ptrptr[i])
	{
		printf("%d   ->    %s\n", i,  ptrptr[i]);
		i++;
	}
}
 */